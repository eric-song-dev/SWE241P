/* ************************************************************************
> File Name:     tests/anagram_test.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Sat Oct 25 03:19:45 2025
> Description:   
 ************************************************************************/

#include <gtest/gtest.h>
#include "../include/SortUtils.h"
#include "../include/AnagramGrouper.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <chrono>
#include <iomanip>

// Helper function to compare vectors of vectors, ignoring the order of inner vectors and elements within inner vectors.
bool compareAnagramGroups(std::vector<std::vector<std::string>> expected, std::vector<std::vector<std::string>> actual) {
    if (expected.size() != actual.size()) return false;

    for (auto& group : expected) std::sort(group.begin(), group.end());
    for (auto& group : actual) std::sort(group.begin(), group.end());

    std::map<std::vector<std::string>, int> expectedCounts;
    std::map<std::vector<std::string>, int> actualCounts;

    for (const auto& group : expected) expectedCounts[group]++;
    for (const auto& group : actual) actualCounts[group]++;

    return expectedCounts == actualCounts;
}


class AnagramTest : public ::testing::Test {
protected:
    AnagramGrouper grouper;

    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(AnagramTest, HeapSortString) {
    EXPECT_EQ(SortUtils::heapSortString(""), "");
    EXPECT_EQ(SortUtils::heapSortString("a"), "a");
    EXPECT_EQ(SortUtils::heapSortString("bac"), "abc");
    EXPECT_EQ(SortUtils::heapSortString("mango"), "agmno");
    EXPECT_EQ(SortUtils::heapSortString("ogtan"), "agnot");
    EXPECT_EQ(SortUtils::heapSortString("hello world"), " dehllloorw");
    EXPECT_EQ(SortUtils::heapSortString("zyxw"), "wxyz");
    EXPECT_EQ(SortUtils::heapSortString("aabbcc"), "aabbcc");
}

TEST_F(AnagramTest, QuickSortString) {
    EXPECT_EQ(SortUtils::quickSortString(""), "");
    EXPECT_EQ(SortUtils::quickSortString("a"), "a");
    EXPECT_EQ(SortUtils::quickSortString("bac"), "abc");
    EXPECT_EQ(SortUtils::quickSortString("mango"), "agmno");
    EXPECT_EQ(SortUtils::quickSortString("ogtan"), "agnot");
    EXPECT_EQ(SortUtils::quickSortString("hello world"), " dehllloorw");
    EXPECT_EQ(SortUtils::quickSortString("zyxw"), "wxyz");
    EXPECT_EQ(SortUtils::quickSortString("aabbcc"), "aabbcc");
}

TEST_F(AnagramTest, GroupAnagramsExample) {
    std::vector<std::string> input = {"bucket","rat","mango","tango","ogtan","tar"};
    std::vector<std::vector<std::string>> expected = {
        {"bucket"},
        {"rat","tar"},
        {"mango"},
        {"tango","ogtan"},
    };

    std::vector<std::vector<std::string>> actualHeap = grouper.groupAnagrams(input, SortAlgorithm::HEAP);
    EXPECT_TRUE(compareAnagramGroups(expected, actualHeap));

    std::vector<std::vector<std::string>> actualQuick = grouper.groupAnagrams(input, SortAlgorithm::QUICK);
    EXPECT_TRUE(compareAnagramGroups(expected, actualQuick));
}

TEST_F(AnagramTest, GroupAnagramsEmptyInput) {
    std::vector<std::string> input = {};
    std::vector<std::vector<std::string>> expected = {};
    EXPECT_EQ(grouper.groupAnagrams(input, SortAlgorithm::HEAP), expected);
    EXPECT_EQ(grouper.groupAnagrams(input, SortAlgorithm::QUICK), expected);
}

TEST_F(AnagramTest, GroupAnagramsNoAnagrams) {
    std::vector<std::string> input = {"abc", "def", "ghi"};
    std::vector<std::vector<std::string>> expected = {{"abc"}, {"def"}, {"ghi"}};
    EXPECT_TRUE(compareAnagramGroups(expected, grouper.groupAnagrams(input, SortAlgorithm::HEAP)));
    EXPECT_TRUE(compareAnagramGroups(expected, grouper.groupAnagrams(input, SortAlgorithm::QUICK)));
}

TEST_F(AnagramTest, GroupAnagramsAllAnagrams) {
    std::vector<std::string> input = {"eat", "tea", "ate"};
    std::vector<std::vector<std::string>> expected = {{"eat", "tea", "ate"}};
     EXPECT_TRUE(compareAnagramGroups(expected, grouper.groupAnagrams(input, SortAlgorithm::HEAP)));
    EXPECT_TRUE(compareAnagramGroups(expected, grouper.groupAnagrams(input, SortAlgorithm::QUICK)));
}

TEST_F(AnagramTest, GroupAnagramsMixedCaseAndEmptyStrings) {
    std::vector<std::string> input = {"Eat", "tea", "ate", "", "tan", "nat", ""};
    std::vector<std::vector<std::string>> expected = {
        {"Eat"},
        {"tea", "ate"},
        {"", ""},
        {"tan", "nat"},
    };
    EXPECT_TRUE(compareAnagramGroups(expected, grouper.groupAnagrams(input, SortAlgorithm::HEAP)));
    EXPECT_TRUE(compareAnagramGroups(expected, grouper.groupAnagrams(input, SortAlgorithm::QUICK)));
}

TEST_F(AnagramTest, InvalidSortAlgorithm) {
    std::vector<std::string> input = {"a", "b"};
    EXPECT_THROW(grouper.groupAnagrams(input, SortAlgorithm::UNKNOWN), std::invalid_argument);
}

TEST_F(AnagramTest, PerformanceComparisonTest) {
    std::vector<std::string> strings = {"bucket","rat","mango","tango","ogtan","tar", "listen", "silent", "enlist", "banana", "nabana", "apple", "paple", "stressed", "desserts", "dormitory", "dirtyroom"};
    std::cout << "input size for performance test: " << strings.size() << " strings" << std::endl;

    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::duration<double, std::milli> duration_ms;

    // 1. Time Heap Sort
    start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<std::string>> groupedHeap = grouper.groupAnagrams(strings, SortAlgorithm::HEAP);
    end = std::chrono::high_resolution_clock::now();
    duration_ms = end - start;
    double heapSortTime = duration_ms.count();
    std::cout << "heap Sort Time: " << std::fixed << std::setprecision(4) << heapSortTime << " ms" << std::endl;

    // 2. Time Quick Sort
    start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<std::string>> groupedQuick = grouper.groupAnagrams(strings, SortAlgorithm::QUICK);
    end = std::chrono::high_resolution_clock::now();
    duration_ms = end - start;
    double quickSortTime = duration_ms.count();
    std::cout << "quick Sort Time: " << std::fixed << std::setprecision(4) << quickSortTime << " ms" << std::endl;
}
