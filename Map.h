#pragma once


#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <list>

#include "Player.h"

class LandMass;
class Territory;
class Continent;
class Map;
class MapLoader;
class Player;

template <typename T>
std::list<T*>& copy(std::list<T*> to_copy);

template <typename T>
std::vector<T*>& copy(std::vector<T*> to_copy);

class LandMass
{

	int* _index_ptr;
	std::string* _name_ptr;

private:
	void set_index(int& new_index);
	void set_name(std::string& new_name);

public:
	LandMass() = delete; // Prevent accidental use

	//Copy constructor - !!!Don't use unless really necessary - cause dupe index
	LandMass(const LandMass& to_copy);

	LandMass(int& index, std::string& landMass_name);
	~LandMass();

	std::string to_string() const; // Return obj as string

	

	std::string& get_name() const;
	int& get_index() const;

	LandMass& operator=(const LandMass& territory);

	friend std::ostream& operator << (std::ostream& stream, const LandMass& land_mass);

	friend class Continent;
	friend class Territory;
};


class Territory : public LandMass
{
	static int _territories_index;

	std::string* _color_ptr;
	int* _army_value_ptr;
	std::list<Continent*>* _continents_ptr;

private:
	Territory() = delete; // Prevent accidental use 

public:
	//Copy constructor. !!!Don't use unless really necessary - cause dupe index
	Territory(const Territory& to_copy);

	Territory(std::string& territory_name, int& army_value, std::string& color);
	~Territory();

	int get_army_value() const;
	std::string get_color() const;
	std::string to_string() const;
	std::list<Continent*>& get_continents() const;

	void add_continent(Continent& new_continent);

	Territory& operator=(const Territory& territory);

	friend std::ostream& operator<<(std::ostream& stream, const Territory& territory);
};



class Continent : public LandMass
{
private:
	Continent() = delete; //Prevents accidental use

	std::list<Continent*>* _neighbor_continents_ptr;
	bool* _visited_ptr; // Used for Map's validation check
	int* _stationed_army_ptr;
	Player* _player_ptr;

public:

	//Copy constructor - !!!Don't use unless really necessary - cause dupe index
	Continent(const Continent& to_copy);


	Continent(int& index, std::string& continent_name);
	~Continent();

	std::list<Continent*>& get_neighbors() const; // Returns a reference to the list of neighbors
	void set_neighbor(Continent& bordered_continent); // Add a new neighbor 

	// Claim a continent
	void claim(Player& player);

	// Check who owns the continent. returns player or null
	Player* check_claim() const;


	// Check is visited
	bool& get_visited() const;
	void set_visited(bool& visited);
	int& get_stationed_army() const;
	void set_stationed_army(int& army);
	std::string to_string() const;

	Continent& operator=(const Continent& continent);

	friend std::ostream& operator<<(std::ostream& stream, const Continent& continent);
};


class MapLoader
{
	enum class FileBlock { None, Files, Continents, Borders, Countries };

	static MapLoader* _instance_ptr;

private:
	MapLoader();

	//Splits read line into a vector.
	std::vector<std::string>& split(std::string& line) const;

	//Checks if a .map file is valid. return: valid=true; invalid=false;
	bool verify(std::string map_file_name);

	//Helper to sort out which obj needs to be created.
	void sort_map_file_data(FileBlock& fileBlock, std::string& line);

	void make_territory(std::vector<std::string>& splited_line);
	void make_continent(std::vector<std::string>& splited_line);
	void assign_borders(std::vector<std::string>& splited_line);

	//Check is string is a number
	bool is_number(std::string& str);


public:

	//Copy constructor. !!!Don't use unless really necessary
	MapLoader(const MapLoader& to_copy);

	~MapLoader();

	void load_map(std::string map_file_name);
	static MapLoader* get_instance();

	MapLoader& operator=(const MapLoader& loader);

	friend std::ostream& operator<<(std::ostream& stream, const MapLoader& loader);
};


class Map
{
	static Map* _instance_ptr;
	std::list<Territory*>* _territories_ptr;
	std::vector<Continent*>* _continents_ptr;

private:
	Map();

	bool help_validate(std::queue<Continent*>& to_be_visited_continents, int& size, int& count);

public:
	~Map();

	static Map* get_instance();

	// Checks if loaded map is valid; return: valid=true; invalid=false;
	bool validate();

	void display() const; // Displays the Map obj
	void set_territory(Territory& new_territory); // Add a new continent
	void set_continent(int& continent_index, Continent& new_continent); // Add a new continent
	void set_border(std::vector<std::string> splited_borders); // Add a new neighbor to a continent
	Continent* get_continent(int index); // Get a continent by index
	std::vector<Continent*>& get_continents() const; // Get all continents
	std::list<Territory*>& get_territories() const; // Get all territories

	//Copy constructor. !!!Don't use unless really necessary
	Map(const Map& to_copy);

	void unload(); // Clears all data on instance

	Map& operator=(const Map& map);

	friend std::ostream& operator<<(std::ostream& stream, const Map& map); // Stream insertion 
};


