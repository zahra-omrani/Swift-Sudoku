#include "Board.h"
#include "Timer.h"
#include "SingleThreadSolver.h"
#include "MultiThreadSolver.h"
#include <iostream>

int main() {
    Board board;
    board.load("sudoku.txt");

    std::cout << "Original Sudoku:\n";
    board.print();

    {
        Timer t("Single-threaded Solver");
        SingleThreadSolver solver;
        if (solver.solve(board)) {
            std::cout << "\nSolved (Single-thread):\n";
            board.print();
        } else {
            std::cout << "No solution found.\n";
        }
    }

    board.load("sudoku.txt");

    {
        Timer t("Multi-threaded Solver");
        MultiThreadSolver solver;
        if (solver.solve(board)) {
            std::cout << "\nSolved (Multi-thread):\n";
            board.print();
        } else {
            std::cout << "No solution found.\n";
        }
    }

    return 0;
}
