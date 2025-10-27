/* ************************************************************************
> File Name:     src/PermutationCheck.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Mon Oct 27 01:59:43 2025
> Description:   
 ************************************************************************/

#include "../include/PermutationCheck.h"

PermutationCheck::PermutationCheck() {}

PermutationCheck::~PermutationCheck() {}

// Time: O(N + M), where N is the length of s1, M is the length of s2
// Space: O(K), where K is the number of unique characters in s1, which is need.size()
bool PermutationCheck::checkInclusion(const std::string& s1, const std::string& s2) {
    // edge cases
    if (s1.empty()) return true; // empty string is always a permutation/substring
    if (s2.empty() || s1.size() > s2.size()) return false;

    // character counts needed for s1's permutation
    std::unordered_map<char, int> need;
    for (const char ch : s1) {
        need[ch]++;
    }

    // sliding window character counts
    std::unordered_map<char, int> window;
    // [left, right)
    int left = 0, right = 0;
    int chMatchCount = 0; // count of characters whose counts match need

    while (right < s2.size()) {
        // extend window
        char rCh = s2[right];
        right++;

        // update window and chMatchCount if rCh is needed
        if (need.count(rCh)) {
            window[rCh]++;
            if (window[rCh] == need[rCh]) {
                chMatchCount++;
            }
        }

        // Only require window.size() equals s1.size()
        if (right - left >= s1.size()) {
            if (chMatchCount == need.size()) {
                return true;
            }

            // shrink window
            char lCh = s2[left];
            left++;

            // update window and chMatchCount if lCh is needed
            if (need.count(lCh)) {
                if (window[lCh] == need[lCh]) {
                    chMatchCount--;
                }
                window[lCh]--;
            }
        }
    }

    return false;
}
