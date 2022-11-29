#pragma once
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <functional>

class Graph {
	public:
	    Graph(const std::string& db_fpath);
        float Exports(int exporter, int importer);
	private:
		int countrycodes(int i);
	    std::vector<std::vector<float>> graph;
};