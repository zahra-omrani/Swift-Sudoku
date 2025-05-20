#include "Board.h"

Board::Board() : grid(9, std::vector<int>(9, 0)) {}

void Board::loadFromString(const std::string& str) {
    for (size_t i = 0; i < str.size() && i < 81; ++i) {
        grid[i / 9][i % 9] = str[i] - '0';
    }
}

bool Board::isValid(int row, int col, int num) {
    for (int i = 0; i < 9; ++i) {
        if (grid[row][i] == num) return false;
        if (grid[i][col] == num) return false;
    }
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int r = startRow; r < startRow + 3; ++r) {
        for (int c = startCol; c < startCol + 3; ++c) {
            if (grid[r][c] == num) return false;
        }
    }
    return true;
}

bool Board::solveRecursive(int row, int col) {
    if (row == 9) return true;
    if (col == 9) return solveRecursive(row + 1, 0);
    if (grid[row][col] != 0) return solveRecursive(row, col + 1);

    for (int num = 1; num <= 9; ++num) {
        if (isValid(row, col, num)) {
            grid[row][col] = num;
            if (solveRecursive(row, col + 1)) return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

void Board::solve() {
    solveRecursive(0, 0);
}

std::string Board::toString() const {
    std::string result;
    for (const auto& row : grid) {
        for (int val : row) {
            result += std::to_string(val);
        }
    }
    return result;
}
