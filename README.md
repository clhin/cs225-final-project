# cs225-final-project


# Github Organization


## Entry

Entry contains the main file, which will run BFS starting from the US, Djikstra's starting with the US, and Page Rank on the entire graph. The first five entries of each are printed.

## SRC
This contains all of the algorithms, node building, and commented out files for visualizations.

## Tests
This contains all the tests in our project. The node building tests are done by building a graph and checking outputs, Djikstra's algorithm, BFS, and Page Rank are all tested functions using test fucntions that take in smaller datasets as input.

# Data
We use the BACI Bilateral Trade Database, which can be downloaded here: http://www.cepii.fr/DATA_DOWNLOAD/baci/data/BACI_HS17_V202201.zip
To use this database in this project, unzip the folder, and then add the file "BACI_HS17_Y2020_V202201.csv" to the cloned repo.

# Running Instructions
This project should be run in the class Docker container. To run firstly clone the repo, and add the csv to the cs225-final-project directory. Withing the project directory, you should set up a build folder to use cmake by running `mkdir build`, `cd build`, then `cmake ..`. The tests can be compiled using `make test` and run using `./test`. To compile main simply use `make main`, and to run use `./main`.

# Running Visualizations
Visualizations will not work in the standard Docker environment, as they require Gnuplot to run. To run locally, the https://alandefreitas.github.io/matplotplusplus/
