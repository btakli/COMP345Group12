#include "Map.h"

Map* Map::_instance = nullptr;

Map::Map() {
	_continents = new std::list<Continent*>();
	_countries = new std::vector<Country*>();
}

Map* Map::get_instance() {
	if (_instance == nullptr) {
		_instance = new Map();
	}
	return _instance;
}

void Map::set_continent(Continent& new_continent) {

	_continents->push_back(&new_continent);
}

void Map::set_country(int& continent_index, Country& new_country) {

	try {
		bool found = false;

		for (Continent* continent : get_continents()) {
			if (continent_index == continent->get_index()) {
				found = true;
				get_countries().push_back(&new_country);
				continent->add_country(new_country);
			}
		}
		if (!found) throw std::runtime_error(" Fail to find continent: " + continent_index);
	}
	catch (std::runtime_error e) {
		throw e;
	}
}

void Map::set_border(std::vector<std::string> splited_borders) {

	try {
		int curr_country_index = stoi(splited_borders[0]) - 1;

		for (size_t i = 1; i < splited_borders.size(); i++) { // 0 is the current selected country the remainig are its neighbours

			Country* country = get_country(stoi(splited_borders[i]));

			if (country) {
				get_countries()[curr_country_index]->set_neighbor(*country);
			}
			else {
				throw new std::runtime_error("Country not found for " + (curr_country_index + 1));
			}
		}
	}
	catch(std::runtime_error e) {
		throw e;
	}
}

bool Map::validate() {

	std::queue<Country*> queue;

	queue.push(get_countries()[0]);

	get_countries()[0]->set_visited(*new bool(true));

	int size = (int)(get_countries().size());
	int count = 0;

	return help_validate(queue, size, count);
}

bool Map::help_validate(std::queue<Country*>& to_be_visited, int& size, int& count) {
	
	if (to_be_visited.size() <= 0) {
		std::cout << "\n-- MAP VALIDATION PASS: " << count << std::endl;

		if (size == count) return true;
		return false;
	}
	else {

		Country* current = to_be_visited.front();
		to_be_visited.pop();
		
		std::list<Country*>& neighbors = current->get_neighbors();

		if (neighbors.size() <= 0) { // Dead end
			std::cout << "-- MAP FAIL VALIDATION: DEAD END --" << std::endl;
			return false;
		}
		else {
			for (Country* neighbor : neighbors) {

				if (!neighbor->get_visited()) {
					neighbor->set_visited(*new bool(true));

					to_be_visited.push(neighbor);
				}
			}
		}
	}

	return help_validate(to_be_visited, size, ++count);
}

void Map::display() {

	if (_continents->size() == 0 && _countries->size() == 0) return;

	std::cout << "-- DISPLAY --\n" << std::endl;

	for (Continent* continent : *_continents) {
		std::cout << continent->to_string() << std::endl;
	}

	std::cout << "-- DISPLAY END --\n" << std::endl;

}

Country* Map::get_country(int index) {
	for (Country* c : get_countries()) {
		if (c->get_index() == index) return c;
	}

	return nullptr;
}

std::list<Continent*>& Map::get_continents() {
	return *_continents;
}

std::vector<Country*>& Map::get_countries(){
	return *_countries;
}

void Map::unload() {
	
	if (get_continents().size() <= 0 && get_countries().size() <= 0) return;

	std::cout << "\n-- UNLOADING --\n" << std::endl;

	for (Continent* c : get_continents()) delete c;
	for (Country* c : get_countries()) delete c;

	_continents->clear();
	_countries->clear();

	std::cout << "\n-- UNLOADING END --\n" << std::endl;
}

Map::~Map() {
	unload();

	delete _instance;
}




/******** MAP LOADER *******/

#define CONTINENTS "[continents]"
#define COUNTRIES "[countries]"
#define BORDERS "[borders]"


MapLoader* MapLoader::_instance = nullptr;


MapLoader::MapLoader() {
	// Empty - see instance
}

