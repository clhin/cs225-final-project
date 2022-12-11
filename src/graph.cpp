#include "graph.h"
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

// List of Variables :
// t: year
// i: exporter
// j: importer
// k: product
// v: value 
// q: quantity

Graph::Graph() { //Used purely for testing purposes since hard to test and interpert with very large graph 
	return;
}

//Takes csv file input of the trade data and constructs the vector of vectors graph; an adjacency matrix
Graph::Graph(const std::string& db_fpath) {
	for (uint x = 0; x <= 237; x++) {
		std::vector<float> tmpvect;
		for (uint y = 0; y <= 237; y++) {
			tmpvect.push_back(0);
		}
		graph.push_back(tmpvect);
	}
	int lineCount = 0;
    std::string line;
	std::ifstream db(db_fpath);
	while(getline(db, line, '\n')) {
		size_t pos;
		std::string token;
		int exporter, importer;
		float productVal;
		unsigned count = 0;
		while((pos = line.find(',')) != std::string::npos) {
			token = line.substr(0, pos);
			if (count != 1 && count != 2 && count != 4) {
				line.erase(0, pos + 1);
				count++;
				continue;
			}
			if(lineCount != 0){
				if(count == 1)
					exporter = countrycodes(std::stoi(token));
				if(count == 2)
					importer = countrycodes(std::stoi(token));
            	if(count == 4)
            		productVal = std::stof(token);
			}

			line.erase(0, pos + 1);
			count++;	
		}
		if(lineCount != 0)
			graph[exporter][importer] += productVal;
		lineCount++;
	}
}

float Graph::Exports(int exporter, int importer){
	int normExporter = countrycodes(exporter);
	int normImporter = countrycodes(importer);
	if (normExporter == -1 || normImporter == -1)
		return -1;
	return graph[normExporter][normImporter];
}

/* A function that runs a BFS traversal of the graph starting from a given start point.
Inputs: The starting country code, given as an int
Outputs: A vector containing the BFS traversal order of the graph, full of country codes.
*/
std::vector<int> Graph::BFS(int start){
	std::queue<int> bfsq; //queue to keep track of the traversal.
	bfsq.push(start); //loading the queue with the first point.

	std::vector<int> traversal;//vector that contains the traversal history.

	std::vector<bool> visited(graph.size(), false); //vector that keeps track of the history of points visited.
	visited[start] = true; //marking the first point as visited.

	while(!bfsq.empty()){ //loop that traverses every point, marking each as visited, and saving the order in the traversal vector.
		int curr = bfsq.front();
		bfsq.pop();
		traversal.push_back(curr);

		for(unsigned long i = 0; i < graph[curr].size(); i++){
			if(!visited[i]){
				if(graph[curr][i] != 0){
					bfsq.push(i);
					visited[i] = true;
				}
			}
		}
	}
	return traversal;
}
//Given a country code, returns the approximate trade price to all other countries represented in a vector. We assume that trade price is inversly proptional to dollar amount of exports between countries
std::vector<float> Graph::Djikstra(int idx) { 
	std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> inverse_pq;
	int key_row = idx; //Gets the row we need to go to on matrix based on country code passed
	std::vector<float>vect_dist;
	inverse_pq.push({0,key_row}); //Start off by adding dist of 0 as well as our start node represented as index to priority que
	for (size_t x = 0; x < graph.size(); x++) { //Set all distances to maximum value in C++
		vect_dist.push_back(FLT_MAX); //Included in .h file
	}
	vect_dist[key_row] = 0; //Set dist at start (key_row for now to 0)
	while(!inverse_pq.empty()) {
		float dist = inverse_pq.top().first;
		int node = inverse_pq.top().second;
		key_row = node;
		for (size_t col = 0; col < graph[0].size(); col++) { //Based on what node (or row we have to go to on matrix), iiterate across row
			if (graph[key_row][col] != 0 && ((1/graph[key_row][col]) + dist) < vect_dist[col]) { //As we itterate ensure that val isn't 0 and dist calculated to go that node < what's currently present
				vect_dist[col] = 1/graph[key_row][col] + dist; //update the distance
				inverse_pq.push({vect_dist[col], col});
			}
		}
		inverse_pq.pop(); //remove top elemnt
	}
	return vect_dist;
}

