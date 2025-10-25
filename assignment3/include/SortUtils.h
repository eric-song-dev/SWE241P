/* ************************************************************************
> File Name:     include/SortUtils.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Sat Oct 25 03:18:40 2025
> Description:   
 ************************************************************************/

#pragma once

#include <string>
#include <vector>
#include <stdexcept>

enum class SortAlgorithm : int {
    UNKNOWN = 0,
    HEAP = 1,
    QUICK = 2,
};

class SortUtils {
public:
    static std::string heapSortString(const std::string& str);
    
    static std::string quickSortString(const std::string& str);
    
private:
    static void heapify(std::vector<char>& chars, int len, int i);
    static void heapSort(std::vector<char>& chars);

    static void quickSort(std::vector<char>& chars, int low, int high);
    static int partition(std::vector<char>& chars, int low, int high);
};
