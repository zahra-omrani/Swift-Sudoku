#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

class Board {
private:
    int grid[9][9];
public:
    void load(const std::string& filename);
    int at(int row, int col) const;
    void set(int row, int col, int val);
    void print() const;
};

#endif
