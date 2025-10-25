/* ************************************************************************
> File Name:     include/AnagramGrouper.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Sat Oct 25 03:19:06 2025
> Description:   
 ************************************************************************/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include "../include/SortUtils.h"

class AnagramGrouper {
public:
    AnagramGrouper();
    ~AnagramGrouper();

    std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strings, const SortAlgorithm& sortAlgorithm = SortAlgorithm::HEAP);

private:
    std::string sortString(const std::string& str, const SortAlgorithm& sortAlgorithm);
};
