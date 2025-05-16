#include "SequentialSolver.h"

bool SequentialSolver::solve(int board[9][9]) {
    return solveSudoku(board);
}

bool SequentialSolver::solve(Board& b) {
    int (*grid)[9] = b.getGrid();
    return solveSudoku(grid);
}

bool SequentialSolver::isSafe(int board[9][9], int row, int col, int num) {
    // Check row and column
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    // Check 3x3 box
    int boxRow = row - row % 3;
    int boxCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[boxRow + i][boxCol + j] == num)
                return false;

    return true;
}

bool SequentialSolver::solveSudoku(int board[9][9]) {
    int row, col;

    // Find empty cell
    bool emptyFound = false;
    for (row = 0; row < 9 && !emptyFound; ++row) {
        for (col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                emptyFound = true;
                break;
            }
        }
    }
    if (!emptyFound) return true; // no empty cells

    --row; // adjust row after loop

    for (int num = 1; num <= 9; ++num) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board))
                return true;
            board[row][col] = 0;
        }
    }

    return false;
}