std::vector<float> Graph::TestDjikstra(int idx, std::vector<std::vector<float>> test_graph) { //Used purely for testing purposes since hard to test + interpert on large graph
	std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> inverse_pq;
	int key_row = idx; //Gets the row we need to go to on matrix based on country code passed
	std::vector<float>vect_dist;
	inverse_pq.push({0,key_row}); //Start off by adding dist of 0 as well as our start node represented as index to priority que
	for (size_t x = 0; x < test_graph.size(); x++) { //Set all distances to maximum value in C++
		vect_dist.push_back(FLT_MAX); //Included in .h file
	}
	vect_dist[key_row] = 0; //Set dist at start (key_row for now to 0)
	while(!inverse_pq.empty()) {
		float dist = inverse_pq.top().first;
		key_row = inverse_pq.top().second;
		for (size_t col = 0; col < test_graph[0].size(); col++) { //Based on what node (or row we have to go to on matrix), iiterate across row
			if (test_graph[key_row][col] != 0 && ((1/test_graph[key_row][col]) + dist) < vect_dist[col]) { //As we itterate ensure that val isn't 0 and dist calculated to go that node < what's currently present
				vect_dist[col] = 1/test_graph[key_row][col] + dist; //update the distance
				inverse_pq.push({vect_dist[col], col});
			}
		}
		inverse_pq.pop(); //remove top elemnt
	}
	return vect_dist;
}


std::vector<float> Graph::pagerank(int iterations) {
	double dampeningfactor = 0.82;
	int size = graph.size();
	std::vector<float> currentpagerank, inlinks(size, 0), outlinks(size, 0);
	for (uint row = 0; row < graph.size(); row++) {
		for (uint col = 0; col < graph.at(row).size(); col++) {
			if (graph.at(row).at(col) != 0) {
				outlinks.at(row)++;
				inlinks.at(col)++;
			}
		}
	}
	for (uint row = 0; row < graph.size(); row++) {
			currentpagerank.push_back(1/size);
	}
	while (iterations > 0) {
		float rank = 0;
		std::vector<float> newpagerank(currentpagerank.size(), 0);
		for (uint i = 0; i < outlinks.size(); i++) {
			if (outlinks.at(i) == 0)
				rank = rank + dampeningfactor * 1.0 * currentpagerank.at(i)/size;
		}
		for (uint row = 0; row < graph.size(); row++) {
			newpagerank.at(row) = rank + (1-dampeningfactor)/size;
			for (uint i = 0; i < inlinks[row]; i++) {
				if (outlinks.at(i) == 0)
					continue;
				newpagerank.at(row) = newpagerank.at(row) + (1.0 * dampeningfactor*currentpagerank.at(i))/outlinks.at(i);
			}
		}
		currentpagerank = newpagerank;
		iterations--;
	}
	return currentpagerank;
}



