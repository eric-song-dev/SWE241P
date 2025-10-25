/* ************************************************************************
> File Name:     src/SearchUtils.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Sat Oct 25 00:10:42 2025
> Description:   
 ************************************************************************/

#include "../include/SearchUtils.h"
#include <vector>

// Time: O(log N)
// Space: O(1)
int findFirstPosition(const std::vector<int>& nums, int target) {
    int low = 0;
    int high = nums.size() - 1;
    int firstPos = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] >= target) {
            if (nums[mid] == target) {
                firstPos = mid;
            }
            high = mid - 1; // Look in the left half (or continue left if found)
        } else {
            low = mid + 1;  // Look in the right half
        }
    }
    return firstPos;
}

// Time: O(log N)
// Space: O(1)
int findLastPosition(const std::vector<int>& nums, int target) {
    int low = 0;
    int high = nums.size() - 1;
    int lastPos = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] <= target) {
            if (nums[mid] == target) {
                lastPos = mid;
            }
            low = mid + 1; // Look in the right half (or continue right if found)
        } else {
            high = mid - 1; // Look in the left half
        }
    }
    return lastPos;
}

// Here I use two separate binary searches to ensure O(log n) complexity for finding both the start and end indices.
// My original thought is to find first index with binary search, then linear scan rightwards
// However, it would degrade to O(n) in the worst case (e.g., an array like [2, 2, 2, 2, 2]).
// Time: O(log N), where N is the number of elements in nums
// Space: O(1)
std::vector<int> SearchUtils::searchRange(const std::vector<int>& nums, int target) {
    if (nums.empty()) return {-1, -1};
    
    int first = findFirstPosition(nums, target);
    int last = findLastPosition(nums, target);

    if (first == -1) return {-1, -1};

    return {first, last};
}

// Key Point: Treat the matrix as a flattened 1D array
// Time: O(log(M*N)), where M is the number of rows and N is the number of columns
// Space: O(1)
bool SearchUtils::searchMatrix(const std::vector<std::vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
        return false;
    }

    int m = static_cast<int>(matrix.size());
    int n = static_cast<int>(matrix[0].size());
    int low = 0;
    int high = m * n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int row = mid / n;
        int col = mid % n;

        if (matrix[row][col] == target) {
            return true;
        } else if (matrix[row][col] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return false;
}
