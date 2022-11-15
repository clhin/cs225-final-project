#include <iostream>
#include "graph.hpp"
int main() {
	//std::cout << "hello world" << std::endl;
	Graph nations = Graph("BACI_HS17_Y2020_V202201.csv");
    std::cout << nations.graph[0][7];
}
