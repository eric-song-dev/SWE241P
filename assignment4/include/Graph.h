/* ************************************************************************
> File Name:     include/Graph.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Sun Oct 26 15:52:57 2025
> Description:   
 ************************************************************************/

#pragma once

#include "City.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Graph {
public:
    Graph();
    ~Graph();
    
    // Task 2: Load data
    bool loadData(const std::string& cityPopulationFilename, const std::string& roadNetworkFilename);
    
    // Task 2: Count the number of cities
    int getCitiesCount();

    // Task 3: Count the number of islands (connected components)
    int countIslands();

    // Task 4: Get the population of each island
    std::vector<long long> getIslandPopulations();

    // Task 5: Find the shortest path (number of highways) between two cities
    // Returns -1 if no path exists.
    int findShortestPath(const std::string& startCityName, const std::string& endCityName);

    // Helper to get a city pointer by name
    City* getCity(const std::string& name) const;
    
private:
    // Task 2: Load city populations from file
    bool loadPopulations(const std::string& filename);

    // Task 2: Load road network from file
    bool loadRoadNetwork(const std::string& filename);
    
    // Helper for DFS traversal, used in countIslands and getIslandPopulations
    void dfs(City* city, std::unordered_set<std::string>& visited, long long& currentPopulation);

    // Helper for BFS traversal, used in findShortestPath
    int bfs(const std::string& startCityName, const std::string& endCityName);

    std::string trim(const std::string& str);

private:
    // Adjacency list presentation
    std::unordered_map<std::string, City*> cities;
};
