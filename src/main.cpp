#include "Utils.h"
#include "ParallelSolver.h"
#include "SequentialSolver.h"
#include "Timer.h"

#include <iostream>
#include <chrono>
#include <thread>

constexpr int DEFAULT_BOARD_COUNT = 10000;

int main() {
    auto boards = loadBoards("sudoku.txt", DEFAULT_BOARD_COUNT);
    if (boards.empty()) return 1;

    const int max_threads = std::thread::hardware_concurrency();

    // Sequential solver timing
    SequentialSolver seqSolver;
    Timer seqTimer;
    seqTimer.start();
    seqSolver.solveBoards(boards);
    seqTimer.stop();
    std::cout << "Sequential Solver Time: " << seqTimer.elapsedMilliseconds() << " ms\n\n";

    // Parallel solver timing
    ParallelSolver parSolver;
    Timer parTimer;
    parTimer.start();
    parSolver.solveBoards(boards, max_threads);
    parTimer.stop();
    std::cout << "Parallel Solver Time (" << max_threads << " threads): "
              << parTimer.elapsedMilliseconds() << " ms\n";

    return 0;
}
