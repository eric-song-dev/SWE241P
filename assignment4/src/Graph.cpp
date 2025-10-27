/* ************************************************************************
> File Name:     src/Graph.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Sun Oct 26 15:53:09 2025
> Description:   
 ************************************************************************/

#include "../include/Graph.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <queue>

Graph::Graph() {}

// Time: O(N)
// Space: O(1)
Graph::~Graph() {
    for (auto const& [name, cityPtr] : cities) {
        delete cityPtr;
    }
    cities.clear();
}

std::string Graph::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

bool Graph::loadData(const std::string& cityPopulationFilename, const std::string& roadNetworkFilename) {
    return loadPopulations(cityPopulationFilename) && loadRoadNetwork(roadNetworkFilename);
}

bool Graph::loadPopulations(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "[error] could not open population file: " << filename << std::endl;
        return false;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(inFile, line)) {
        lineNumber++;
        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos) {
            std::cerr << "[warning] invalid format on line " << lineNumber << " in " << filename << ": " << line << std::endl;
            continue;
        }

        std::string cityName = trim(line.substr(0, colonPos));
        std::string popStr = trim(line.substr(colonPos + 1));

        if (cityName.empty()) {
             std::cerr << "[warning] empty city name on line " << lineNumber << " in " << filename << std::endl;
             continue;
        }

        long long population = std::stoll(popStr);
        if (cities.find(cityName) == cities.end()) {
            cities[cityName] = new City(cityName, population);
        } else {
             std::cerr << "[warning] duplicate city definition found for '" << cityName << "' on line " << lineNumber << " in " << filename << ", using first definition" << std::endl;
        }
    }

    inFile.close();
    return true;
}

bool Graph::loadRoadNetwork(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "[error] could not open road network file: " << filename << std::endl;
        return false;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(inFile, line)) {
        lineNumber++;
        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos) {
            std::cerr << "[warning] invalid format on line " << lineNumber << " in " << filename << ": " << line << std::endl;
            continue;
        }

        std::string city1Name = trim(line.substr(0, colonPos));
        std::string city2Name = trim(line.substr(colonPos + 1));

        if(city1Name.empty() || city2Name.empty()) {
             std::cerr << "[warning] empty city name on line " << lineNumber << " in " << filename << std::endl;
             continue;
        }

        City* city1 = getCity(city1Name);
        City* city2 = getCity(city2Name);

        if (city1 == nullptr) {
            std::cerr << "[warning] city '" << city1Name << "' mentioned in " << filename << " (line " << lineNumber << ") not found in population data, skipping road" << std::endl;
            continue;
        }
        if (city2 == nullptr) {
             std::cerr << "[warning] city '" << city2Name << "' mentioned in " << filename << " (line " << lineNumber << ") not found in population data, skipping road" << std::endl;
            continue;
        }

        // Since this is an undirected graph, so need to add bidirectional connection here
        city1->addNeighbor(city2);
        city2->addNeighbor(city1);
    }

    inFile.close();
    return true;
}

// Time: O(V + E) where V/E are vertices/edges in the component
// Space: O(V) for recursion stack
void Graph::dfs(City* city, std::unordered_set<std::string>& visited, long long& currentPopulation) {
    // base case
    if (!city || visited.count(city->name)) {
        return;
    }
    visited.insert(city->name);
    currentPopulation += city->population;

    for (City* neighbor : city->neighbors) {
        dfs(neighbor, visited, currentPopulation);
    }
}

// Time: O(V + E) where V is number of cities, E is number of highways
// Space: O(V) for visited set and recursion/queue stack
int Graph::countIslands() {
    std::unordered_set<std::string> visited;
    int islandCount = 0;
    long long dummyPopulation = 0; // Not used for counting

    for (auto const& [name, cityPtr] : cities) {
        if (!visited.count(name)) {
            islandCount++;
            dfs(cityPtr, visited, dummyPopulation); // Traverse the component
        }
    }
    return islandCount;
}

// Time: O(1)
// Space: O(1)
int Graph::getCitiesCount() {
    return static_cast<int>(cities.size());
}

// Time: O(V + E) where V is number of cities, E is number of highways
// Space: O(V) for visited set and recursion/queue stack
std::vector<long long> Graph::getIslandPopulations() {
    std::unordered_set<std::string> visited;
    std::vector<long long> islandPopulations;

    for (auto const& [name, cityPtr] : cities) {
        if (!visited.count(name)) {
            long long currentIslandPopulation = 0;
            dfs(cityPtr, visited, currentIslandPopulation);
            islandPopulations.push_back(currentIslandPopulation);
        }
    }
    return islandPopulations;
}

// Time: O(V + E) where V is number of cities, E is number of highways
// Space: O(V) for visited set and queue
int Graph::bfs(const std::string& startCityName, const std::string& endCityName) {
    City* startCity = getCity(startCityName);
    City* endCity = getCity(endCityName);

    if (!startCity || !endCity) {
        return -1;
    }

    if (startCity == endCity) {
        return 0;
    }

    // first: city pointer, second: distance from start
    std::queue<std::pair<City*, int>> q;
    std::unordered_set<std::string> visited;

    q.push({startCity, 0});
    visited.insert(startCity->name);

    while (!q.empty()) {
        City* currentCity = q.front().first;
        int currentDistance = q.front().second;
        q.pop();

        if (currentCity == endCity) {
            // found the shortest path
            return currentDistance;
        }

        for (City* neighbor : currentCity->neighbors) {
            if (!visited.count(neighbor->name)) {
                visited.insert(neighbor->name);
                q.push({neighbor, currentDistance + 1});
            }
        }
    }

    return -1;
}

// Time: O(V + E) in the worst case, BFS
// Space: O(V) for visited set and queue
int Graph::findShortestPath(const std::string& startCityName, const std::string& endCityName) {
    return bfs(startCityName, endCityName);
}

// Time: O(1)
// Space: O(1)
City* Graph::getCity(const std::string& name) const {
    if (cities.count(name)) {
        return cities.at(name);
    }
    return nullptr;
}
