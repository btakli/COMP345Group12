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

// Returns a copy of T as list
template <typename T>
std::list<T*>& copy(std::list<T*> to_copy);

// Returns a copy of T as vector
template <typename T>
std::vector<T*>& copy(std::vector<T*> to_copy);

class LandMass
{
	int* _index_ptr;
	std::string* _name_ptr;
	Player* _claimant_ptr;

protected:


	// Set a new index
	void set_index(int& new_index);
	
	// Set a new name
	void set_name(std::string& new_name);

public:

	// Constructor
	LandMass(); 

	// Copy constructor - !!!Don't use unless really necessary - cause dupe index
	LandMass(const LandMass& to_copy);

	// Custom constuctor
	LandMass(int& index, std::string& landMass_name);
	
	// Destructor
	~LandMass();

	// Claim a land mass
	void claim(Player& player);

	// Check who owns the land mass. returns player or null
	Player* get_claimant() const;

	// Return obj as string
	std::string to_string() const; 
	
	// Get name. return: string name
	std::string& get_name() const;

	// Get index. return: int index
	int& get_index() const;

	// Assignment operator. DO NOT USE.
	LandMass& operator=(const LandMass& territory);

	// Stream insertion.
	friend std::ostream& operator << (std::ostream& stream, const LandMass& land_mass);
};


class Territory : public LandMass
{
	static int s_territories_index;

	std::string* _color_ptr;
	int* _army_value_ptr;
	std::list<Continent*>* _continents_ptr;



private:
	// Constructor deleted. Prevent accidental use
	Territory() = delete;

public:

	// Copy constructor. !!!Don't use unless really necessary - cause dupe index
	Territory(const Territory& to_copy);

	// Custom constructor
	Territory(std::string& territory_name, int& army_value, std::string& color);
	
	// Destructor
	~Territory();

	// Get army value. return an int
	int get_army_value() const;

	// Get color. return a string representing the color of this territory
	std::string get_color() const;
	
	// Obj to string
	std::string to_string() const;

	// Get continent. return an address to list of continent pointers
	std::list<Continent*>& get_continents() const;

	// Add a continent
	void add_continent(Continent& new_continent);

	// Assignment operator. DO NOT USE
	Territory& operator=(const Territory& territory);

	// Stream insertion
	friend std::ostream& operator<<(std::ostream& stream, const Territory& territory);
};



class Continent : public LandMass
{
	std::list<Continent*>* _neighbor_continents_ptr;
	bool* _visited_ptr; // Used for Map's validation check
	int* _stationed_army_ptr;

private:

	// Check is visited
	bool& get_visited() const;

	// Set visited. 
	void set_visited(bool& visited);

public:

	// Constructor
	Continent(); 

	// Copy constructor - !!!Don't use unless really necessary - cause dupe index
	Continent(const Continent& to_copy);

	// Custom constructor
	Continent(int& index, std::string& continent_name);

	// Destructor
	~Continent();

	// Returns a reference to the list of neighbors
	std::list<Continent*>& get_neighbors() const; 

	// Add a new neighbor 
	void set_neighbor(Continent& bordered_continent); 

	// Return number of station army as int.
	int& get_stationed_army() const;
	
	// Set new stationed army
	void set_stationed_army(int& army);

	// Obj to string
	std::string to_string() const;

	// Assignment operator. DO NOT USE
	Continent& operator=(const Continent& continent);

	// Stream insertion
	friend std::ostream& operator<<(std::ostream& stream, const Continent& continent);

	friend class Map;
};


class MapLoader
{
	enum class FileBlock { None, Files, Continents, Borders, Countries };

	static MapLoader* _instance_ptr;

private:

	// Constructor
	MapLoader();

	// Splits read line into a vector.
	std::vector<std::string>& split(std::string& line) const;

	// Checks if a .map file is valid. return: valid=true; invalid=false;
	bool verify(std::string map_file_name);

	// Helper to sort out which obj needs to be created.
	void sort_map_file_data(FileBlock& fileBlock, std::string& line);

	// Make a new territory
	void make_territory(std::vector<std::string>& splited_line);

	// Make a new continent
	void make_continent(std::vector<std::string>& splited_line);

	// Assigne borders to continent
	void assign_borders(std::vector<std::string>& splited_line);

	// Check if string is a number
	bool is_number(std::string& str);

public:

	//Copy constructor. !!!Don't use unless really necessary
	MapLoader(const MapLoader& to_copy);

	// Destructor
	~MapLoader();

	// Load a new map
	void load_map(std::string map_file_name);

	// Return mapLoader instance
	static MapLoader* get_instance();

	// Assignment operator. DO NOT USE
	MapLoader& operator=(const MapLoader& loader);

	// Stream insertion
	friend std::ostream& operator<<(std::ostream& stream, const MapLoader& loader);
};


class Map
{
	static Map* _instance_ptr;
	std::list<Territory*>* _territories_ptr;
	std::vector<Continent*>* _continents_ptr;

private:

	// Constructor
	Map();

	// Helper function for validate()
	bool help_validate(std::queue<Continent*>& to_be_visited_continents,  Continent& prev,  int& size, int& count);

	// Add a new continent
	void set_territory(Territory& new_territory);

	// Add a new continent
	void set_continent(int& continent_index, Continent& new_continent);

	// Add a new neighbor to a continent
	void set_border(std::vector<std::string> splited_borders);

public:

	// Destructor
	~Map();

	// Return map instance
	static Map* get_instance();

	// Checks if loaded map is valid; return: valid=true; invalid=false;
	bool validate();

	// Displays the Map obj
	void display() const; 

	// Get a continent by index. Return pointer ref to that continent or null
	Continent* get_continent(int index); 

	// Get all continents. Return ref to vector of continents*
	std::vector<Continent*>& get_continents() const; 

	// Get all territories. Return ref to list of territories*
	std::list<Territory*>& get_territories() const; 

	//Copy constructor. !!!Don't use unless really necessary
	Map(const Map& to_copy);

	// Clears all data on instance
	void unload(); 

	// Assignment operator. DO NOT USE
	Map& operator=(const Map& map);

	// Stream insertion 
	friend std::ostream& operator<<(std::ostream& stream, const Map& map); 

	friend class MapLoader;
};


