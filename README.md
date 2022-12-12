# cs225-final-project


## Github Organization


### Entry

Entry contains the main file, which will prompt the user to eter a country, and be returned a BFS starting from the input country, and the top three countries in the Page Rank Search function, then the user will be prompted to ender two nations to compare the relative price of trade, which use Dijkstra's algorithm's output to determine. If any invalid inputs are made, the main function will end with a message stating the invalid input.

### SRC
This contains all of the algorithms, node building, and commented out files for visualizations.

### Tests
This contains all the tests in our project. The node building tests are done by building a graph and checking outputs, Djikstra's algorithm uses a smaller graph as input to test, BFS uses the graph to compare with the expoected output, and Page Rank is tested by checking that the probabilities of the reankings all sum to one, and tested that after one iteration the results are correct.

## Data
We use the BACI Bilateral Trade Database, which can be downloaded here: http://www.cepii.fr/DATA_DOWNLOAD/baci/data/BACI_HS17_V202201.zip
To use this database in this project, unzip the folder, and then add the file `BACI_HS17_Y2020_V202201.csv` to the cloned repo.

## Running Instructions
This project should be run in the class Docker container. To run firstly clone the repo, and add the csv to the cs225-final-project directory. Withing the project directory, you should set up a build folder to use cmake by running `mkdir build`, then `cd build`, then `cmake ..`. The tests can be compiled using `make test` and run using `./test`. To compile main simply use `make main`, and to run use `./main`, from there you will be prompted to input counties.

## Running Visualizations
Visualizations will not work in the standard Docker environment, as they require Gnuplot to run. To run locally, the library matplotplusplus is required, and the functions need to be uncommented and called. The balanceOfTradeMap function takes a country and a completed graph as an input, and the PageRankVisualization takes a country as input and the output of pageRankSearch on that fuction as input. Matplotplusplus: https://alandefreitas.github.io/matplotplusplus/
