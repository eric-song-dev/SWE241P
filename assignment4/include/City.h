/* ************************************************************************
> File Name:     include/City.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Sun Oct 26 15:52:32 2025
> Description:   
 ************************************************************************/

#pragma once

#include <string>
#include <vector>
#include <iostream>

struct City {
    std::string name;
    long long population;
    std::vector<City*> neighbors;

    City(std::string name, long long population);
    ~City();

    // Task 1: Add a neighbor
    void addNeighbor(City* neighbor);
};
