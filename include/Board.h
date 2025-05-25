#ifndef BOARD_H
//#define BOARD_H

#include <array>
#include <bitset>
#include <string>
#include <vector>
#include <random>

class Board {
public:
    Board();

    // Core functionality
    void loadFromString(const std::string& str);
    bool solveRecursive(int row, int col, bool countSolutions = false);
    void solve();
    std::string toString() const;

    // Difficulty tracking
    int getBacktracks() const { return backtracks; }
    void resetBacktracks() { backtracks = 0; }

    // Puzzle generation
    void generateHardPuzzle(int minClues = 22, int maxClues = 25);
    bool hasUniqueSolution();

private:

    std::vector<int> board;
    mutable std::vector<int> tmp_buffer;
    std::array<int, 81> grid;
    std::array<std::bitset<9>, 9> rowsUsed;
    std::array<std::bitset<9>, 9> colsUsed;
    std::array<std::bitset<9>, 9> boxesUsed;

    int backtracks = 0;
    int solutionCount = 0;

    static std::mt19937 rng; // Shared RNG

    // Helper methods
    int& at(int row, int col);
    int at(int row, int col) const;

    bool placeNumber(int row, int col, int num);
    void removeNumber(int row, int col, int num);
    bool canPlace(int row, int col, int num) const;

    bool findMostConstrainedCell(int& row, int& col) const;
    std::vector<int> getPossibleNumbers(int row, int col) const;

    void removeNumbersToMakeHard(int remainingClues);
};

#endif // BOARD_H
