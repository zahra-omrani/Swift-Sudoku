#include "MultiThreadSolver.h"
#include "Board.h"
#include <atomic>
#include <iostream>

MultiThreadSolver::MultiThreadSolver(int threadCount) : numThreads(threadCount) {}

void MultiThreadSolver::solveBoards(const std::vector<std::string>& boards) {
    std::atomic<size_t> index(0);

    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&]() {
            while (true) {
                size_t currentIndex = index++;
                if (currentIndex >= boards.size()) break;

                Board board;
                board.loadFromString(boards[currentIndex]);
                board.solve();
                std::cout << "Solved board " << currentIndex << ": " << board.toString() << "\n";
            }
        });
    }

    for (auto& t : threads) {
        t.join();
    }
}
