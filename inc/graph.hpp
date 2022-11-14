#include "graph.h"
#include <map>
#include <vector>
#include <string>
#include <fstream>
#define NATION_COUNT 200 // placeholder if we use vectors

// List of Variables :
// t: year
// i: exporter
// j: importer
// k: product
// v: value 
// q: quantity

Graph::Graph(const std::string& db_fpath) {
    std::string line;
	std::ifstream db(db_fpath);
	while(getline(db, line, '\n')) {
		size_t pos;
		std::string token;
		unsigned exporter, importer;
		float productVal;
		unsigned count = 0;
		while((pos = line.find(',')) != std::string::npos) {
			token = line.substr(0, pos);
			if (count != 7 && count != 58) {
				line.erase(0, pos + 1);
				count++;
				continue;
			}
			if(count == 1)
				exporter = stoul(token);
			if(count == 2)
				importer = stoul(token);
            if(count == 4)
                productVal = stof(token);

			line.erase(0, pos + 1);
			count++;	
		}
        if(!graph[exporter].count(importer))
            graph[exporter][importer] = productVal;
        else
            graph[exporter][importer] += productVal;
	}
}