//takes country code input as an int and returns the enumerated value of the country, ie the position in the vectors
//in each node
int Graph::countrycodes(int i){
	switch (i){
		case 4: return 0;
		case 8: return 1;
		case 12: return 2;
		case 16: return 3;
		case 20: return 4;
		case 24: return 5;
		case 28: return 6;
		case 31: return 7;
		case 32: return 8;
		case 36: return 9;
		case 40: return 10;
		case 44: return 11;
		case 48: return 12;
		case 50: return 13;
		case 51: return 14;
		case 52: return 15;
		case 56: return 16;
		case 58: return 17;
		case 60: return 18;
		case 64: return 19;
		case 68: return 20;
		case 70: return 21;
		case 72: return 22;
		case 76: return 23;
		case 84: return 24;
		case 86: return 25;
		case 90: return 26;
		case 92: return 27;
		case 96: return 28;
		case 100: return 29;
		case 104: return 30;
		case 108: return 31;
		case 112: return 32;
		case 116: return 33;
		case 120: return 34;
		case 124: return 35;
		case 132: return 36;
		case 136: return 37;
		case 140: return 38;
		case 144: return 39;
		case 148: return 40;
		case 152: return 41;
		case 156: return 42;
		case 162: return 43;
		case 166: return 44;
		case 170: return 45;
		case 174: return 46;
		case 175: return 47;
		case 178: return 48;
		case 180: return 49;
		case 184: return 50;
		case 188: return 51;
		case 191: return 52;
		case 192: return 53;
		case 196: return 54;
		case 200: return 55;
		case 203: return 56;
		case 204: return 57;
		case 208: return 58;
		case 212: return 59;
		case 214: return 60;
		case 218: return 61;
		case 222: return 62;
		case 226: return 63;
		case 231: return 64;
		case 232: return 65;
		case 233: return 66;
		case 238: return 67;
		case 242: return 68;
		case 246: return 69;
		case 251: return 70;
		case 258: return 71;
		case 260: return 72;
		case 262: return 73;
		case 266: return 74;
		case 268: return 75;
		case 270: return 76;
		case 275: return 77;
		case 276: return 78;
		case 278: return 79;
		case 280: return 80;
		case 288: return 81;
		case 292: return 82;
		case 296: return 83;
		case 300: return 84;
		case 304: return 85;
		case 308: return 86;
		case 316: return 87;
		case 320: return 88;
		case 324: return 89;
		case 328: return 90;
		case 332: return 91;
		case 340: return 92;
		case 344: return 93;
		case 348: return 94;
		case 352: return 95;
		case 360: return 96;
		case 364: return 97;
		case 368: return 98;
		case 372: return 99;
		case 376: return 100;
		case 381: return 101;
		case 384: return 102;
		case 388: return 103;
		case 392: return 104;
		case 398: return 105;
		case 400: return 106;
		case 404: return 107;
		case 408: return 108;
		case 410: return 109;
		case 414: return 110;
		case 417: return 111;
		case 418: return 112;
		case 422: return 113;
		case 426: return 114;
		case 428: return 115;
		case 430: return 116;
		case 434: return 117;
		case 440: return 118;
		case 442: return 119;
		case 446: return 120;
		case 450: return 121;
		case 454: return 122;
		case 458: return 123;
		case 462: return 124;
		case 466: return 125;
		case 470: return 126;
		case 478: return 127;
		case 480: return 128;
		case 484: return 129;
		case 490: return 130;
		case 496: return 131;
		case 498: return 132;
		case 499: return 133;
		case 500: return 134;
		case 504: return 135;
		case 508: return 136;
		case 512: return 137;
		case 516: return 138;
		case 520: return 139;
		case 524: return 140;
		case 528: return 141;
		case 530: return 142;
		case 531: return 143;
		case 533: return 144;
		case 534: return 145;
		case 535: return 146;
		case 540: return 147;
		case 548: return 148;
		case 554: return 149;
		case 558: return 150;
		case 562: return 151;
		case 566: return 152;
		case 570: return 153;
		case 574: return 154;
		case 579: return 155;
		case 580: return 156;
		case 583: return 157;
		case 584: return 158;
		case 585: return 159;
		case 586: return 160;
		case 591: return 161;
		case 598: return 162;
		case 600: return 163;
		case 604: return 164;
		case 608: return 165;
		case 612: return 166;
		case 616: return 167;
		case 620: return 168;
		case 624: return 169;
		case 626: return 170;
		case 634: return 171;
		case 642: return 172;
		case 643: return 173;
		case 646: return 174;
		case 652: return 175;
		case 654: return 176;
		case 659: return 177;
		case 660: return 178;
		case 662: return 179;
		case 666: return 180;
		case 670: return 181;
		case 674: return 182;
		case 678: return 183;
		case 682: return 184;
		case 686: return 185;
		case 688: return 186;
		case 690: return 187;
		case 694: return 188;
		case 697: return 189;
		case 699: return 190;
		case 702: return 191;
		case 703: return 192;
		case 704: return 193;
		case 705: return 194;
		case 706: return 195;
		case 710: return 196;
		case 711: return 197;
		case 716: return 198;
		case 724: return 199;
		case 728: return 200;
		case 729: return 201;
		case 736: return 202;
		case 740: return 203;
		case 748: return 204;
		case 752: return 205;
		case 757: return 206;
		case 760: return 207;
		case 762: return 208;
		case 764: return 209;
		case 768: return 210;
		case 772: return 211;
		case 776: return 212;
		case 780: return 213;
		case 784: return 214;
		case 788: return 215;
		case 792: return 216;
		case 795: return 217;
		case 796: return 218;
		case 798: return 219;
		case 800: return 220;
		case 804: return 221;
		case 807: return 222;
		case 810: return 223;
		case 818: return 224;
		case 826: return 225;
		case 834: return 226;
		case 842: return 227;
		case 849: return 228;
		case 854: return 229;
		case 858: return 230;
		case 860: return 231;
		case 862: return 232;
		case 876: return 233;
		case 882: return 234;
		case 887: return 235;
		case 891: return 236;
		case 894: return 237;

	}
	return -1;
}
