#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>

class Board {
public:
    Board();

    void loadFromString(const std::string& str);
    bool isValid(int row, int col, int num);
    bool solveRecursive(int row, int col);
    void solve();

    std::string toString() const;

private:
    std::vector<std::vector<int>> grid;
};

#endif
