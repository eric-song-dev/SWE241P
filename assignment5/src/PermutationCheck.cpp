/* ************************************************************************
> File Name:     src/PermutationCheck.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Mon Oct 27 01:59:43 2025
> Description:   
 ************************************************************************/

#include "../include/PermutationCheck.h"
#include <unordered_map>
#include <string>

PermutationCheck::PermutationCheck() {}

PermutationCheck::~PermutationCheck() {}

// Time: O(N! * M * N), where N = s1.size(), M = s2.size(), O(N!) is for backtracking operation, O((M-N)*N) or O(M*N) is for s2.find operation
// Space: O(N), for map and recursion stack
bool PermutationCheck::backtrack(std::unordered_map<char, int>& need, std::string& currentPermutation, const int targetSize, const std::string& s2) {
    // base case, when the permutation is the same size as s1 and this permutation is a substring of s2
    if (currentPermutation.size() == targetSize && s2.find(currentPermutation) != std::string::npos) {
        return true;
    }

    for (const auto& pair : need) {
        const char ch = pair.first;
        const int count = pair.second;

        if (count > 0) {
            // make choice
            // 1. add char to the current permutation
            // 2. decrease the count
            currentPermutation.push_back(ch);
            need[ch]--;

            // if any branch finds a solution, return true immediately
            // early termination, is also like a pruning
            if (backtrack(need, currentPermutation, targetSize, s2)) {
                return true;
            }

            // Undo choice (backtrack)
            // 1. restore the count
            // 2. remove char to the current permutation
            need[ch]++;
            currentPermutation.pop_back();
        }
    }

    // If all character choices fail to find a match from this state
    return false;
}

// Time: O(N! * M * N), where N = s1.size(), M = s2.size(), O(N!) is for backtracking operation, O((M-N)*N) or O(M*N) is for s2.find operation
// Space: O(N), for map and recursion stack
bool PermutationCheck::checkInclusion(const std::string& s1, const std::string& s2) {
    // edge cases
    if (s1.empty()) return true;
    if (s2.empty() || s1.size() > s2.size()) return false;

    std::unordered_map<char, int> need;
    for (const char ch : s1) {
        need[ch]++;
    }

    std::string currentPermutation = "";
    
    return backtrack(need, currentPermutation, static_cast<int>(s1.size()), s2);
}
