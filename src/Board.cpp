#include "Board.h"
#include <fstream>
#include <iostream>

void Board::load(const std::string& filename) {
    std::ifstream file(filename);
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            file >> grid[i][j];
}

int Board::at(int row, int col) const {
    return grid[row][col];
}

void Board::set(int row, int col, int val) {
    grid[row][col] = val;
}

void Board::print() const {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j)
            std::cout << grid[i][j] << ' ';
        std::cout << '\n';
    }
}
