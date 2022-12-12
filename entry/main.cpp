#include <iostream>
#include "graph.h"
int main() {
	//std::cout << "hello world" << std::endl;
	Graph nations = Graph("BACI_HS17_Y2020_V202201.csv");
    std::cout << nations.Exports(0,7);
	auto rank = nations.pagerank(100);

	auto test = nations.pageranksearch(1,rank);
	nations.pageranksearch(5,rank);
	nations.pageranksearch(10,rank);

	std::cout << test.size();
}