void MapLoader::load_map(std::string map_file_name) {

	map_file_name = "resources/" + map_file_name + ".map";

	if (!verify(map_file_name)) return; // Map fails basic verifications


	try {
		std::ifstream reader(map_file_name);

		if (reader.is_open()) {

			std::string line;
			FileBlock read_block = FileBlock::None;

			while (std::getline(reader, line)) {

				if (line._Equal(CONTINENTS)) {
					read_block = FileBlock::Continents;
					continue;
				}
				else if (line._Equal(COUNTRIES)) {
					read_block = FileBlock::Countries;
					continue;
				}
				else if (line._Equal(BORDERS)) {
					read_block = FileBlock::Borders;
					continue;
				}
				else if (line[0] == ';' || line.empty()) { // Ignore comments && empty
					continue;
				}

				if (read_block != FileBlock::None) sort_map_file_data(read_block, line);
			}

			reader.close();
		}
		else {
			throw std::runtime_error("Fail to open file @loading map : " + map_file_name);
		}
	}
	catch (std::runtime_error const& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		Map::get_instance()->unload();
		return;
	}
}

void MapLoader::sort_map_file_data(FileBlock& fileBlock, std::string& line) {

	try {
		switch (fileBlock) {

		case FileBlock::Continents:
			make_continent(split(line));
			break;

		case FileBlock::Borders:
			assign_borders(split(line));
			break;

		case FileBlock::Countries:
			make_countries(split(line));
			break;

		default:
			throw std::runtime_error("Unkown file block. Please reformat file.");
		}
	}
	catch (std::runtime_error const& e) {
		throw e;
	}
}

MapLoader* MapLoader::get_instance() {
	if (_instance == nullptr) {
		_instance = new MapLoader();
	}
	return _instance;
}

std::vector<std::string> MapLoader::split(std::string& line) const {
	std::vector<std::string> tokens;

	size_t start = 0;
	for (size_t i = 0; i < line.size(); i++) {
		if (line[i] == ' ') {
			tokens.push_back(line.substr(start, i - start));
			start = i + 1;
		}
		else if (i == line.size() - 1) {
			tokens.push_back(line.substr(start, i - start + 1));
		}
	}
	return tokens;
}

void MapLoader::make_continent(std::vector<std::string> line_tokens) {

	try {

		std::string* continent_name_ptr = new std::string(line_tokens[0]);
		std::string* color_ptr = new std::string(line_tokens[2]);

		if (!is_number(line_tokens[1])) throw std::runtime_error("Army value is not of type int: " + line_tokens[1]);

		int* army_value_ptr = new int(stoi(line_tokens[1]));

		Continent* new_continent = new Continent(*continent_name_ptr, *army_value_ptr, *color_ptr);
		Map::get_instance()->set_continent(*new_continent);
	}
	catch (std::runtime_error e) {
		throw e;
	}
}

void MapLoader::make_countries(std::vector<std::string> line_tokens) {

	try {
		std::string* country_name = new std::string(line_tokens[1]);

		if (!is_number(line_tokens[0])) throw std::runtime_error("Country value is not of type int: " + line_tokens[0]);
		if (!is_number(line_tokens[2])) throw std::runtime_error("Continent value is not of type int: " + line_tokens[2]);

		int* country_index_ptr = new int(stoi(line_tokens[0]));
		int* continent_index_ptr = new int(stoi(line_tokens[2]));

		Country* new_country = new Country(*country_index_ptr, *country_name);
		Map::get_instance()->set_country(*continent_index_ptr, *new_country);
	}
	catch (std::runtime_error e) {
		throw e;
	}
}

void MapLoader::assign_borders(std::vector<std::string> line_tokens) {

	try {
		for (std::string& s : line_tokens) if (!is_number(s)) throw new std::runtime_error("Border is not of type int: " + s);

		Map::get_instance()->set_border(line_tokens);
	}
	catch (std::runtime_error const& e) {
		throw e;
	}
}

