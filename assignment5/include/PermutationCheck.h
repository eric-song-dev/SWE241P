/* ************************************************************************
> File Name:     include/PermutationCheck.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Mon Oct 27 01:59:29 2025
> Description:   
 ************************************************************************/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class PermutationCheck {
public:
    PermutationCheck();
    ~PermutationCheck();

    // Task 1: Check if s2 contains a permutation of s1
    bool checkInclusion(const std::string& s1, const std::string& s2);
};
