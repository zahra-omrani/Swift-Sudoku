#include "MultiThreadSolver.h"
#include "Board.h"
#include <mutex>
#include <atomic>
#include <iostream>

MultiThreadSolver::MultiThreadSolver(int threadCount)
    : numThreads(std::min(threadCount, static_cast<int>(std::thread::hardware_concurrency()))) {
}

// This overrides ISolver
void MultiThreadSolver::solveBoards(const std::vector<std::string>& boards) {
    solveBoards(boards, false); // delegate
}

// Your extended method
void MultiThreadSolver::solveBoards(const std::vector<std::string>& boards, bool enableOutput) {
    std::atomic<int> index(0);
    std::mutex coutMutex;

    std::vector<std::thread> threads;
    for (int t = 0; t < numThreads; ++t) {
        threads.emplace_back([&]() {
            while (true) {
                int i = index.fetch_add(1);
                if (i >= static_cast<int>(boards.size())) break;

                Board board;
                board.loadFromString(boards[i]);
                board.solve();

                if (enableOutput) {
                    std::lock_guard<std::mutex> lock(coutMutex);
                   // std::cout << "Solved board " << i << ": " << board.toString() << "\n";
                }
            }
            });
    }

    for (auto& t : threads) {
        t.join();
    }
}
