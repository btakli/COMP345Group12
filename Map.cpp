#include "Map.h"

Map* Map::_instance_ptr = nullptr;

Map::Map() {
	_territories_ptr = new std::list<Territory*>();
	_continents_ptr = new std::vector<Continent*>();
}

Map::Map(const Map& to_copy) {
	_instance_ptr = to_copy.get_instance();
}

Map* Map::get_instance() {
	if (_instance_ptr == nullptr) {
		_instance_ptr = new Map();
	}
	return _instance_ptr;
}

void Map::set_territory(Territory& new_territory) {

	_territories_ptr->push_back(&new_territory);
}

void Map::set_continent(int& territory_index, Continent& new_continent) {

	try {
		bool found = false;

		for (Territory* territory : get_territories()) {
			if (territory_index == territory->get_index()) {
				found = true;
				get_continents().push_back(&new_continent);
				territory->add_continent(new_continent);
			}
		}
		if (!found) throw std::runtime_error(" Fail to find territory: " + territory_index);
	}
	catch (std::runtime_error e) {
		throw e;
	}
}

void Map::set_border(std::vector<std::string> splited_borders) {

	try {
		int curr_continent_index = stoi(splited_borders[0]) - 1;

		for (size_t i = 1; i < splited_borders.size(); i++) { // 0 is the current selected continent the remainig are its neighbours

			Continent* continent = get_continent(stoi(splited_borders[i]));

			if (continent) {
				get_continents()[curr_continent_index]->set_neighbor(*continent);
			}
			else {
				throw new std::runtime_error("Continent not found for " + (curr_continent_index + 1));
			}
		}
	}
	catch (std::runtime_error e) {
		throw e;
	}
}

bool Map::validate() {

	std::queue<Continent*> queue;

	queue.push(get_continents()[0]);

	get_continents()[0]->set_visited(*new bool(true));

	int size = (int)(get_continents().size());
	int count = 0;

	return help_validate(queue, size, count);
}

bool Map::help_validate(std::queue<Continent*>& to_be_visited, int& size, int& count) {

	if (to_be_visited.size() <= 0) {
		std::cout << "\n-- MAP VALIDATION PASS: " << count << std::endl;

		if (size == count) return true;
		return false;
	}
	else {

		Continent* current = to_be_visited.front();
		to_be_visited.pop();

		std::list<Continent*>& neighbors = current->get_neighbors();

		if (neighbors.size() <= 0) { // Dead end
			std::cout << "-- MAP FAIL VALIDATION: DEAD END --" << std::endl;
			return false;
		}
		else {
			for (Continent* neighbor : neighbors) {

				if (!neighbor->get_visited()) {
					neighbor->set_visited(*new bool(true));

					to_be_visited.push(neighbor);
				}
			}
		}
	}

	return help_validate(to_be_visited, size, ++count);
}

void Map::display() const {

	if (_territories_ptr->size() == 0 && _continents_ptr->size() == 0) return;

	std::cout << "-- DISPLAY --\n" << std::endl;

	for (Territory* territory : *_territories_ptr) {
		std::cout << territory->to_string() << std::endl;
	}

	std::cout << "-- DISPLAY END --\n" << std::endl;

}

Continent* Map::get_continent(int index) {
	for (Continent* c : get_continents()) {
		if (c->get_index() == index) return c;
	}

	return nullptr;
}

std::list<Territory*>& Map::get_territories() const {
	return *_territories_ptr;
}

std::vector<Continent*>& Map::get_continents() const {
	return *_continents_ptr;
}

void Map::unload() {

	if (get_territories().size() <= 0 && get_continents().size() <= 0) return;

	std::cout << "\n-- UNLOADING --\n" << std::endl;

	for (Territory* c : get_territories()) delete c;
	for (Continent* c : get_continents()) delete c;

	_territories_ptr->clear();
	_continents_ptr->clear();

	std::cout << "\n-- UNLOADING END --\n" << std::endl;
}

Map& Map::operator=(const Map& map) {
	_instance_ptr = map.get_instance();
	return *this;
}

Map::~Map() {
	unload();

	delete _instance_ptr;
}


std::ostream& operator<<(std::ostream& stream, const Map& map) {

	stream << "-- DISPLAY --\n\n";

	for (Territory* territory : map.get_territories()) {
		stream << territory->to_string() << std::endl;
	}

	stream << "-- DISPLAY END --\n\n";

	return stream;
}





/******** MAP LOADER *******/

#define CONTINENTS "[continents]" // == Territory
#define COUNTRIES "[countries]" // == Continent
#define BORDERS "[borders]" // == Border


MapLoader* MapLoader::_instance_ptr = nullptr;


MapLoader::MapLoader() {
	// Empty - see instance
}

MapLoader::MapLoader(const MapLoader& to_copy) {
	_instance_ptr = to_copy.get_instance();
}

