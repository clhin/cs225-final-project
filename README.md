# cs225-final-project


## Github Organization


### Entry

Entry contains the main file, which will prompt the user to eter a country, and be returned a BFS starting from the input country, and the top three countries in the Page Rank Search function, then the user will be prompted to ender two nations to compare the relative price of trade, which use Dijkstra's algorithm's output to determine. If any invalid inputs are made, the main function will end with a message stating the invalid input.

### SRC
This contains all of the algorithms, node building, and commented out files for visualizations. All the code for the algorithms can be found in `graph.cpp`.

### Tests
This contains all the tests in our project. The node building tests are done by building a graph and checking outputs, Djikstra's algorithm uses a smaller graph as input to test, BFS uses the graph to compare with the expoected output, and Page Rank is tested by checking that the probabilities of the reankings all sum to one, and tested that after one iteration the results are correct.

## Data
We use the BACI Bilateral Trade Database for 2020, which can be downloaded here: https://drive.google.com/drive/folders/1V_HJuovf_Ql6d2zJtBFoiWon96oyc1JM?usp=sharing
To use this database in this project, download the file, and then add the file `BACI_HS17_Y2020_V202201.csv` to the cloned repo. To use other years of the data base see: http://www.cepii.fr/CEPII/en/bdd_modele/bdd_modele_item.asp?id=37

## Running Instructions
This project should be run in the class Docker container. To run firstly clone the repo, and add the csv to the cs225-final-project directory. Withing the project directory, you should set up a build folder to use cmake by running `mkdir build`, then `cd build`, then `cmake ..`. The tests can be compiled using `make test` and run using `./test`. To compile main simply use `make main`, and to run use `./main`, from there you will be prompted to input counties.

## Running Visualizations
Visualizations will not work in the standard Docker environment, as they require Gnuplot to run. To run locally, the library matplotplusplus is required, and the functions need to be uncommented and called. The balanceOfTradeMap function takes a country and a completed graph as an input, and the PageRankVisualization takes a country as input and the output of pageRankSearch on that fuction as input. Matplotplusplus: https://alandefreitas.github.io/matplotplusplus/

## Team
Rithvik Kopparapu (rithvik9@illinois.edu) 

John Hofmann (johnwh3@illinois.edu) 

Praneeth Rangamudri (jrang3@illinois.edu) 

Chase Hinkle (chinkle3@illinois.edu) 
