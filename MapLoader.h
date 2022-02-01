#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

#include "Continent.h"
#include "Map.h"

#define CONTINENTS "[continents]"
#define COUNTRIES "[countries]"
#define BORDERS "[borders]"

class MapLoader
{
	enum class FileBlock { None, Files, Continents, Borders, Countries };

	static MapLoader *_instance;

public:
	~MapLoader();

	void load_map(std::string map_file_name);
	static MapLoader* get_instance();

private:
	MapLoader();

	std::vector<std::string> split(std::string &line) const;

	bool verify(std::string map_file_name);

	void sort_map_file_data(FileBlock &fileBlock, std::string &line);
	void make_continent(std::vector<std::string> splited_line);
	void make_countries(std::vector<std::string> splited_line);
	void assign_borders(std::vector<std::string> splited_line);
};

