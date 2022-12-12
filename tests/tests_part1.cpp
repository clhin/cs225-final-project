#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <vector>
#include "graph.h"

//helper function for dealing with float rounding problems, this takes two vectors and compares them to see if
//every value is equal within a tolerance
bool compare_float(std::vector<float>vect_1, std::vector<float>vect_2){
     for (size_t x = 0; x <vect_1.size(); x++) {
        if (std::abs(vect_1[x] - vect_2[x]) >= 0.001) {
           return false;
        }
    }
    return true;

}

//helper function for dealing with float rounding problems, this takes two floats and compares them to see if
//both values are equal within a tolerance
bool compare_single_float(float float_1, float float_2){
        if (std::abs(float_1 - float_2) >= 0.001) {
           return false;
    }
    return true;

}

Graph nations = Graph("../BACI_HS17_Y2020_V202201.csv");

//first trade pair only one value
TEST_CASE("buildGraph1", "[weight=10][part1]"){
    REQUIRE(27.82f == nations.Exports(4,31));
}
//empty trade pair
TEST_CASE("buildGraph2", "[weight=10][part1]"){
    REQUIRE(0.0f == nations.Exports(4,12));
}
//large trade pair
TEST_CASE("buildGraph3", "[weight=10][part1]"){
    REQUIRE(44844.316f == nations.Exports(76,226));
}
//country with itself should be zero
TEST_CASE("buildGraph4", "[weight=10][part1]"){
    REQUIRE(0.0f == nations.Exports(100,100));
}
//another large trade pair, using ceil because float is only accurate to 7 digits
TEST_CASE("buildGraph5", "[weight=10][part1]"){
    REQUIRE(ceil(148533.361f) == ceil(nations.Exports(112,31)));
}

//BFS test case from actual dataset
//checks that the first non-zero values of BFS called on row 1 equal row 1 from the graph, adding the starting value
TEST_CASE("bfs1", "[weight=10][part1]"){
    std::vector<int>row1 = {1, 7, 8, 9, 10, 14, 16, 18, 20, 21, 22, 23, 28, 29, 30, 31, 32, 33, 35, 36, 39, 41, 42, 45, 46, 48, 51, 52, 54, 56, 57, 58, 60, 61, 62, 64, 66, 69, 70, 71, 75, 78, 84, 88, 90, 93, 94, 95, 96, 99, 100, 101, 102, 103, 104, 105, 106, 107, 109, 110, 111, 113, 115, 118, 119, 120, 121, 123, 126, 127, 128, 130, 131, 132, 133, 135, 136, 138, 141, 149, 150, 151, 155, 158, 160, 161, 163, 164, 165, 167, 168, 171, 172, 173, 185, 186, 187, 190, 191, 192, 194, 196, 198, 199, 204, 205, 206, 209, 210, 214, 216, 220, 221, 222, 224, 225, 227, 229, 230, 231, 237};
    std::vector<int>bfsrow1 = nations.BFS(1);
    bfsrow1.resize(row1.size());
    REQUIRE(bfsrow1 == row1);
}

