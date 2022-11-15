#include <catch2/catch_test_macros.hpp>
#include "graph.h"
//doesnt work yet
TEST_CASE("buildGraph1", "[weight=10][part1]"){
    Graph nations = Graph(BACI_HS17_Y2020_V202201.csv);
    REQUIRE(27.82 == nations[0][7]);
}