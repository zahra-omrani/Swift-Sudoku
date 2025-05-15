#pragma once
#include <iostream>

class Board {
private:
    int grid[9][9];
public:
    void loadFromArray(int puzzle[9][9]);
    int (&getGrid())[9][9];  // Return reference to 9x9 grid
    void print() const;
};



