#include "Map.h"



/******** MAP **********/


Map* Map::_instance_ptr = nullptr;

Map::Map() {
	_continents_ptr = new std::list<Continent*>();
	_territories_ptr = new std::vector<Territory*>();
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

void Map::set_continent(Continent& new_continent) {

	_continents_ptr->push_back(&new_continent);
}

Continent* Map::get_continent(int index) {
	for (Continent* continent : get_continents()) {
		if (continent->get_index() == index) return continent;
	}

	return nullptr;
}


void Map::set_territory(int& continent_index, Territory& new_territory) {

	try {
		bool found = false;

		for (Continent* continent : get_continents()) {
			if (continent_index == continent->get_index()) {
				found = true;
				get_territories().push_back(&new_territory);
				continent->add_territory(new_territory);
				new_territory.set_parent(*continent);
			}
		}
		if (!found) throw std::runtime_error(" Fail to find territory: " + continent_index);
	}
	catch (std::runtime_error e) {
		throw e;
	}
}

void Map::set_border(std::vector<std::string> splited_borders) {

	try {
		int curr_territory_index = stoi(splited_borders[0]) - 1;

		for (size_t i = 1; i < splited_borders.size(); i++) { // 0 is the current selected territory the remainig are its neighbours

			Territory* territory = get_territory(stoi(splited_borders[i]));

			if (territory) {
				get_territories()[curr_territory_index]->set_neighbor(*territory);
			}
			else {
				throw new std::runtime_error("Territory not found for " + (curr_territory_index + 1));
			}
		}
	}
	catch (std::runtime_error e) {
		throw e;
	}
}

bool Map::validate() {

	std::queue<Territory*> queue;

	queue.push(get_territories()[0]);

	get_territories()[0]->set_visited(*new bool(true));

	int size = (int)(get_territories().size());
	int count = 0;

	Territory out_destination;

	// Travel from A to B
	bool reach_destination = help_validate(queue, out_destination, size, count);

	if (!reach_destination) return false;

	// Reset 
	for (Territory* c : *_territories_ptr) c->set_visited(*new bool(false)); 
	while (!queue.empty()) queue.pop(); // Guarantees empty queue
	queue.push(get_territory(out_destination.get_index()));
	get_territories()[out_destination.get_index() - 1]->set_visited(*new bool(true));
	count = 0;
	// Reset End -----

	// Travel from B to A
	reach_destination = help_validate(queue, out_destination, size, count);

	// If travel A to B and B to A valid; therefore, map valid.
	return reach_destination;
}

// Using bfs
bool Map::help_validate(std::queue<Territory*>& to_be_visited, Territory& prev, int& size, int& count) {

	if (to_be_visited.size() <= 0) { // Check if all nodes have ben visited
		if (size == count) return true;
		return false;
	}
	else {

		Territory* current = to_be_visited.front();
		to_be_visited.pop();

		std::vector<Territory*>& neighbors = current->get_neighbors();

		if (neighbors.size() <= 0) { // Dead end
			return false;
		}
		else {

			for (Territory* neighbor : neighbors) {

				if (!neighbor->get_visited()) {
					neighbor->set_visited(*new bool(true));

					to_be_visited.push(neighbor);
				}
			}
		}

		prev = *current;

		return help_validate(to_be_visited, prev, size, ++count);
	}
}

void Map::display() const {

	if (_continents_ptr->size() == 0 && _territories_ptr->size() == 0) return;

	std::cout << "-- DISPLAY --\n" << std::endl;

	for (Continent* continent : *_continents_ptr) {
		std::cout << continent->to_string() << std::endl;
	}

	std::cout << "-- DISPLAY END --\n" << std::endl;

}

Territory* Map::get_territory(int index) {
	for (Territory* territory : get_territories()) {
		if (territory->get_index() == index) return territory;
	}

	return nullptr;
}

std::list<Continent*>& Map::get_continents() const {
	return *_continents_ptr;
}

std::vector<Territory*>& Map::get_territories() const {
	return *_territories_ptr;
}

bool Map::exist() {
	if (_continents_ptr->size() > 0 && _territories_ptr->size() > 0) return true;
	return false;
}

void Map::unload() {

	if (get_continents().size() <= 0 && get_territories().size() <= 0) return;

	for (Continent* c : get_continents()) delete c;
	for (Territory* c : get_territories()) delete c;

	_continents_ptr->clear();
	_territories_ptr->clear();
}

Map& Map::operator=(const Map& other) {
	if (this != &other) {
		_instance_ptr = other.get_instance();
	}
	return *this;
}

Map::~Map() {
	unload();

	delete _instance_ptr;
}


std::ostream& operator<<(std::ostream& stream, const Map& map) {

	stream << "-- DISPLAY --\n\n";

	for (Continent* continent : map.get_continents()) {
		stream << continent->to_string() << std::endl;
	}

	stream << "-- DISPLAY END --\n\n";

	return stream;
}





/******** MAP LOADER *******/

#define CONTINENTS "[continents]" // == Continent
#define COUNTRIES "[countries]" // == Territory
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

				if (line == CONTINENTS) {
					read_block = FileBlock::Continents;
					continue;
				}
				else if (line == COUNTRIES) {
					read_block = FileBlock::Countries;
					continue;
				}
				else if (line == BORDERS) {
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
			make_territory(split(line));
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

void MapLoader::make_continent(std::vector<std::string>& line_tokens) {

	try {

		std::string* continent_name_ptr = new std::string(line_tokens[0]);
		std::string* color_ptr = new std::string(line_tokens[2]);

		if (!is_number(line_tokens[1])) throw std::runtime_error("Army value is not of type int: " + line_tokens[1]);

		int* army_value_ptr = new int(stoi(line_tokens[1]));

		Continent* new_continent = new Continent(*continent_name_ptr, *army_value_ptr, *color_ptr);
		Map::get_instance()->set_continent(*new_continent);
	}
	catch (std::runtime_error e) {
		delete& line_tokens;
		throw e;
	}

	delete& line_tokens;
}

void MapLoader::make_territory(std::vector<std::string>& line_tokens) {

	try {
		std::string* territory_name = new std::string(line_tokens[1]);

		if (!is_number(line_tokens[0])) throw std::runtime_error("Territory value is not of type int: " + line_tokens[0]);
		if (!is_number(line_tokens[2])) throw std::runtime_error("Continent value is not of type int: " + line_tokens[2]);

		int* territory_index_ptr = new int(stoi(line_tokens[0]));
		int* continent_index_ptr = new int(stoi(line_tokens[2]));

		Territory* new_territory = new Territory(*territory_index_ptr, *territory_name);
		Map::get_instance()->set_territory(*continent_index_ptr, *new_territory);
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
			if (line == CONTINENTS
				|| line == COUNTRIES
				|| line == BORDERS)
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

MapLoader& MapLoader::operator=(const MapLoader& other) {
	if (this != &other) {
		_instance_ptr = other.get_instance();
	}
	return *this;
}


MapLoader::~MapLoader() {
	delete _instance_ptr;
}


std::ostream& operator<<(std::ostream& stream, const MapLoader& loader) {
	stream << "Map loader stream. Nothing else to display.\n";
	return stream;
}




/********** Continent **********/  // aka a continent(file)

int Continent::s_territories_index = 0;

Continent::Continent(const Continent& to_copy) : LandMass(to_copy) {

	_bonus_army_value_ptr = new int(to_copy.get_army_bonus_value());
	_color_ptr = new std::string(to_copy.get_color());
	_territories_ptr = &copy(to_copy.get_territories());
}


Continent::Continent(std::string& territory_name, int& army_value, std::string& color) : LandMass(*(new int(++s_territories_index)), territory_name) {

	_bonus_army_value_ptr = &army_value;
	_color_ptr = &color;
	_territories_ptr = new std::vector<Territory*>();
}

int Continent::get_army_bonus_value() const {
	return *_bonus_army_value_ptr;
}

std::string Continent::to_string() const {

	std::string tmp = "";

	for (Territory* c : get_territories()) tmp += "   " + c->to_string() + "\n";

	return LandMass::to_string() + " | Army Bonus: " + std::to_string(get_army_bonus_value()) + "\n"
		+ tmp;
}

void Continent::verify_claims() {
	Player* claimant = get_territories().front()->get_claimant();

	if (claimant == nullptr) return; // No one claimed continent


	for (Territory* t : get_territories()) {

		if (t == nullptr) return; // Territory wasn't claimed therefore no one claimed continent

		if (claimant != t->get_claimant()) {
			claim(nullptr); // No one conquered the entire continent
			return;
		}
	}

	// Player successful conquered the entire continent
	claim(claimant);
}

void Continent::add_territory(Territory& new_territory) {
	get_territories().push_back(&new_territory);
}

Continent& Continent::operator=(const Continent& other)
{
	if (this != &other) {
		delete _color_ptr;
		delete _bonus_army_value_ptr;
		delete _territories_ptr;
		delete& get_name();
		delete& get_index();

		_bonus_army_value_ptr = new int(other.get_army_bonus_value());
		_color_ptr = new std::string(other.get_color());
		_territories_ptr = &copy(other.get_territories());

		set_index(*new int(other.get_index()));
		set_name(*new std::string(other.get_name()));
		claim(other.get_claimant());
	}

	return *this;
}


std::vector<Territory*>& Continent::get_territories() const {
	return *_territories_ptr;
}

std::string Continent::get_color() const {
	return *_color_ptr;
}

Continent::~Continent() {

	s_territories_index = 0;

	delete _color_ptr;
	delete _bonus_army_value_ptr;
	delete _territories_ptr;
}

std::ostream& operator<<(std::ostream& stream, const Continent& continent) {

	return stream << continent.to_string();
}


/*********** Territory **********/     // aka a country(file)

Territory::Territory() : LandMass() {
	_continent_ptr = nullptr;
	_visited_ptr = nullptr;
	_neighbor_territories_ptr = nullptr;
	_stationed_army_ptr = nullptr;
}

Territory::Territory(const Territory& to_copy) : LandMass(to_copy) {

	_continent_ptr = nullptr;
	_visited_ptr = new bool(to_copy.get_visited());
	_neighbor_territories_ptr = &copy(to_copy.get_neighbors());
	_stationed_army_ptr = new int(to_copy.get_stationed_army());
}

Territory::Territory(int& index, std::string& continent_name) : LandMass(index, continent_name) {

	_continent_ptr = nullptr;
	_visited_ptr = new bool(false);
	_neighbor_territories_ptr = new std::vector<Territory*>();
	_stationed_army_ptr = new int(0);
}

std::vector<Territory*>& Territory::get_neighbors() const {
	return *_neighbor_territories_ptr;
}

void Territory::set_neighbor(Territory& bordered_territory) {
	_neighbor_territories_ptr->push_back(&bordered_territory);
}

std::string Territory::to_string() const {
	std::string tmp = "";

	for (Territory* c : get_neighbors()) 
		tmp += "\t>> [" + std::to_string(c->get_index()) + "] " + c->get_name() + " [Stationed Army: " + std::to_string(c->get_stationed_army()) + "]\n";
	
	return LandMass::to_string() + " [Stationed Army: " + std::to_string(this->get_stationed_army()) + "]\n" + tmp;
}

bool& Territory::get_visited() const {
	return *_visited_ptr;
}

void Territory::set_visited(bool& visited) {

	delete _visited_ptr;
	_visited_ptr = &visited;
}

int& Territory::get_stationed_army() const {
	return *_stationed_army_ptr;
}

void Territory::set_stationed_army(int army) {
	*_stationed_army_ptr = army;
}

void Territory::claim(Player* player, bool verify) {

	LandMass::claim(player);
	
	if(verify) get_parent().verify_claims();
}

// Set parent obj which is a continent
void Territory::set_parent(Continent& parent) {
	_continent_ptr = &parent;
}

Continent& Territory::get_parent() const{
	return *_continent_ptr;
}

Territory& Territory::operator=(const Territory& other) {

	if (this != &other) {
		delete& get_name();
		delete& get_index();
		delete _neighbor_territories_ptr;
		delete _visited_ptr;
		delete _stationed_army_ptr;

		set_name(*new std::string(other.get_name()));
		set_index(*new int(other.get_index()));
		_visited_ptr = new bool(other.get_visited());
		_neighbor_territories_ptr = &copy(other.get_neighbors());
		_stationed_army_ptr = new int(other.get_stationed_army());
		claim(other.get_claimant(), false);
	}

	return *this;
}



Territory::~Territory() {

	delete _neighbor_territories_ptr;
	delete _visited_ptr;
	delete _stationed_army_ptr;
}

std::ostream& operator<<(std::ostream& stream, const Territory& continent) {
	
	return stream << continent.to_string();
}



/*********** LANDMASS ********/

LandMass::LandMass() {
	_claimant_ptr = nullptr;
	_index_ptr = nullptr;
	_name_ptr = nullptr;
}

LandMass::LandMass(const LandMass& to_copy) {

	_claimant_ptr = to_copy.get_claimant();
	_index_ptr = new int(to_copy.get_index());
	_name_ptr = new std::string(to_copy.get_name());
}

LandMass::LandMass(int& index, std::string& landMass_name) {

	_claimant_ptr = nullptr;
	_index_ptr = &index;
	_name_ptr = &landMass_name;
}

void LandMass::claim(Player* player) {
	_claimant_ptr = player;
}

Player* LandMass::get_claimant() const {
	return _claimant_ptr;
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
	return "[" + std::to_string(get_index()) + "] " + this->get_name() + " << CLAIMED BY: " + ((_claimant_ptr == nullptr) ? "N/A" : *_claimant_ptr->getName()) + " >> ";
}

LandMass& LandMass::operator=(const LandMass& other) {

	if (this != &other) {
		delete _index_ptr;
		delete _name_ptr;

		set_index(*new int(other.get_index()));
		set_name(*new std::string(other.get_name()));
		_claimant_ptr = other.get_claimant();
	}


	return *this;
}

LandMass::~LandMass() {

	delete _index_ptr;
	delete _name_ptr;
}


std::ostream& operator << (std::ostream& stream, const LandMass& landMass) {
	
	return stream << landMass.to_string();
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