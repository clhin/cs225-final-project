#pragma once
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <queue>
#include <float.h>
#include <bits/stdc++.h>

class Graph {
	public:
		Graph();
	    Graph(const std::string& db_fpath);
        float Exports(int exporter, int importer);
		std::vector<int> BFS(int start);
		std::vector<float> pagerank(int i);
		std::vector<float> Djikstra(int country_code);
		std::vector<float> TestDjikstra(int country_code, std::vector<std::vector<float>> test_graph);
		std::vector<int> pageranksearch(int country, std::vector<float> rank);
	private:
		int countrycodes(int i);
	    std::vector<std::vector<float>> graph;
};

std::string getCountryName(int index);
std::vector<float> getCountryCoords(int index);
std::vector<std::string> idxVectToString(std::vector<int> countryIdxs);
int stringToIdx(std::string country);
