#pragma once
#include "countries.h"
#include <vector>
#include <string>
#include <fstream>
#include <functional>

class Graph {
	public:
	Graph(const std::string&);
	private:
	std::vector<std::vector<int>> graph;
	int countrycodes(int);
	int terrorcodes(std::string);
};