//Djikstra Test Cases
TEST_CASE("djikstra1", "[weight=10][part1]") { //Tests Undirected Simple Graph
    std::vector<std::vector<float>> test_matrix_one= {
    {0, 10, 20, 30, 0},
    {10, 0, 15, 0, 10},
    {20, 15, 0, 20, 15},
    {30, 0, 20, 0, 20},
    {0, 10, 15, 20, 0}};
    Graph nations;
    std::vector<float>correct_dist_from_zero = {0,1.0/10,1.0/20,1.0/30, (1.0/30 + 1.0/20)};
    std::vector<float>output_zero = nations.TestDjikstra(0,test_matrix_one);
    REQUIRE(compare_float(correct_dist_from_zero, output_zero));
    std::vector<float>correct_dist_from_four = {(1.0/30 + 1.0/20),1.0/10,1.0/15,1.0/20, 0};
    std::vector<float>output_four = nations.TestDjikstra(4,test_matrix_one);
    REQUIRE(compare_float(correct_dist_from_four, output_four));
}
TEST_CASE("djikstra2", "[weight=10][part1]") { //Tests Graph where some pair of nodes are connected by more than one edge 
    std::vector<std::vector<float>> test_matrix_one= {
    {0, 10, 20, 30, 0},
    {20, 0, 15, 0, 10},
    {20, 15, 0, 20, 15},
    {30, 0, 35, 0, 20},
    {0, 10, 15, 20, 0}};
    Graph nations;
    std::vector<float>correct_dist_from_zero = {0,1.0/10,1.0/20,1.0/30, (1.0/30 + 1.0/20)};
    std::vector<float>output_zero = nations.TestDjikstra(0,test_matrix_one);
    REQUIRE(compare_float(correct_dist_from_zero, output_zero));
    std::vector<float>correct_dist_from_four = {(1.0/30 + 1.0/20),1.0/10,1.0/15,1.0/20, 0};
    std::vector<float>output_four = nations.TestDjikstra(4,test_matrix_one);
    REQUIRE(compare_float(correct_dist_from_four, output_four));
    
}
TEST_CASE("djikstra3", "[weight=10][part1]") { //Test graph where there's more than one node in graph such that it's not neighbor to every other node in graph
    std::vector<std::vector<float>> test_matrix_one= { //Essentially if you start at any node there will be more than one node in graph such that it's not a neighbor to the start node
    {0, 4, 4, 0, 0, 0},
    {4, 0, 2, 0, 0, 0},
    {4, 2, 0, 3, 1, 6},
    {0, 0, 3, 0, 0, 2},
    {0, 0, 1, 0, 0, 3},
    {0, 0, 6, 2, 3, 0}};
    Graph nations;
    std::vector<float>correct_dist_from_zero = {0, 1.0/4, 1.0/4, 7.0/12, 0.75, 5.0/12};
    std::vector<float>output_zero = nations.TestDjikstra(0,test_matrix_one);
    REQUIRE(compare_float(correct_dist_from_zero,output_zero));
    std::vector<float>correct_dist_from_five = {5.0/12, 2.0/3, 1.0/6, 1.0/2, 1.0/3, 0};
    std::vector<float>output_five = nations.TestDjikstra(5,test_matrix_one);
    REQUIRE(compare_float(correct_dist_from_five,output_five));
}
TEST_CASE("djikstra4", "[weight=10][part1]") { //Similar to previous test case except some pair of nodes are connected by more than one edge
    std::vector<std::vector<float>> test_matrix_one= {
    {0, 4, 4, 0, 0, 0},
    {8, 0, 2, 0, 0, 0},
    {4, 2, 0, 3, 1, 6},
    {0, 0, 6, 0, 0, 9},
    {0, 0, 7, 0, 0, 3},
    {0, 0, 9, 2, 3, 0}};
    Graph nations;
    std::vector<float>correct_dist_from_zero = {0, 1.0/4, 1.0/4, 7.0/12, 0.75, 5.0/12};
    std::vector<float>output_zero = nations.TestDjikstra(0,test_matrix_one);
    //REQUIRE(correct_dist_from_zero == output_zero);
    REQUIRE(compare_float(correct_dist_from_zero,output_zero));
    std::vector<float>correct_dist_from_five = {13.0/36, 11.0/18, 1.0/9, 4.0/9, 1.0/3, 0};
    std::vector<float>output_five = nations.TestDjikstra(5,test_matrix_one);
    REQUIRE(compare_float(correct_dist_from_five,output_five));
}

//The sum of all the page rank outputs should be 1, as the outputs of page rank are all probabilities
TEST_CASE("PageRankOutput1", "[weight=10][part1]"){

    std::vector<float> PageRankOutput = nations.pagerank(100);

    float sum = 0.0;
    for(unsigned i = 0; i < PageRankOutput.size(); i++){
		sum += PageRankOutput[i];
	}
    bool inRange = (sum < 1.01) && (sum > .99);
    REQUIRE(inRange);
}

//expected output of one round of pagerank on index 0
TEST_CASE("PageRankOutput2", "[weight=10][part1]"){

    std::vector<float> PageRankOutput = nations.pagerank(1);

    REQUIRE(compare_single_float(PageRankOutput[0], 0.000756302f));
}
