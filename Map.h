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

class Territory
{
private:
	int* _index_ptr;
	std::string* _name_ptr;
	Player* _player_ptr;

public:
	Territory() = delete;
	Territory(int& index, std::string& territory_name);
	~Territory();

	std::string to_string(); // Display obj as string

	void claim(Player& player); // To claim a Country or Continent
	Player* check_claim(); // Check who owns the Country or Continent

	std::string get_name() const; // Get name
	int get_index() const; // Get index
};


class Continent : public Territory
{
	static int _continent_index;

	std::string* _color_ptr;
	int* _army_value_ptr;
	std::list<Country*>* _countries;

private:
	Continent() = delete;

public:

	Continent(std::string& continent_name, int& army_value, std::string& color);
	~Continent();

	int get_army_value(); // Get army value
	std::string get_color(); // Get color 
	std::string to_string(); // Display obj as string
	std::list<Country*>& get_countries(); // Return countries on continent

	void add_country(Country& new_country);
};


class Country : public Territory
{
private:
	Country() = delete;

	std::list<Country*>* _neighbor_countries;
	bool* _visited_ptr; // Used for Map's validation check
	int* _army;

public:

	Country(int& index, std::string& country_name);
	~Country();

	std::list<Country*>& get_neighbors(); // Returns a reference to the list of neighbors
	void set_neighbor(Country& bordered_country); // Add a new neighbor 
	bool& get_visited(); // Check is visited
	void set_visited(bool& visited); // Set visited
	int& get_stationed_army(); // Get the number of soldier stationed in this Country
	void set_stationed_army(int& army); // Set the numer of soldier stationed in this Country
	std::string to_string(); // Display obj as string
};


class MapLoader
{
	enum class FileBlock { None, Files, Continents, Borders, Countries };

	static MapLoader* _instance;

public:
	~MapLoader();

	void load_map(std::string map_file_name); // Use this function to load a map
	static MapLoader* get_instance();

private:
	MapLoader();

	std::vector<std::string> split(std::string& line) const;

	bool verify(std::string map_file_name);

	void sort_map_file_data(FileBlock& fileBlock, std::string& line); // File data spliter // Please don't call
	void make_continent(std::vector<std::string> splited_line); // Please don't call
	void make_countries(std::vector<std::string> splited_line); // Please don't call
	void assign_borders(std::vector<std::string> splited_line); // Please don't call
	bool is_number(std::string& str); // Please don't call
};


class Map
{
	static Map* _instance;
	std::list<Continent*>* _continents;
	std::vector<Country*>* _countries;

private:
	Map();
	bool help_validate(std::queue<Country*>& visited_countries, int& size, int& count); // // Please don't call, helper function for the validate method


public:
	~Map();

	static Map* get_instance();
	bool validate(); // Checks if loaded map is valid
	void display(); // Displays the Map obj
	void set_continent(Continent& new_continent); // Add a new continent
	void set_country(int& continent_index, Country& new_country); // Add a new country
	void set_border(std::vector<std::string> splited_borders); // Add a new neighbor to a country
	Country* get_country(int index); // Get a country by index
	std::vector<Country*>& get_countries(); // Get all countries
	std::list<Continent*>& get_continents(); // Get all continents

	void unload(); // Clears all data on instance
};



