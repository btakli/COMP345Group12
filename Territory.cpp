#include "Territory.h"


Territory::Territory(int index, std::string territory_name) {
	_index = index;
	_name = territory_name;
}


std::string Territory::get_name() {
	return _name;
}

int Territory::get_index() {
	return _index;
}

std::string Territory::to_string() {
	return "[" +std::to_string(_index) + "] " + _name;
}

Territory::~Territory() {

}