/* ************************************************************************
> File Name:     src/City.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Sun Oct 26 15:52:46 2025
> Description:   
 ************************************************************************/

#include "../include/City.h"

City::City(std::string name, long long population) : name(std::move(name)), population(population) {}

City::~City() {}

// Time: O(1)
// Space: O(1)
void City::addNeighbor(City* neighbor) {
    if (neighbor != nullptr) {
        neighbors.push_back(neighbor);
    }
}
