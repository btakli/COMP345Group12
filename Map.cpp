#include "Map.h"

Map* Map::_instance = nullptr;

Map::Map() {
	// Empty - see instance
}

Map* Map::get_instance() {
	if (_instance == nullptr) {
		_instance = new Map();
	}
	return _instance;
}

void Map::set_continent(Continent& new_continent) {
	_continents.push_back(&new_continent);
}

void Map::set_country(int continent_index, Country& new_country) {
	for (Continent* continent : _continents) {
		if (continent_index == continent->get_index()) {
			_countries.push_back(&new_country);
			continent->add_country(new_country);
		}
	}
}

void Map::set_border(std::vector<std::string> splited_borders) {

	int curr_country_index = stoi(splited_borders[0]) - 1;

	for (size_t i = 1; i < splited_borders.size(); i++) { // 0 is the current selected country the remainig are its neighbours

		Country* country = get_country(stoi(splited_borders[i]));

		if (country) {
			_countries[curr_country_index]->set_neighbor_country(*country);
		}
		else {
			std::cerr << "ERROR: Country not found: " << curr_country_index << std::endl;
		}
	}
}

bool Map::validate() {

	std::cerr << "NOT IMPLEMENTED" << std::endl;
	return false;
}


void Map::display() {

	if (_continents.size() == 0 && _countries.size() == 0) return;

	std::cout << "-- DISPLAY --\n" << std::endl;

	for (Continent* continent : _continents) {
		std::cout << continent->to_string() << std::endl;
	}

	std::cout << "-- DISPLAY END --\n" << std::endl;

}

Country* Map::get_country(int index) {
	for (Country* c : _countries) {
		if (c->get_index() == index) return c;
	}

	return nullptr;
}

void Map::clear() {

	for (Continent* c : _continents) delete c;
	for (Country* c : _countries) delete c;

	_continents.clear();
	_countries.clear();
}

Map::~Map() {

	delete _instance;
	clear();
}
