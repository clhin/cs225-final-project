#include <iostream>
#include <vector>
#include <algorithm>
#include "graph.h"

int main() {

	Graph nations = Graph("../BACI_HS17_Y2020_V202201.csv");

	std::string countryIn;
	std::cout<<"Enter the name of a country, Example: Australia"<<std::endl;
	std::cin>>countryIn;

	int countryIdx = stringToIdx(countryIn);

	//only runs with valid input
	if(countryIdx != -1){
		//BFS terminal output, outputs BFS starting at input node as strings
		std::vector<int> bfsout = nations.BFS(countryIdx);
		std::vector<std::string> bfsString = idxVectToString(bfsout);

		std::cout<<"BFS Traversal Starting at "<< countryIn<< ":"<<std::endl;

		for(unsigned i = 0; i < bfsString.size(); i++){
			std::cout<<bfsString[i]<< ", ";
			if(i % 10 == 0 && i != 0)
				std::cout<<std::endl;
		}
		std::cout<<std::endl<<std::endl;

		//page rank terminal output, outputs top three ranked nations that trade with input as strings
		std::vector<float> pagerankout = nations.pagerank(100);
		std::vector<int> importantPartners = nations.pageranksearch(countryIdx, pagerankout);
		std::vector<std::string> importantPartnersString = idxVectToString(importantPartners);

		std::cout<<countryIn<<"'s Three Most Important Trade Partners Ranked by Page Rank: "<< importantPartnersString[0]<<", "<<importantPartnersString[1]<<", "<<importantPartnersString[2]<<std::endl<<std::endl;


		//terminal interface for Djikstra that compares the price of trading with two nations with the input nation
		std::vector<float> DjikstraOut = nations.Djikstra(countryIdx);
		std::string compare1, compare2;
		std::cout<<"Enter two naitons to compare trading costs with the input nation, where the trading cost is determined using Djikstra's Algorithm \nto find the shortest path between two nations where the weight of the path is defined by the inverse of trade\nvolume, this approximates the price of trade as Economies of Scale make the prices of trade lower where there is more trade\n";
		std::cout<<"Enter the First Nation to Compare, Example: Mongolia\n";
		std::cin>>compare1;
		std::cout<<"Enter the First Nation to Compare, Example: Japan \n";
		std::cin>>compare2;

		int compare1Idx = stringToIdx(compare1);
		int compare2Idx = stringToIdx(compare2);
		
		//checks if inputs are valid before comparison
		if(compare1Idx != -1 && compare2Idx != -1){
			if(DjikstraOut[compare1Idx] < DjikstraOut[compare2Idx])
				std::cout<<"It is Cheaper to Trade with "<<compare1<<std::endl;
			else if(DjikstraOut[compare1Idx] > DjikstraOut[compare2Idx])
				std::cout<<"It is Cheaper to Trade with "<<compare2<<std::endl;
			else
				std::cout<<"The Price of trading with both nations is the same"<<std::endl;
		}
		//invalid input message
		else
			std::cout<<"Invalid Inputs"<<std::endl;


	}
	//invalid country message
	else
		std::cout<<"Not a Valid Country"<<std::endl;

	return 0;
}


