/* ************************************************************************
> File Name:     tests/recursion_backtracking_test.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Mon Oct 27 02:04:05 2025
> Description:   
 ************************************************************************/

#include <gtest/gtest.h>
#include "../include/PermutationCheck.h"
#include "../include/NQueensSolver.h"
#include <string>
#include <vector>
#include <iostream>

class RecursionBacktrackingTest : public ::testing::Test {
protected:
    PermutationCheck pc;
    NQueensSolver nqs{DEFAULT_BOARD_SIZE};

    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(RecursionBacktrackingTest, Permutation_Example1) {
    std::string s1 = "ab";
    std::string s2 = "eidbaooo";
    EXPECT_TRUE(pc.checkInclusion(s1, s2));
    std::cout << "test passed: permutation example 1" << std::endl << std::endl;
}

TEST_F(RecursionBacktrackingTest, Permutation_Example2) {
    std::string s1 = "ab";
    std::string s2 = "eidboaoo";
    EXPECT_FALSE(pc.checkInclusion(s1, s2));
    std::cout << "test passed: permutation example 2" << std::endl << std::endl;
}

TEST_F(RecursionBacktrackingTest, Permutation_SameString) {
    std::string s1 = "abc";
    std::string s2 = "abc";
    EXPECT_TRUE(pc.checkInclusion(s1, s2));
    std::cout << "test passed: permutation same string" << std::endl << std::endl;
}

TEST_F(RecursionBacktrackingTest, Permutation_PermutationAtStart) {
    std::string s1 = "abc";
    std::string s2 = "bacxyz";
    EXPECT_TRUE(pc.checkInclusion(s1, s2));
    std::cout << "test passed: permutation at start" << std::endl << std::endl;
}

TEST_F(RecursionBacktrackingTest, Permutation_PermutationAtEnd) {
    std::string s1 = "abc";
    std::string s2 = "xyzcba";
    EXPECT_TRUE(pc.checkInclusion(s1, s2));
    std::cout << "test passed: permutation at end" << std::endl << std::endl;
}

TEST_F(RecursionBacktrackingTest, Permutation_S1LongerThanS2) {
    std::string s1 = "abcde";
    std::string s2 = "abc";
    EXPECT_FALSE(pc.checkInclusion(s1, s2));
    std::cout << "test passed: permutation s1 longer than s2" << std::endl << std::endl;
}

TEST_F(RecursionBacktrackingTest, Permutation_EmptyS1) {
    std::string s1 = "";
    std::string s2 = "abc";
    EXPECT_TRUE(pc.checkInclusion(s1, s2));
    std::cout << "test passed: permutation empty s1" << std::endl << std::endl;
}

TEST_F(RecursionBacktrackingTest, Permutation_EmptyS2) {
    std::string s1 = "abc";
    std::string s2 = "";
    EXPECT_FALSE(pc.checkInclusion(s1, s2));
    std::cout << "test passed: permutation empty s2" << std::endl << std::endl;
}

TEST_F(RecursionBacktrackingTest, Permutation_NoMatch) {
    std::string s1 = "xyz";
    std::string s2 = "abcdefg";
    EXPECT_FALSE(pc.checkInclusion(s1, s2));
    std::cout << "test passed: permutation no matching characters" << std::endl << std::endl;
}

TEST_F(RecursionBacktrackingTest, NQueens_Example1) {
    std::vector<int> initial = {1, 2, 3, 4, 5, 6, 7, 8};
    EXPECT_EQ(nqs.minMovesToSolveNQueens(initial), 7);
    std::cout << "test passed: nqueens example 1 (diagonal)" << std::endl << std::endl;
}

TEST_F(RecursionBacktrackingTest, NQueens_Example2) {
    std::vector<int> initial = {1, 1, 1, 1, 1, 1, 1, 1};
    EXPECT_EQ(nqs.minMovesToSolveNQueens(initial), 7);
    std::cout << "test passed: nqueens example 2 (all row 1)" << std::endl << std::endl;
}

TEST_F(RecursionBacktrackingTest, NQueens_AlreadySolved) {
    std::vector<int> initial = {4, 2, 7, 3, 6, 8, 5, 1};
    EXPECT_EQ(nqs.minMovesToSolveNQueens(initial), 0);
    std::cout << "test passed: nqueens already solved" << std::endl << std::endl;
}

TEST_F(RecursionBacktrackingTest, NQueens_OneMoveAway) {
    std::vector<int> initial = {4, 2, 7, 3, 6, 8, 5, 2};
    EXPECT_EQ(nqs.minMovesToSolveNQueens(initial), 1);
    std::cout << "test passed: nqueens one move away" << std::endl << std::endl;
}

TEST_F(RecursionBacktrackingTest, NQueens_TwoMovesAway) {
    std::vector<int> initial = {5, 2, 7, 3, 6, 8, 5, 2};
    EXPECT_EQ(nqs.minMovesToSolveNQueens(initial), 2);
    std::cout << "test passed: nqueens two moves away" << std::endl << std::endl;
}

TEST_F(RecursionBacktrackingTest, NQueens_InvalidInputSize) {
     std::vector<int> initial = {1, 2, 3};
     EXPECT_EQ(nqs.minMovesToSolveNQueens(initial), -1);
     std::cout << "test passed: nqueens invalid input size" << std::endl << std::endl;
}

TEST_F(RecursionBacktrackingTest, NQueens_InvalidInputValue) {
     std::vector<int> initial = {1, 2, 3, 4, 9, 6, 7, 8}; // 9 is out of bounds [1, 8]
     EXPECT_EQ(nqs.minMovesToSolveNQueens(initial), -1);
     std::cout << "test passed: nqueens invalid input value" << std::endl << std::endl;
}
