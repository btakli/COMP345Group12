#pragma once


#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <list>

#include "Player.h"

class Territory;
class Continent;
class Country;
class Map;
class MapLoader;
class Player;

template <typename T>
std::list<T*>& copy(std::list<T*> to_copy);

template <typename T>
std::vector<T*>& copy(std::vector<T*> to_copy);

class Territory
{

	int* _index_ptr;
	std::string* _name_ptr;

private:
	void set_index(int& new_index);
	void set_name(std::string& new_name);

public:
	Territory() = delete; // Prevent accidental use

	//Copy constructor - !!!Don't use unless really necessary - cause dupe index
	Territory(const Territory& to_copy);

	Territory(int& index, std::string& territory_name);
	~Territory();

	std::string to_string() const; // Display obj as string



	std::string& get_name() const;
	int& get_index() const;

	Territory& operator=(const Territory& territory);

	friend std::ostream& operator << (std::ostream& stream, const Territory& territory);

	friend class Country;
	friend class Continent;
};


class Continent : public Territory
{
	static int _continent_index;

	std::string* _color_ptr;
	int* _army_value_ptr;
	std::list<Country*>* _countries_ptr;

private:
	Continent() = delete; // Prevent accidental use 

public:
	//Copy constructor. !!!Don't use unless really necessary - cause dupe index
	Continent(const Continent& to_copy);

	Continent(std::string& continent_name, int& army_value, std::string& color);
	~Continent();

	int get_army_value() const;
	std::string get_color() const;
	std::string to_string() const;
	std::list<Country*>& get_countries() const;

	void add_country(Country& new_country);

	Continent& operator=(const Continent& continent);

	friend std::ostream& operator<<(std::ostream& stream, const Continent& continent);
};



class Country : public Territory
{
private:
	Country() = delete; //Prevents wrong call

	std::list<Country*>* _neighbor_countries_ptr;
	bool* _visited_ptr; // Used for Map's validation check
	int* _stationed_army_ptr;
	Player* _player_ptr;

public:

	//Copy constructor - !!!Don't use unless really necessary - cause dupe index
	Country(const Country& to_copy);


	Country(int& index, std::string& country_name);
	~Country();

	std::list<Country*>& get_neighbors() const; // Returns a reference to the list of neighbors
	void set_neighbor(Country& bordered_country); // Add a new neighbor 

	// Claim a country
	void claim(Player& player);

	// Check who owns the country. returns player or null
	Player* check_claim() const;


	// Check is visited
	bool& get_visited() const;
	void set_visited(bool& visited);
	int& get_stationed_army() const;
	void set_stationed_army(int& army);
	std::string to_string() const;

	Country& operator=(const Country& country);

	friend std::ostream& operator<<(std::ostream& stream, const Country& country);
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

	void make_continent(std::vector<std::string>& splited_line);
	void make_countries(std::vector<std::string>& splited_line);
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
	std::list<Continent*>* _continents_ptr;
	std::vector<Country*>* _countries_ptr;

private:
	Map();

	bool help_validate(std::queue<Country*>& visited_countries, int& size, int& count);

public:
	~Map();

	static Map* get_instance();

	// Checks if loaded map is valid; return: valid=true; invalid=false;
	bool validate();

	void display() const; // Displays the Map obj
	void set_continent(Continent& new_continent); // Add a new continent
	void set_country(int& continent_index, Country& new_country); // Add a new country
	void set_border(std::vector<std::string> splited_borders); // Add a new neighbor to a country
	Country* get_country(int index); // Get a country by index
	std::vector<Country*>& get_countries() const; // Get all countries
	std::list<Continent*>& get_continents() const; // Get all continents

	//Copy constructor. !!!Don't use unless really necessary
	Map(const Map& to_copy);

	void unload(); // Clears all data on instance

	Map& operator=(const Map& map);

	friend std::ostream& operator<<(std::ostream& stream, const Map& map); // Stream insertion 
};


