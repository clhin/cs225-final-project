#include "graph.h"
#include "visualizations.h"
#include <string>
#include <vector>
#include <matplot/matplot.h>

/*

//This visualizes a nation/node on the graph and maps all of its edges on a world map, and colors the edges red or green 
//based on whether the nation is a net importer or exporter, red for importer green for exporter
void balanceOfTradeMap(int country, Graph g){
    std::string inName = getCountryName(country);
    std::vector<float> inCoords = getCountryCoords(country);

    //iterates through all connections, and determines if net importer or exporter, then adds the points and edges to the map
    for(unsigned i = 0; i < g.graph[country].size(); i++){
        if(g.graph[country][i] != 0 && g.graph[i][country] != 0){
            float tradeBalance = g.graph[country][i] - g.graph[i][country];
            std::string outName = getCountryName(i);
            std::vector<float> outCoords = getCountryCoords(i);
            if(tradeBalance > 0)
                matplot::geoplot(std::vector{inCoords[0], outCoords[0]}, std::vector{inCoords[1], outCoords[1]}, "g-");
            else
                matplot::geoplot(std::vector{inCoords[0], outCoords[0]}, std::vector{inCoords[1], outCoords[1]}, "r-");

            matplot::hold(matplot::on);

        }
    }
    //Adds name of input country and shows output
    matplot::text(inCoords[1], inCoords[0], inName);
    matplot::show();
}

//This function takes the output of page rank search for a given country, and maps the three highest ranked countries
//on a map with red arrows connecting the ranked countries to the input country
void PageRankVisualization(int country, std::vector<int> rankings){

    std::string inName = getCountryName(country);
    std::vector<float> inCoords = getCountryCoords(country);

    //iterates through the ranking, and then adds the points and edges to the map
    for(unsigned i = 0; i < rankings.size(); i++){

        std::string outName = getCountryName(i);
        std::vector<float> outCoords = getCountryCoords(i);
        matplot::geoplot(std::vector{inCoords[0], outCoords[0]}, std::vector{inCoords[1], outCoords[1]}, "r");
        matplot::text(outCoords[1], outCoords[0], outName);
        matplot::hold(matplot::on);

    }
    matplot::text(inCoords[1], inCoords[0], inName);
    matplot::show();
}


*/
