#pragma once


#include <list>
#include <vector>
#include "Continent.h"

class Map
{
	static Map *_instance; // TODO: transform it to an object instead of instance
	std::list<Continent*> _continents;
	std::vector<Country*> _countries;

private:
	Map();

public:
	~Map();

	static Map *get_instance();
	bool validate();
	void display();
	void set_continent(Continent& new_continent);
	void set_country(int continent_index, Country& new_country);
	void set_border(std::vector<std::string> splited_borders);
	Country* get_country(int index);

	void clear(); // Clears all data on instance
};

