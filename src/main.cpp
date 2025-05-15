#include "Board.h"
#include "SequentialSolver.h"
#include "SingleThreadSolver.h"
#include "Timer.h"
#include <iostream>

int main() {
    int puzzle[9][9] = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };

    Board board;
    board.loadFromArray(puzzle);

    std::cout << "Initial Sudoku board:\n";
    board.print();

    SingleThreadSolver solver;

    {
        Timer timer("Sudoku solving");
        if (solver.solve(board)) {
            std::cout << "\nSudoku solved successfully:\n";
            board.print();
        } else {
            std::cout << "\nFailed to solve the Sudoku.\n";
        }
    }

    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;
}
