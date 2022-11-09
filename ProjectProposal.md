## Leading Question 
Given a dataset of trade between nations, what nations are the most dependent on goods from others, and what countries have the most nations dependent on them? In this project, our goal is to utilize the dataset to create an engine that takes user input of a country and lists the countries that it imports and exports the most to. This will be done using a breadth first traversal which finds all of the paths from a starting node to all other nodes in our graph Dijsktra's Algorithm which calculates the shortest path from one node to any other node and the Page Rank algorithm, which determines the nations with the greatest trade “importance” to an input nation.

## Dataset Acquisition
We will be using the CEPII BACI database of bilateral trade flows for 200 nations, and 5000 products. We will be using the database that covers the years from 2017 to 2020, but only the file for 2020 trade. The dataset can be found here: http://www.cepii.fr/CEPII/en/bdd_modele/bdd_modele_item.asp?id=37
## Data Format
The format is in a series of three CSV files, one with the trade data, where each nation is stored with a code and each good is stored with a code, with the volume and quantity given as well. The other two CSV’s are the product codes and nation codes.

## Data Correction
Firstly the CSV file includes a row for the year, which will be discarded as we are only using data from 2020. Then all the product codes would be consolidated into one total import and export value between nations based on the total value of the products.

## Data Storage
Once the data has been parsed, we would store the values as a map of vectors, where the map key is the country code and the vector holds the trading partner map keys, and trade weights of those connected nations. The storage complexity of this graph would be O(n^2), where n is the number of nodes/nations, as each node can be connected to all other nodes, thus at worst each node would need to contain a vector with all other nodes.
## Algorithm 
Algorithm #1: BFS: With BFS, we would find all the exports from one country to every other country in the graph. Each node in the graph is a country, and each edge represents the trade. With this structure, we can display the countries and the trade between them in a manner that works with BFS. The time complexity of this algorithm would be O(C+A) (C representing each country (node), and A representing each trade pair (edge)).

Algorithm #2: Dijkstra's Algorithm: This algorithm calculates the most trade from one node to any other node, with weights calculated as the number of imports and exports between the two nodes. This function takes a graph reference and the output should be the greatest exporter to a given country. When we analyze the time complexity of the Dijkstra's algorithm a using fibonacci heap, it would be O(C log C + A) where C represents a country (node).

Algorithm #3: Page Rank: The input for page rank will be the node that the user wishes to see the most relevant results for. The “most relevant” information in this case will be which partners trade the most with the node (country). The output, as specified in page rank, will be an eigenvector of each node and a value that corresponds to their importance. We will represent this with a C++ vector of doubles. We expect the runtime to be O(n+m), where n is the number of nodes and m is the number of edges. This can scale by a constant if multiple runs are completed, but the results will still be constant time.

## Timeline
Week of November 7:
	Finish formatting data, and project structure setup. Begin work on algos.
	
Week of November 14:
Mid-Project Check In, have node building/data cleaning finished
Continue work on Algos

Week of November 21:
	Complete Algos
	
Week of November 28:
	Begin work on visualizations
	
Week of December 5:
	Complete visualizations
	Project due December 8 (Friday)
