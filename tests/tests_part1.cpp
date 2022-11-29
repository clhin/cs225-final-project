#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include "graph.h"


//first trade pair only one value
TEST_CASE("buildGraph1", "[weight=10][part1]"){
    Graph nations = Graph("../BACI_HS17_Y2020_V202201.csv");
    REQUIRE(27.82f == nations.Exports(4,31));
}
//empty trade pair
TEST_CASE("buildGraph2", "[weight=10][part1]"){
    Graph nations = Graph("../BACI_HS17_Y2020_V202201.csv");
    REQUIRE(0.0f == nations.Exports(4,12));
}
//large trade pair
TEST_CASE("buildGraph3", "[weight=10][part1]"){
    Graph nations = Graph("../BACI_HS17_Y2020_V202201.csv");
    REQUIRE(44844.316f == nations.Exports(76,226));
}
//country with itself should be zero
TEST_CASE("buildGraph4", "[weight=10][part1]"){
    Graph nations = Graph("../BACI_HS17_Y2020_V202201.csv");
    REQUIRE(0.0f == nations.Exports(100,100));
}
//another large trade pair, using ceil because float is only accurate to 7 digits
TEST_CASE("buildGraph5", "[weight=10][part1]"){
    Graph nations = Graph("../BACI_HS17_Y2020_V202201.csv");
    REQUIRE(ceil(148533.361f) == ceil(nations.Exports(112,31)));
}