#pragma once
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <functional>

class Graph {
	public:
	    Graph(const std::string& db_fpath);
            //std::vector<std::vector<float > > graph;
	private:
            int countrycodes(int i);
	    std::vector<std::vector<float>> graph;
};