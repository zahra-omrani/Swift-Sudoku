#include "Utils.h"
#include "ParallelSolver.h"
#include "Timer.h"

#include <iostream>
#include <chrono>
#include <thread>

constexpr int DEFAULT_BOARD_COUNT = 10000;

int main() {
    auto boards = loadBoards("sudoku.txt", DEFAULT_BOARD_COUNT);
    if (boards.empty()) return 1;

    const int max_threads = std::thread::hardware_concurrency();
    ParallelSolver solver;

    auto start = std::chrono::high_resolution_clock::now();
    solver.solveBoards(boards, max_threads);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Solved " << boards.size() << " boards in "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\n";

    return 0;
}
