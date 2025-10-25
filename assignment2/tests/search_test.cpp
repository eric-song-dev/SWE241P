/* ************************************************************************
> File Name:     tests/search_test.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Sat Oct 25 00:11:23 2025
> Description:   
 ************************************************************************/

#include <gtest/gtest.h>
#include "SearchUtils.h"
#include <vector>
#include <iostream>

bool VectorsMatch(const std::vector<int>& expected, const std::vector<int>& actual) {
    if (expected.size() != actual.size()) return false;
    
    for (size_t i = 0; i < expected.size(); ++i) {
        if (expected[i] != actual[i]) {
            return false;
        }
    }
    
    return true;
}


class SearchTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(SearchTest, Task1_BasicFound) {
    std::vector<int> nums = {4, 9, 10, 13, 17, 17, 19, 21};
    int target = 17;
    std::vector<int> expected = {4, 5};
    std::vector<int> result = SearchUtils::searchRange(nums, target);
    EXPECT_TRUE(VectorsMatch(expected, result));
}

TEST_F(SearchTest, Task1_NotFound) {
    std::vector<int> nums = {2, 4, 6, 8, 10, 14, 16};
    int target = 12;
    std::vector<int> expected = {-1, -1};
    std::vector<int> result = SearchUtils::searchRange(nums, target);
    EXPECT_TRUE(VectorsMatch(expected, result));
}

TEST_F(SearchTest, Task1_EmptyArray) {
    std::vector<int> nums = {};
    int target = 0;
    std::vector<int> expected = {-1, -1};
    std::vector<int> result = SearchUtils::searchRange(nums, target);
    EXPECT_TRUE(VectorsMatch(expected, result));
}

TEST_F(SearchTest, Task1_SingleElementFound) {
    std::vector<int> nums = {5};
    int target = 5;
    std::vector<int> expected = {0, 0};
    std::vector<int> result = SearchUtils::searchRange(nums, target);
    EXPECT_TRUE(VectorsMatch(expected, result));
}

TEST_F(SearchTest, Task1_SingleElementNotFound) {
    std::vector<int> nums = {5};
    int target = 3;
    std::vector<int> expected = {-1, -1};
    std::vector<int> result = SearchUtils::searchRange(nums, target);
    EXPECT_TRUE(VectorsMatch(expected, result));
}

TEST_F(SearchTest, Task1_TargetAtBeginning) {
    std::vector<int> nums = {2, 2, 3, 4, 5};
    int target = 2;
    std::vector<int> expected = {0, 1};
    std::vector<int> result = SearchUtils::searchRange(nums, target);
    EXPECT_TRUE(VectorsMatch(expected, result));
}

TEST_F(SearchTest, Task1_TargetAtEnd) {
    std::vector<int> nums = {1, 3, 5, 5};
    int target = 5;
    std::vector<int> expected = {2, 3};
    std::vector<int> result = SearchUtils::searchRange(nums, target);
    EXPECT_TRUE(VectorsMatch(expected, result));
}

TEST_F(SearchTest, Task1_AllElementsAreTarget) {
    std::vector<int> nums = {7, 7, 7, 7, 7};
    int target = 7;
    std::vector<int> expected = {0, 4};
    std::vector<int> result = SearchUtils::searchRange(nums, target);
    EXPECT_TRUE(VectorsMatch(expected, result));
}

TEST_F(SearchTest, Task2_BasicFound) {
    std::vector<std::vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int target = 3;
    const bool expected = true;
    const bool result = SearchUtils::searchMatrix(matrix, target);
    EXPECT_EQ(expected, result);
}

TEST_F(SearchTest, Task2_NotFound) {
    std::vector<std::vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int target = 13;
    const bool expected = false;
    const bool result = SearchUtils::searchMatrix(matrix, target);
    EXPECT_EQ(expected, result);
}

TEST_F(SearchTest, Task2_EmptyMatrix) {
    std::vector<std::vector<int>> matrix = {};
    int target = 1;
    const bool expected = false;
    const bool result = SearchUtils::searchMatrix(matrix, target);
    EXPECT_EQ(expected, result);
}

TEST_F(SearchTest, Task2_EmptyRow) {
    std::vector<std::vector<int>> matrix = {{}};
    int target = 1;
    const bool expected = false;
    const bool result = SearchUtils::searchMatrix(matrix, target);
    EXPECT_EQ(expected, result);
}

TEST_F(SearchTest, Task2_SingleElementMatrixFound) {
    std::vector<std::vector<int>> matrix = {{5}};
    int target = 5;
    const bool expected = true;
    const bool result = SearchUtils::searchMatrix(matrix, target);
    EXPECT_EQ(expected, result);
}

TEST_F(SearchTest, Task2_SingleElementMatrixNotFound) {
    std::vector<std::vector<int>> matrix = {{5}};
    int target = 3;
    const bool expected = false;
    const bool result = SearchUtils::searchMatrix(matrix, target);
    EXPECT_EQ(expected, result);
}

TEST_F(SearchTest, Task2_TargetFirstElement) {
    std::vector<std::vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int target = 1;
    const bool expected = true;
    const bool result = SearchUtils::searchMatrix(matrix, target);
    EXPECT_EQ(expected, result);
}

TEST_F(SearchTest, Task2_TargetLastElement) {
    std::vector<std::vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int target = 60;
    const bool expected = true;
    const bool result = SearchUtils::searchMatrix(matrix, target);
    EXPECT_EQ(expected, result);
}

TEST_F(SearchTest, Task2_SingleRowMatrix) {
    std::vector<std::vector<int>> matrix = {{1, 3, 5, 7, 10, 11, 16, 20}};
    int target = 16;
    const bool expected = true;
    const bool result = SearchUtils::searchMatrix(matrix, target);
    EXPECT_EQ(expected, result);
}

TEST_F(SearchTest, Task2_SingleColumnMatrix) {
    std::vector<std::vector<int>> matrix = {{1}, {10}, {23}};
    int target = 10;
    const bool expected = true;
    const bool result = SearchUtils::searchMatrix(matrix, target);
    EXPECT_EQ(expected, result);
}
