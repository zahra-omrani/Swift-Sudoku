#include "SequentialSolver.h"
#include "Board.h"
#include <iostream>

void SequentialSolver::solveBoards(const std::vector<std::string>& boards) {
    for (size_t i = 0; i < boards.size(); ++i) {
        Board board;
        board.loadFromString(boards[i]);
        board.solve();
        std::cout << "Solved board " << i << ": " << board.toString() << "\n";
    }
}
