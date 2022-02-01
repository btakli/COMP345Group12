#pragma once

#include <string>
#include <iostream> // To be removed

class Territory
{

private:
	int _index;
	std::string _name;
	//Player* ?


public:
	Territory() = delete;
	Territory(int index, std::string territory_name);
	~Territory();

	std::string to_string();

	std::string get_name();
	int get_index();

	friend class Continent;
	friend class Country;
};