void MapLoader::load_map(std::string map_file_name) {

	map_file_name = "resources/" + map_file_name + ".map";

	if (!verify(map_file_name)) return; // Map fails basic verifications

	Map::get_instance()->unload(); // Force unload old map

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
			make_territory(split(line));
			break;

		case FileBlock::Borders:
			assign_borders(split(line));
			break;

		case FileBlock::Countries:
			make_continent(split(line));
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
	if (_instance_ptr == nullptr) {
		_instance_ptr = new MapLoader();
	}
	return _instance_ptr;
}

std::vector<std::string>& MapLoader::split(std::string& line) const {
	std::vector<std::string>* tokens = new std::vector<std::string>();

	size_t start = 0;
	for (size_t i = 0; i < line.size(); i++) {
		if (line[i] == ' ') {
			(*tokens).push_back(line.substr(start, i - start));
			start = i + 1;
		}
		else if (i == line.size() - 1) {
			(*tokens).push_back(line.substr(start, i - start + 1));
		}
	}

	return *tokens;
}

void MapLoader::make_territory(std::vector<std::string>& line_tokens) {

	try {

		std::string* territory_name_ptr = new std::string(line_tokens[0]);
		std::string* color_ptr = new std::string(line_tokens[2]);

		if (!is_number(line_tokens[1])) throw std::runtime_error("Army value is not of type int: " + line_tokens[1]);

		int* army_value_ptr = new int(stoi(line_tokens[1]));

		Territory* new_territory = new Territory(*territory_name_ptr, *army_value_ptr, *color_ptr);
		Map::get_instance()->set_territory(*new_territory);
	}
	catch (std::runtime_error e) {
		delete& line_tokens;
		throw e;
	}

	delete& line_tokens;
}

void MapLoader::make_continent(std::vector<std::string>& line_tokens) {

	try {
		std::string* continent_name = new std::string(line_tokens[1]);

		if (!is_number(line_tokens[0])) throw std::runtime_error("Continent value is not of type int: " + line_tokens[0]);
		if (!is_number(line_tokens[2])) throw std::runtime_error("Territory value is not of type int: " + line_tokens[2]);

		int* continent_index_ptr = new int(stoi(line_tokens[0]));
		int* territory_index_ptr = new int(stoi(line_tokens[2]));

		Continent* new_continent = new Continent(*continent_index_ptr, *continent_name);
		Map::get_instance()->set_continent(*territory_index_ptr, *new_continent);
	}
	catch (std::runtime_error e) {
		delete& line_tokens;
		throw e;
	}

	delete& line_tokens;
}

