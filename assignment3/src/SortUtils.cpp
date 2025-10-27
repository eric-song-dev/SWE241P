/* ************************************************************************
> File Name:     src/SortUtils.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Sat Oct 25 03:18:52 2025
> Description:   
 ************************************************************************/

#include "../include/SortUtils.h"
#include <vector>
#include <algorithm>

// Time: O(N log N), where N is the length of the string
// Space: O(1)
std::string SortUtils::heapSortString(const std::string& str) {
    if (str.empty()) {
        return "";
    }
    std::vector<char> chars(str.begin(), str.end());
    heapSort(chars);
    return std::string(chars.begin(), chars.end());
}

// Time: Average O(N log N), Worst O(N^2), where N is the length of the string
// Space: Average O(log N) for recursion stack, Worst O(N)
std::string SortUtils::quickSortString(const std::string& str) {
     if (str.empty()) {
        return "";
    }
    std::vector<char> chars(str.begin(), str.end());
    quickSort(chars, 0, static_cast<int>(chars.size()) - 1);
    return std::string(chars.begin(), chars.end());
}

// Time: O(log N), where N is the length of the string
// Space: O(1)
void SortUtils::heapify(std::vector<char>& chars, int len, int i) {
    int largest = i;
    int lson = 2 * i + 1;
    int rson = 2 * i + 2;

    if (lson < len && chars[lson] > chars[largest]) largest = lson;
    if (rson < len && chars[rson] > chars[largest]) largest = rson;

    if (largest != i) {
        std::swap(chars[i], chars[largest]);
        heapify(chars, len, largest);
    }
}

// Time: O(N log N), where N is the length of the string
// Space: O(1)
void SortUtils::heapSort(std::vector<char>& chars) {
    int len = static_cast<int>(chars.size());

    // 1. Build max heap
    // Start from the last non-leaf node and go up to the root
    for (int i = len / 2 - 1; i >= 0; i--)
        heapify(chars, len, i);

    // 2. One by one extract elements from heap
    for (int i = len - 1; i > 0; i--) {
        // Move current root (largest element) to end
        std::swap(chars[0], chars[i]);
        // Call max heapify on the reduced heap, the size of the heap is reduced by 1 in each iteration
        heapify(chars, i, 0);
    }
}

// Time: Average O(N log N), Worst O(N^2)
// Space: Average O(log N), Worst O(N)
void SortUtils::quickSort(std::vector<char>& chars, int low, int high) {
    if (low < high) {
        // pi is partitioning index, chars[pi] is now at right place
        int pi = partition(chars, low, high);

        quickSort(chars, low, pi - 1);
        quickSort(chars, pi + 1, high);
    }
}

// Time: O(N) where N = high - low + 1
// Space: O(1)
int SortUtils::partition(std::vector<char>& chars, int low, int high) {
    char pivot = chars[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (chars[j] <= pivot) {
            std::swap(chars[++i], chars[j]);
        }
    }
    std::swap(chars[i + 1], chars[high]);
    return (i + 1);
}
