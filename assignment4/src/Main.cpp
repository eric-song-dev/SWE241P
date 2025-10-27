/* ************************************************************************
> File Name:     src/Main.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Sun Oct 26 15:53:29 2025
> Description:   
 ************************************************************************/

#include "../include/Graph.h"
#include <iostream>
#include <string>
#include <vector>

static const std::string DEFAULT_PATH = "/Users/ericsong/Courses/SWE241P/assignment4/";
static const std::string DEFAULT_POPULATION_FILE = DEFAULT_PATH + "city_population.txt";
static const std::string DEFAULT_ROAD_FILE = DEFAULT_PATH + "road_network.txt";

int main(int argc, char* argv[]) {
    std::string populationFilename = DEFAULT_POPULATION_FILE;
    std::string roadFilename = DEFAULT_ROAD_FILE;

    if (argc == 3) {
        populationFilename = argv[1];
        roadFilename = argv[2];
         std::cout << "Using provided files:" << std::endl;
         std::cout << "  Population: " << populationFilename << std::endl;
         std::cout << "  Road Network: " << roadFilename << std::endl;
    } else if (argc != 1) {
        std::cerr << "Usage: " << argv[0] << " [ <population_file> <road_network_file> ]" << std::endl;
        std::cerr << "Using default files: " << populationFilename << " and " << roadFilename << std::endl;
    } else {
        std::cout << "Using default files:" << std::endl;
        std::cout << "  Population: " << populationFilename << std::endl;
        std::cout << "  Road Network: " << roadFilename << std::endl;
    }


    Graph g;

    // Task 2: Load data
    std::cout << "--- Task 2: Loading Data ---" << std::endl;
    bool loaded = g.loadData(populationFilename, roadFilename);

    if (!loaded) {
        std::cerr << "[error] failed to load one or both input files" << std::endl;
        return 1;
    }
    std::cout << "--- Task 2: Loading data and counting cities ---" << std::endl;
    std::cout << "number of cities: " << g.getCitiesCount() << std::endl << std::endl;

    // Task 3: Count Islands
    std::cout << "--- Task 3: Counting Islands ---" << std::endl;
    std::cout << "number of islands: " << g.countIslands() << std::endl << std::endl;

    // Task 4: Get Island Populations
    std::cout << "--- Task 4: Calculating Island Populations ---" << std::endl;
    std::vector<long long> populations = g.getIslandPopulations();
    std::cout << "populations of each island:" << std::endl;
    for (size_t i = 0; i < populations.size(); ++i) {
        std::cout << "  island " << (i + 1) << ": " << populations[i] << std::endl;
    }
    std::cout << std::endl;

    // Task 5: Find Shortest Path
    std::cout << "--- Task 5: Finding Shortest Path ---" << std::endl;
    std::string cityA = "New York";
    std::string cityB = "Citrus Heights";
    std::cout << "finding shortest path between '" << cityA << "' and '" << cityB << "'" << std::endl;
    int shortestPath = g.findShortestPath(cityA, cityB);
    if (shortestPath != -1) {
        std::cout << "minimum number of highways between '" << cityA << "' and '" << cityB << "': " << shortestPath << std::endl;
    } else {
        std::cout << "could not find path between '" << cityA << "' and '" << cityB << "'" << std::endl;
    }

    std::cout << std::endl;

    return 0;
}
