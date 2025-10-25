/* ************************************************************************
> File Name:     include/SearchUtils.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Sat Oct 25 00:10:24 2025
> Description:   
 ************************************************************************/

#pragma once

#include <vector>

class SearchUtils {
public:
    static std::vector<int> searchRange(const std::vector<int>& nums, int target);
    static bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target);
};
