# CEPII BACI Database of Bilateral Trade Final Project Report

## Leading Question and Project Plan:
Given a dataset of trade between nations, what nations are the most dependent on goods from others, and what countries have the most nations dependent on them? In this project, our goal is to utilize the dataset to create an engine that takes user input of a country and lists the countries that it imports and exports the most to. This will be done using a breadth first traversal which finds all of the paths from a starting node to all other nodes in our graph Dijsktra's Algorithm which calculates the shortest path from one node to any other node and the Page Rank algorithm, which determines the nations with the greatest trade “importance” to an input nation. 

After finishing our project, we were able to successfully determine the answer to our leading question and adequately implement every algorithm.


## BFS
When implementing BFS, we wanted it to be able to work easily on the main dataset. So, it is structured as follows: For input, it takes in a start country code (a node on our graph) and it uses a queue to do the traversal, a vector of booleans to mark nodes visited, and traverses the graph (represented as a vector of vectors) using a while loop with a for loop inside. The algorithm returns a vector containing the country by country BFS traversal, starting with the “start” country given. Since the output is simply a vector of country codes, we implemented a few functions that convert from country code to the country name, making the output more clear to visualize. This is shown in main.cpp, where if you enter a country name, our program will take it, convert to a country code, run BFS starting from there, convert the vector of ints back to country names, and print it out to see. An example of this output is listed here: 

The runtime of BFS matches as expected, O(C+A) (C representing each country (node), and A representing each trade pair (edge)). For testing, since we were running this algorithm on the dataset itself, we took one row of country codes from the graph, and checked that the first few non-zero entries of the BFS vector starting from said row matches the row from the graph exactly. This test worked with several rows, and in our test case, we included a sample row and matched it to a BFS vector run on that row.

## Dijkstra's Algorithm
This takes in a country code and returns the approximate trade price to all other countries represented in a vector. We assume that trade price is inversely proportional to the dollar amount of exports between countries. This assumption maps pretty well onto the real world, for example neighboring countries tend to do a lot of trade with each other, and their trade prices are lower because they are so close, another example is that highly used shipping routes see their costs reduced as so many ships use them thus making the price of shipping lower. Within Djiktra’s algorithm function, I used a priority queue of pairs to traverse the graph. The key represents 1/weight and value represents node (row index of node on matrix). In order to run Djikstra’s we start off at a node. Then we proceed to the neighboring node and add 1/export weight. From that neighboring node of the start, move to the next neighboring node adding 1/prev export weight + 1/ current export weight. Here is an example of what I’m referring to If A is neighboring with B, and export weight = 2. A’s approximate trade price is with B ½ Now if B neighbors with C and export weight from B to C= 4. Approximate trade price from A to C  = ½ + ¼ 


The run time of this algorithm is O(C^2 * logC) where C represents country code (node). In order to test the algorithm, I had a separate function that would test djikstra’s on smaller graphs since it would be difficult to test and interpret results on the graph used in the project. The tester function is similar to the original except in addition to an index corresponding to a country on graph (matrix), a parameter representing the graph (matrix) was also passed in. 
PageRank:


## Conclusion
By implementing the algorithms we were able to find the largest exporting and importing nations	 as well as through Dijkstra's Algorithm we were able to create an approximate comparison between the trading costs between two nations especially when there may be a cheaper country to route trade through, and through Page Rank we were able to find which nations do trade with the most countries, a decent metric for approximating nations with the most open trade.
