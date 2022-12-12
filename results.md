# CEPII BACI Database of Bilateral Trade Final Project Report

## Leading Question and Project Plan:
Given a dataset of trade between nations, what nations are the most dependent on goods from others, and what countries have the most nations dependent on them? In this project, our goal is to utilize the dataset to create an engine that takes user input of a country and lists the countries that it imports and exports the most to. This will be done using a breadth first traversal which finds all of the paths from a starting node to all other nodes in our graph Dijsktra's Algorithm which calculates the shortest path from one node to any other node and the Page Rank algorithm, which determines the nations with the greatest trade “importance” to an input nation. 

After finishing our project, we were able to successfully determine the answer to our leading question and adequately implement every algorithm.


## BFS
When implementing BFS, we wanted it to be able to work easily on the main dataset. So, it is structured as follows: For input, it takes in a start country code (a node on our graph) and it uses a queue to do the traversal, a vector of booleans to mark nodes visited, and traverses the graph (represented as a vector of vectors) using a while loop with a for loop inside. The algorithm returns a vector containing the country by country BFS traversal, starting with the “start” country given. Since the output is simply a vector of country codes, we implemented a few functions that convert from country code to the country name, making the output more clear to visualize. This is shown in main.cpp, where if you enter a country name, our program will take it, convert to a country code, run BFS starting from there, convert the vector of ints back to country names, and print it out to see. An example of this output is listed here: 
![BFS Results](https://github.com/clhin/cs225-final-project/blob/main/reportImages/bfs%20results.png)
The runtime of BFS matches as expected, O(C+A) (C representing each country (node), and A representing each trade pair (edge)). For testing, since we were running this algorithm on the dataset itself, we took one row of country codes from the graph, and checked that the first few non-zero entries of the BFS vector starting from said row matches the row from the graph exactly. This test worked with several rows, and in our test case, we included a sample row and matched it to a BFS vector run on that row.

## Dijkstra's Algorithm
This takes in a country code and returns the approximate trade price to all other countries represented in a vector. We assume that trade price is inversely proportional to the dollar amount of exports between countries. This assumption maps pretty well onto the real world, for example neighboring countries tend to do a lot of trade with each other, and their trade prices are lower because they are so close, another example is that highly used shipping routes see their costs reduced as so many ships use them thus making the price of shipping lower. Within Djiktra’s algorithm function, I used a priority queue of pairs to traverse the graph. The key represents 1/weight and value represents node (row index of node on matrix). In order to run Djikstra’s we start off at a node. Then we proceed to the neighboring node and add 1/export weight. From that neighboring node of the start, move to the next neighboring node adding 1/prev export weight + 1/ current export weight. Here is an example of what I’m referring to If A is neighboring with B, and export weight = 2. A’s approximate trade price is with B ½ Now if B neighbors with C and export weight from B to C= 4. Approximate trade price from A to C  = ½ + ¼ 


The run time of this algorithm is O(C^2 * logC) where C represents country code (node). In order to test the algorithm, I had a separate function that would test djikstra’s on smaller graphs since it would be difficult to test and interpret results on the graph used in the project. The tester function is similar to the original except in addition to an index corresponding to a country on graph (matrix), a parameter representing the graph (matrix) was also passed in. 

## PageRank
This algorithm was one of our more interesting implementations for the dataset. When running the pagerank algorithm,
we found that the top ten countries with the most amount of countries traded to was as follows:
Czechia, France, Korea, Poland, South Africa, Spain, Germany, Singapore, Thailand, and Indonesia. This was very interesting to us
as we originally thought that the US and China would be top results, but we dug into it a bit more and found that
both the US and China have tariffs and sanctions on a number of countries that these "open port" countries lack. We
tested our algorithm by making sure that, as a pagerank should, each element summed with the rest adds to 1. With
floating point rounding, we decided to make this a bound between .99 and 1.01. We also made sure that we tested to make
sure that the proper countries were showing up first, last, etc. We achieved a runtime of iterations * O(n+m), but depending on how many iterations
are performed, this could take a lot of time for a linear output. Here is a visualization of the page rank search function, which returns the three highest ranked countries that an input country trades with:
![PageRank](https://github.com/clhin/cs225-final-project/blob/main/reportImages/pagerank.png)

We definitely answered the leading questions we proposed about the most active trade countries with this algorithm. As stated, running the pagerank
algorithm allowed us to see what countries with the most active ports were (listed above). As for trade dependence, we attempted to solve this with
pagerank and a search function, but we think our results would be more valuable if we considered volume as well. Taking the most active port out of
anyone's trade network will obviously cause lots of damage, but it may not correlate to the most amount of trade done with the target country.

## Conclusion
By implementing the algorithms and graph we were able to find the largest exporting and importing nations as well as through Dijkstra's Algorithm we were able to create an approximate comparison between the trading costs between two nations especially when there may be a cheaper country to route trade through, and through Page Rank we were able to find which nations do trade with the most countries, a decent metric for approximating nations with the most open trade. BFS provides a potential trade path in order for an input nation to export to all other nations.
