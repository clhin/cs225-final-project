#pragma once
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <functional>

class Graph {
	public:
	    Graph(const string& db_fpath);
        //if we use vectors, use this
        // class Pair{
        // public:
        //     unsigned nationCode;
        //     unsigned importAmmt;
        //     Pair(unsigned nationCodeIn, unsigned importAmmtIn){
        //         nationCode = nationCodeIn;
        //         importAmmt = importAmmtIn;
        //     }
        // };
	private:
	    std::map<std::map<float>> graph;
};