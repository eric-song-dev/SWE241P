/* ************************************************************************
> File Name:     src/AnagramGrouper.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Sat Oct 25 03:19:18 2025
> Description:   
 ************************************************************************/

#include "../include/AnagramGrouper.h"
#include <iostream>
#include <stdexcept>

AnagramGrouper::AnagramGrouper() {}

AnagramGrouper::~AnagramGrouper() {}

// Time: O(L * N log N) using HeapSort/QuickSort (average), where L is the number of strings and N is the max length of a string
// Space: O(L * N) in the worst case for storing strings in the map and the result
std::vector<std::vector<std::string>> AnagramGrouper::groupAnagrams(const std::vector<std::string>& strings, const SortAlgorithm& sortAlgorithm)
{
    std::unordered_map<std::string, std::vector<std::string>> anagramMap;

    for (const std::string& originalString : strings) {
        std::string sortedStr = sortString(originalString, sortAlgorithm);
        anagramMap[sortedStr].push_back(originalString);
    }

    std::vector<std::vector<std::string>> result;
    result.reserve(anagramMap.size());

    for (const auto& [key, val] : anagramMap) {
        result.push_back(val);
    }

    return result;
}

std::string AnagramGrouper::sortString(const std::string& str, const SortAlgorithm& sortAlgorithm) {
    if (sortAlgorithm == SortAlgorithm::HEAP) {
        return SortUtils::heapSortString(str);
    } else if (sortAlgorithm == SortAlgorithm::QUICK) {
        return SortUtils::quickSortString(str);
    } else {
        throw std::invalid_argument("Unsupported sort algorithm");
    }
}
