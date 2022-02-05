#include "Country.h"

Country::Country(int index, std::string &country_name) : Territory(index, country_name) {

}

std::list<Country*>& Country::get_bordered_countries() {
	return _neighbor_countries;
}

void Country::set_neighbor_country(Country& bordered_country) {
	_neighbor_countries.push_back(&bordered_country);
}

std::string Country::to_string() {
	std::string tmp = "";

	for (Country* c : _neighbor_countries) tmp += "\t>> " + std::to_string(c->get_index()) + " " + c->get_name() + "\n";

	return Territory::to_string() + "\n" + tmp;
}

Country::~Country() {
	for (Country* c : _neighbor_countries) delete c;
}
