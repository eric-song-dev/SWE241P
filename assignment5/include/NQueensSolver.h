/* ************************************************************************
> File Name:     include/NQueensSolver.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Mon Oct 27 01:59:52 2025
> Description:   
 ************************************************************************/

#pragma once

#include <vector>
#include <string>
#include <limits>

static const int DEFAULT_BOARD_SIZE = 8;

class NQueensSolver {
public:
    NQueensSolver(int size = DEFAULT_BOARD_SIZE);
    ~NQueensSolver();

    // Task 2: Calculate minimum moves to solve N-Queens
    int minMovesToSolveNQueens(const std::vector<int>& initialPositions);
    
private:
    // Backtracking function to find all N-Queens res
    void backtrack(std::vector<std::string>& board, int row);
    
    // Check if placing a queen at board[row][col] is valid
    bool isValid(const std::vector<std::string>& board, int row, int col);

    // Calculate moves needed to transform initial to target
    int calculateMoves(const std::vector<int>& initial, const std::vector<int>& target);
    
    // convert board (vector<string>) to position (vector<int>) format
    std::vector<int> convertBoardToPosition(const std::vector<std::string>& board);

private:
    int boardSize = 0;
    int minMoves = std::numeric_limits<int>::max();
    std::vector<std::vector<int>> res;
};
