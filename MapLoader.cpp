#include "MapLoader.h"

MapLoader* MapLoader::_instance = nullptr;


MapLoader::MapLoader() {
	// Empty - see instance
}

void MapLoader::load_map(std::string map_file_name){

	if (!verify(map_file_name)) return; // Map fails basic verifications

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

			if(read_block != FileBlock::None) sort_map_file_data(read_block, line);
 		}
	}
	else {
		throw std::runtime_error("ERROR: Fail to open file @loading map: " + map_file_name);
	} 
}

void MapLoader::sort_map_file_data(FileBlock &fileBlock, std::string &line)  {

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
		throw std::runtime_error("ERROR: Unkown file block. Please reformat file.");
	}
}

MapLoader* MapLoader::get_instance() {
	if (_instance == nullptr) {
		_instance = new MapLoader();
	}
	return _instance;
}


std::vector<std::string> MapLoader::split(std::string &line) const {
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

void MapLoader::make_continent(std::vector<std::string> line_tokens) { //TODO: Needs to check if data types are correcte, if not Map clears + throw

	std::string continent_name = line_tokens[0];
	std::string color = line_tokens[2];

	Continent* new_continent = new Continent(continent_name, stoi(line_tokens[1]), color);
	Map::get_instance()->set_continent(*new_continent);
}

void MapLoader::make_countries(std::vector<std::string> line_tokens) { //TODO: Needs to check if data types are correcte, if not Map clears + throw

	std::string country_name = line_tokens[1];

	Country* new_country = new Country(stoi(line_tokens[0]), country_name);
	Map::get_instance()->set_country(stoi(line_tokens[2]), *new_country);
}

void MapLoader::assign_borders(std::vector<std::string> line_tokens) { //TODO: Needs to check if data types are correcte, if not Map clears + throw
	Map::get_instance()->set_border(line_tokens);
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
			throw std::runtime_error("ERROR: File format is not respected.");
		}
	}
	else {
		throw std::runtime_error("ERROR: Fail to open file @file format verifier: " + map_file_name);
	}
}

MapLoader::~MapLoader() {
	delete _instance;
}