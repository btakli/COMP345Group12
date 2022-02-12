#include <iostream>

#include "Map.h"

#define BERLIN "berlin"
#define CANADA "canada"
#define COW "cow"
#define ESTONIA "estonia"
#define FORTERESS "fortress"
#define INVALID1 "invalid1"
#define INVALID2 "invalid2"
#define INVALID3 "invalid3"

#define UPPERLIMIT 10

//Test stream insertion, copy constructor
void test_assignment();

//Test stream insertion, assignment operator
void test_copy();

int main() {

	bool run = true;

	while (run) {
		bool error = false;
		try {
			int option;
			do {
				std::cout << "Please choose from 0 to " << UPPERLIMIT << "." << std::endl;

				std::cin >> option;

				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					option = -1;
				}
			} while (option > UPPERLIMIT || option < 0);

			system("cls");

			std::cout << "-- OPTION " << option << " --\n\n" << std::endl;

			switch (option)
			{
			case 1:
				MapLoader::get_instance()->load_map(BERLIN);
				break;

			case 2:
				MapLoader::get_instance()->load_map(CANADA);
				break;

			case 3:
				MapLoader::get_instance()->load_map(COW);
				break;

			case 4:
				MapLoader::get_instance()->load_map(ESTONIA);
				break;

			case 5:
				MapLoader::get_instance()->load_map(FORTERESS);
				break;

			case 6:
				MapLoader::get_instance()->load_map(INVALID1);
				break;

			case 7:
				MapLoader::get_instance()->load_map(INVALID2);
				break;

			case 8:
				test_assignment();
				break;

			case 9:
				test_copy();
				break;

			case 10:
				MapLoader::get_instance()->load_map(INVALID3);
				break;

			case 0:
				run = false;
				break;
			}
		}
		catch (std::runtime_error e) {
			std::cout << "ERROR: " << e.what() << std::endl;
			error = true;
		}

		if (run && !error) {
			std::cout << *Map::get_instance();
			Map::get_instance()->validate();
		}
		Map::get_instance()->unload();
		
	}

	return 0;
}

//Test stream insertion, copy constructor
void test_copy() {

	//Copy
	MapLoader* loader_copy(MapLoader::get_instance());
	loader_copy->load_map(CANADA);

	Map* map_instance_copy(Map::get_instance());
	Continent continent_copy(*map_instance_copy->get_continent(1));
	LandMass landMass_copy(*map_instance_copy->get_continent(1));
	Territory territory_copy(*map_instance_copy->get_territories().front());

	// Stream insertion of copy
	std::cout << "-- COPY --" << std::endl;
	std::cout << "MapLoader:\t" << *loader_copy->get_instance() << std::endl;
	std::cout << "Map:\t" << *map_instance_copy->get_instance() << std::endl;
	std::cout << "Continent:\t" << continent_copy << std::endl;
	std::cout << "Landmass:\t" << landMass_copy << std::endl;
	std::cout << "Territory:\t" << territory_copy << std::endl;
}

//Test stream insertion, assignment operator
void test_assignment() { 


	//Assignement
	MapLoader* loader_assign = MapLoader::get_instance();
	loader_assign->load_map(CANADA);

	Map* map_assign = Map::get_instance();

	Continent continent_assign = (*map_assign->get_continent(1));
	LandMass landMass_assign = (*map_assign->get_continent(1));
	Territory territory_assign = (*map_assign->get_territories().front());


	// Stream insertion of assignment
	std::cout << "-- ASSIGNMENT --" << std::endl;
	std::cout << "MapLoader:\t" << *loader_assign->get_instance() << std::endl;
	std::cout << "Map:\t" << *map_assign->get_instance() << std::endl;
	std::cout << "Continent:\t" << continent_assign << std::endl;
	std::cout << "Landmass:\t" << landMass_assign << std::endl;
	std::cout << "Territory:\t" << territory_assign << std::endl;
}