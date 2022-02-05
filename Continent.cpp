#include "Continent.h"

int Continent::_continent_index = 0;

Continent::Continent(std::string continent_name, int army_value, std::string color) : Territory(++_continent_index, continent_name) {

	_army_value = army_value;
	_color = color;
}


int Continent::get_index() {
	return Territory::_index;
}

int Continent::get_army_value() {
	return _army_value;
}

std::string Continent::to_string() {

	std::string tmp = "";

	for (Country* c : _countries) tmp += "   " + c->to_string() + "\n";

	return Territory::to_string() + " | Army: " + std::to_string(_army_value) + " | " + _color + "\n"
		+ tmp;
}

void Continent::add_country(Country& new_country) {
	_countries.push_back(&new_country);
}

std::string Continent::get_color() {
	return _color;
}

Continent::~Continent() {
	for (Country* c : _countries) delete c;
}