#pragma once
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <queue>
#include <bits/stdc++.h>

class Graph {
	public:
	    Graph(const std::string& db_fpath);
        float Exports(int exporter, int importer);
		std::vector<int> BFS(int start);
		std::vector<float> pagerank(int i);
		std::vector<float> Djikstra(int country_code);
		std::vector<float> TestDjikstra(int country_code, std::vector<std::vector<float>> test_graph);
	private:
		int countrycodes(int i);
	    std::vector<std::vector<float>> graph;
};
