/* ************************************************************************
> File Name:     src/NQueensSolver.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Mon Oct 27 02:00:02 2025
> Description:   
 ************************************************************************/

#include "../include/NQueensSolver.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <numeric>
#include <algorithm>

NQueensSolver::NQueensSolver(int size) : boardSize(size), minMoves(std::numeric_limits<int>::max()) {}

NQueensSolver::~NQueensSolver() {}

// Time: O(N!), where N is boardSize, dominated by finding all res (backtrack)
// Space: O(N^2) for the board and storing res
int NQueensSolver::minMovesToSolveNQueens(const std::vector<int>& initialPositions) {
    if (initialPositions.size() != boardSize) {
        std::cerr << "[error] wrong size, size must be " << boardSize << std::endl;
        return -1;
    }

    // convert 1-based input [1, 8] to 0-based [0, 7]
    std::vector<int> positions = initialPositions;
    for(int& row : positions) {
        row--;
        if (row < 0 || row >= boardSize) {
             std::cerr << "[error] invalid row position in input" << std::endl;
             return -1;
        }
    }

    res.clear();
    minMoves = std::numeric_limits<int>::max();

    // '.' = empty, 'Q' = queen
    std::vector<std::string> board(boardSize, std::string(boardSize, '.'));
    
    // find all valid N-Queens res using backtracking
    backtrack(board, 0);

    if (res.empty()) {
        std::cerr << "[warning] no n-queens res found" << std::endl;
        return -1;
    }

    for (const auto& sol : res) {
        minMoves = std::min(minMoves, calculateMoves(positions, sol));
    }

    return minMoves;
}

std::vector<int> NQueensSolver::convertBoardToPosition(const std::vector<std::string>& board) {
    std::vector<int> currentPosition(boardSize);
    for (int r = 0; r < boardSize; ++r) {
        for (int c = 0; c < boardSize; ++c) {
            if (board[r][c] == 'Q') {
                currentPosition[c] = r;
                break;
            }
        }
    }
    return currentPosition;
}

// Time: O(N!) where N is boardSize, dominated by finding all res (backtrack)
// Space: O(N^2) for the board and storing res
void NQueensSolver::backtrack(std::vector<std::string>& board, int row) {
    // base case
    if (row == boardSize) {
        auto currentPosition = convertBoardToPosition(board);
        res.push_back(currentPosition);
        return;
    }

    for (int col = 0; col < boardSize; col++) {
        // check if placing a queen at (row, col) is safe
        if (!isValid(board, row, col)) {
            continue;
        }
        
        // make choice, place queen
        board[row][col] = 'Q';
        
        // recurse: move to the next row
        backtrack(board, row + 1);
        
        // undo choice (backtrack), remove queen
        board[row][col] = '.';
    }
}

// Time: O(N), where N is boardSize
// Space: O(1)
bool NQueensSolver::isValid(const std::vector<std::string>& board, int row, int col) {
    // check column conflict
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q')
            return false;
    }
    // check up-right diagonal conflict
    for (int i = row - 1, j = col + 1; i >= 0 && j < boardSize; i--, j++) {
        if (board[i][j] == 'Q')
            return false;
    }
    // check up-left diagonal conflict
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q')
            return false;
    }
    
    return true;
}

// Time: O(N), where N is boardSize
// Space: O(1)
int NQueensSolver::calculateMoves(const std::vector<int>& initial, const std::vector<int>& target) {
     int moves = 0;
     for (int i = 0; i < boardSize; ++i) {
         if (initial[i] != target[i]) {
             moves++;
         }
     }
     return moves;
}