void MapLoader::assign_borders(std::vector<std::string>& line_tokens) {

	try {
		for (std::string& s : line_tokens) if (!is_number(s)) throw new std::runtime_error("Border is not of type int: " + s);

		Map::get_instance()->set_border(line_tokens);
	}
	catch (std::runtime_error const& e) {
		delete& line_tokens;
		throw e;
	}
	delete& line_tokens;
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

MapLoader& MapLoader::operator=(const MapLoader& loader) {
	_instance_ptr = loader.get_instance();
	return *_instance_ptr;
}


MapLoader::~MapLoader() {
	delete _instance_ptr;
}


std::ostream& operator<<(std::ostream& stream, const MapLoader& loader) {
	stream << "Map loader stream. Nothing else to display.\n";
	return stream;
}




/********** TERRITORY **********/  // aka a continent(file)

int Territory::_territories_index = 0;

Territory::Territory(const Territory& to_copy) : LandMass(*new int(to_copy.get_index()), *new std::string(to_copy.get_name())) {
	_army_value_ptr = new int(to_copy.get_army_value());
	_color_ptr = new std::string(to_copy.get_color());
	_continents_ptr = &copy(to_copy.get_continents());
}


Territory::Territory(std::string& territory_name, int& army_value, std::string& color) : LandMass(*(new int(++_territories_index)), territory_name) {

	_army_value_ptr = &army_value;
	_color_ptr = &color;
	_continents_ptr = new std::list<Continent*>();
}

int Territory::get_army_value() const {
	return *_army_value_ptr;
}

std::string Territory::to_string() const {

	std::string tmp = "";

	for (Continent* c : get_continents()) tmp += "   " + c->to_string() + "\n";

	return LandMass::to_string() + " | Army: " + std::to_string(get_army_value()) + " | " + get_color() + "\n"
		+ tmp;
}

void Territory::add_continent(Continent& new_continent) {
	get_continents().push_back(&new_continent);
}

Territory& Territory::operator=(const Territory& continent)
{
	delete _color_ptr;
	delete _army_value_ptr;
	delete _continents_ptr;
	delete& get_name();
	delete& get_index();

	_army_value_ptr = new int(continent.get_army_value());
	_color_ptr = new std::string(continent.get_color());
	_continents_ptr = &copy(continent.get_continents());

	set_index(*new int(continent.get_index()));
	set_name(*new std::string(continent.get_name()));

	return *this;
}


std::list<Continent*>& Territory::get_continents() const {
	return *_continents_ptr;
}

std::string Territory::get_color() const {
	return *_color_ptr;
}

Territory::~Territory() {
	std::cout << "Unloaded:\t" << typeid(Territory).name() << "\t\t" << LandMass::get_name() << std::endl;

	_territories_index = 0;

	delete _color_ptr;
	delete _army_value_ptr;
	delete _continents_ptr;
}

std::ostream& operator<<(std::ostream& stream, const Territory& continent) {

	return stream << continent.to_string();
}


/*********** CONTINENT **********/     // aka a country(file)

Continent::Continent(const Continent& to_copy) : LandMass(*new int(to_copy.get_index()), *new std::string(to_copy.get_name())) {

	_player_ptr = to_copy.check_claim();
	_visited_ptr = new bool(to_copy.get_visited());
	_neighbor_continents_ptr = &copy(to_copy.get_neighbors());
	_stationed_army_ptr = new int(to_copy.get_stationed_army());

}

Continent::Continent(int& index, std::string& continent_name) : LandMass(index, continent_name) {

	_player_ptr = nullptr;
	_visited_ptr = new bool(false);
	_neighbor_continents_ptr = new std::list<Continent*>();
	_stationed_army_ptr = new int(0);
}

std::list<Continent*>& Continent::get_neighbors() const {
	return *_neighbor_continents_ptr;
}

void Continent::set_neighbor(Continent& bordered_continent) {
	_neighbor_continents_ptr->push_back(&bordered_continent);
}

std::string Continent::to_string() const {
	std::string tmp = "";

	for (Continent* c : get_neighbors()) tmp += "\t>> " + std::to_string(c->get_index()) + " " + c->get_name() + "\n";

	return LandMass::to_string() + "\n" + tmp;
}

bool& Continent::get_visited() const {
	return *_visited_ptr;
}

void Continent::set_visited(bool& visited) {

	delete _visited_ptr;
	_visited_ptr = &visited;
}

int& Continent::get_stationed_army() const {
	return *_stationed_army_ptr;
}

void Continent::set_stationed_army(int& army) {
	_stationed_army_ptr = &army;
}

Continent& Continent::operator=(const Continent& continent) {

	delete& get_name();
	delete& get_index();
	delete _neighbor_continents_ptr;
	delete _visited_ptr;
	delete _stationed_army_ptr;

	set_name(*new std::string(continent.get_name()));
	set_index(*new int(continent.get_index()));
	_visited_ptr = new bool(continent.get_visited());
	_neighbor_continents_ptr = &copy(continent.get_neighbors());
	_stationed_army_ptr = new int(continent.get_stationed_army());

	return *this;
}

void Continent::claim(Player& player) {
	_player_ptr = &player;
}

Player* Continent::check_claim() const {
	return _player_ptr;
}

Continent::~Continent() {

	std::cout << "Unloaded:\t" << typeid(Continent).name() << "\t\t" << LandMass::get_name() << std::endl;

	delete _neighbor_continents_ptr;
	delete _visited_ptr;
	delete _stationed_army_ptr;
}

std::ostream& operator<<(std::ostream& stream, const Continent& continent) {
	
	return stream << continent.to_string();
}



/*********** TERRITORY ********/

LandMass::LandMass(const LandMass& to_copy) {
	_index_ptr = new int(to_copy.get_index());
	_name_ptr = new std::string(to_copy.get_name());
}

LandMass::LandMass(int& index, std::string& territory_name) {
	_index_ptr = &index;
	_name_ptr = &territory_name;
}

void LandMass::set_index(int& new_index) {
	_index_ptr = &new_index;
}

void LandMass::set_name(std::string& new_name) {
	_name_ptr = &new_name;
}


std::string& LandMass::get_name() const {
	return *_name_ptr;
}

int& LandMass::get_index() const {
	return *_index_ptr;
}

std::string LandMass::to_string() const {
	return "[" + std::to_string(get_index()) + "] " + get_name();
}

LandMass& LandMass::operator=(const LandMass& territory) {
	delete _index_ptr;
	delete _name_ptr;

	set_index(*new int(territory.get_index()));
	set_name(*new std::string(territory.get_name()));

	return *this;
}

LandMass::~LandMass() {
	std::cout << "Unloaded:\t" << typeid(LandMass).name() << "\t\t" << LandMass::get_name() << std::endl;

	delete _index_ptr;
	delete _name_ptr;
}


std::ostream& operator << (std::ostream& stream, const LandMass& territory) {
	
	return stream << territory.to_string();
}



//********** Global scope utility functions ********//

template <typename T>
std::list<T*>& copy(std::list<T*> to_copy) {
	std::list<T*>* tmp = new std::list<T*>();

	for (T* t : to_copy) (*tmp).push_back(t);

	return *tmp;
}

template <typename T>
std::vector<T*>& copy(std::vector<T*> to_copy) {
	std::vector<T*>* tmp = new std::vector<T*>();

	for (T* t : to_copy) (*tmp).push_back(t);

	return *tmp;
}