#include "Board.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <iostream>

Board::Board() {
    grid.fill(0);
    for (auto& b : rowsUsed) b.reset();
    for (auto& b : colsUsed) b.reset();
    for (auto& b : boxesUsed) b.reset();
}

// Static RNG initialization
std::mt19937 Board::rng(std::random_device{}());

int& Board::at(int row, int col) {
    return grid[row * 9 + col];
}

int Board::at(int row, int col) const {
    return grid[row * 9 + col];
}

bool Board::canPlace(int row, int col, int num) const {
    int boxIndex = (row / 3) * 3 + (col / 3);
    int bit = num - 1;
    return !rowsUsed[row].test(bit) &&
           !colsUsed[col].test(bit) &&
           !boxesUsed[boxIndex].test(bit);
}

bool Board::placeNumber(int row, int col, int num) {
    if (!canPlace(row, col, num))
        return false;
    at(row, col) = num;
    int boxIndex = (row / 3) * 3 + (col / 3);
    rowsUsed[row].set(num - 1);
    colsUsed[col].set(num - 1);
    boxesUsed[boxIndex].set(num - 1);
    return true;
}

void Board::removeNumber(int row, int col, int num) {
    at(row, col) = 0;
    int boxIndex = (row / 3) * 3 + (col / 3);
    rowsUsed[row].reset(num - 1);
    colsUsed[col].reset(num - 1);
    boxesUsed[boxIndex].reset(num - 1);
}

void Board::loadFromString(const std::string& str) {
    grid.fill(0);
    for (auto& b : rowsUsed) b.reset();
    for (auto& b : colsUsed) b.reset();
    for (auto& b : boxesUsed) b.reset();

    for (size_t i = 0; i < str.size() && i < 81; ++i) {
        char ch = str[i];
        if (ch >= '1' && ch <= '9') {
            int val = ch - '0';
            int row = i / 9;
            int col = i % 9;
            placeNumber(row, col, val);
        }
    }
}

std::string Board::toString() const {
    std::string result;
    for (int i = 0; i < 81; ++i) {
        int val = grid[i];
        result += (val == 0 ? '.' : ('0' + val));
        if ((i + 1) % 9 == 0)
            result += '\n';
    }
    return result;
}

bool Board::findMostConstrainedCell(int& row, int& col) const {
    int minOptions = 10;
    bool found = false;

    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (at(r, c) != 0) continue;

            int options = static_cast<int>(getPossibleNumbers(r, c).size());
            if (options < minOptions) {
                minOptions = options;
                row = r;
                col = c;
                found = true;
                if (minOptions == 1)
                    return true; // Early exit
            }
        }
    }
    return found;
}

std::vector<int> Board::getPossibleNumbers(int row, int col) const {
    std::vector<int> possible;
    for (int num = 1; num <= 9; ++num) {
        if (canPlace(row, col, num)) {
            possible.push_back(num);
        }
    }
    std::shuffle(possible.begin(), possible.end(), rng);
    return possible;
}

bool Board::solveRecursive(int row, int col, bool countSolutions) {
    if (row == 9) {
        if (countSolutions) {
            ++solutionCount;
            return solutionCount > 1;
        }
        return true;
    }

    if (!findMostConstrainedCell(row, col)) {
        return true;
    }

    for (int num : getPossibleNumbers(row, col)) {
        if (placeNumber(row, col, num)) {
            if (solveRecursive(row, col, countSolutions)) {
                if (!countSolutions || solutionCount > 1)
                    return true;
            }
            removeNumber(row, col, num);
            backtracks++;
        }
    }

    return false;
}

void Board::solve() {
    backtracks = 0;
    solutionCount = 0;
    solveRecursive(0, 0);
}

bool Board::hasUniqueSolution() {
    Board temp = *this;
    temp.solutionCount = 0;
    temp.solveRecursive(0, 0, true);
    return temp.solutionCount == 1;
}

void Board::removeNumbersToMakeHard(int remainingClues) {
    std::vector<int> positions(81);
    std::iota(positions.begin(), positions.end(), 0);
    std::shuffle(positions.begin(), positions.end(), rng);

    int removed = 0;
    for (int pos : positions) {
        if (grid[pos] == 0)
            continue;

        int row = pos / 9;
        int col = pos % 9;
        int val = grid[pos];

        removeNumber(row, col, val);

        if (!hasUniqueSolution()) {
            placeNumber(row, col, val); // revert removal
        } else {
            removed++;
            if (removed >= 81 - remainingClues)
                break;
        }
    }
}

void Board::generateHardPuzzle(int minClues, int maxClues) {
    grid.fill(0);
    for (auto& b : rowsUsed) b.reset();
    for (auto& b : colsUsed) b.reset();
    for (auto& b : boxesUsed) b.reset();

    solve();

    std::uniform_int_distribution<int> dist(minClues, maxClues);
    removeNumbersToMakeHard(dist(rng));
}