bool MapLoader::verify(std::string map_file_name) {

	int file_format_tester = 0;

	std::ifstream reader(map_file_name);

	if (reader.is_open()) {

		std::string line;
		FileBlock read_block = FileBlock::None;

		while (std::getline(reader, line)) {
			if (line._Equal(CONTINENTS)
				|| line._Equal(COUNTRIES)
				|| line._Equal(BORDERS))
				file_format_tester++;
		}

		if (file_format_tester != 3) { // 3 for the 3 file blocks (continents, countries, borders)
			throw std::runtime_error("File format is not respected.");
		}

		reader.close();
		return true;
	}
	else {
		throw std::runtime_error("Fail to open file @file format verifier: " + map_file_name);
	}

	return false;
}

bool MapLoader::is_number(std::string& str) {
	for (char& s : str) if (!isdigit(s)) return false;
	return true;
}

MapLoader::~MapLoader() {
	delete _instance;
}




/********** CONTINENT **********/

int Continent::_continent_index = 0;

Continent::Continent(std::string& continent_name, int& army_value, std::string& color) : Territory(*(new int(++_continent_index)), continent_name) {

	_army_value_ptr = &army_value;
	_color_ptr = &color;
	_countries = new std::list<Country*>();
}

int Continent::get_army_value() {
	return *_army_value_ptr;
}

std::string Continent::to_string() {

	std::string tmp = "";

	for (Country* c : get_countries()) tmp += "   " + c->to_string() + "\n";

	return Territory::to_string() + " | Army: " + std::to_string(get_army_value()) + " | " + get_color() + "\n"
		+ tmp;
}

void Continent::add_country(Country& new_country) {
	get_countries().push_back(&new_country);
}


std::list<Country*>& Continent::get_countries() {
	return *_countries;
}

std::string Continent::get_color() {
	return *_color_ptr;
}


Continent::~Continent() {
	std::cout << "Unloaded:\t" << typeid(Continent).name() << "\t\t" << Territory::get_name() << std::endl;

	_continent_index = 0;

	delete _color_ptr;
	delete _army_value_ptr;
	delete _countries;
}


/*********** COUNTRY **********/

Country::Country(int& index, std::string& country_name) : Territory(index, country_name) {
	_visited_ptr = new bool(false);
	_neighbor_countries = new std::list<Country*>();
	_army = new int(0);
}

std::list<Country*>& Country::get_neighbors() {
	return *_neighbor_countries;
}

void Country::set_neighbor(Country& bordered_country) {
	_neighbor_countries->push_back(&bordered_country);
}

std::string Country::to_string() {
	std::string tmp = "";

	for (Country* c : get_neighbors()) tmp += "\t>> " + std::to_string(c->get_index()) + " " + c->get_name() + "\n";

	return Territory::to_string() + "\n" + tmp;
}

bool& Country::get_visited() {
	return *_visited_ptr;
}

void Country::set_visited(bool& visited) {

	delete _visited_ptr;
	_visited_ptr = &visited;
}

int& Country::get_stationed_army() {
	return *_army;
}

void Country::set_stationed_army(int& army) {
	_army = &army;
}

Country::~Country() {

	std::cout << "Unloaded:\t" << typeid(Country).name() << "\t\t" << Territory::get_name() << std::endl;

	delete _neighbor_countries;
	delete _visited_ptr;
	delete _army;
}


/*********** TERRITORY ********/


Territory::Territory(int& index, std::string& territory_name) {
	_index_ptr = &index;
	_name_ptr = &territory_name;
	_player_ptr = nullptr;
}


std::string Territory::get_name() const {
	return *_name_ptr;
}

int Territory::get_index() const {
	return *_index_ptr;
}

std::string Territory::to_string() {
	return "[" + std::to_string(get_index()) + "] " + get_name();
}

Territory::~Territory() {
	std::cout << "Unloaded:\t" << typeid(Territory).name() << "\t\t" << Territory::get_name() << std::endl;

	delete _index_ptr;
	delete _name_ptr;
}

void Territory::claim(Player& player) {
	_player_ptr = &player;
}

Player* Territory::check_claim() {
	if(_player_ptr) 
		return _player_ptr;
	return nullptr;
}