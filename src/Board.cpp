#include "Board.h"
#include <string>

void Board::loadFromArray(const int puzzle[9][9]) {
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            grid[i][j] = puzzle[i][j];
}

int (&Board::getGrid())[9][9] {
    return grid;
}

void Board::print() const {
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0 && i != 0)
            std::cout << "------+-------+------\n";
        for (int j = 0; j < 9; ++j) {
            if (j % 3 == 0 && j != 0)
                std::cout << "| ";
            std::cout << (grid[i][j] ? std::to_string(grid[i][j]) : ".") << " ";
        }
        std::cout << "\n";
    }
}
