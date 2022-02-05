#pragma once

#include <list>
#include "Territory.h"

class Country : public Territory
{
private:
	Country() = delete;

	std::list<Country*> _neighbor_countries;

public:
	
	Country(int index, std::string &country_name);
	~Country();

	std::list<Country*>& get_bordered_countries();
	void set_neighbor_country(Country& bordered_country);
	std::string to_string();
};

