#include <iostream>
#include "graph.h"
int main() {
	//std::cout << "hello world" << std::endl;
	Graph nations = Graph("BACI_HS17_Y2017_V202201.csv");
    std::cout << nations.Exports(0,7);
	nations.pagerank(100);
}
