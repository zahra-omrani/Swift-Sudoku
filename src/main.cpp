#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <iomanip>
#include <mutex>
#include <atomic>

#include "SequentialSolver.h"
#include "MultiThreadSolver.h"
#include "Timer.h"
#include "Board.h"

std::vector<std::string> loadBoards(const std::string& filename, int count) {
    std::vector<std::string> boards;
    std::ifstream file(filename);
    std::string line;
    while (boards.size() < static_cast<size_t>(count) && std::getline(file, line)) {
        if (!line.empty()) boards.push_back(line);
    }
    return boards;
}

class MultiThreadSolverWithProgress {
public:
    MultiThreadSolverWithProgress(int threadCount) : numThreads(threadCount) {}

    void solveBoardsWithProgress(const std::vector<std::string>& boards) {
        std::atomic<size_t> index(0);
        std::atomic<size_t> completed(0);
        size_t total = boards.size();
        std::mutex coutMutex;

        std::vector<std::thread> threads;
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back([&, i]() {
                while (true) {
                    size_t currentIndex = index++;
                    if (currentIndex >= total) break;

                    Board board;
                    board.loadFromString(boards[currentIndex]);
                    board.solve();

                    {
                        std::lock_guard<std::mutex> lock(coutMutex);
                        ++completed;
                        float progress = (float)completed / total * 100;
                        std::cout << "\rProgress: [" << std::string(progress / 5, '#')
                                  << std::string(20 - progress / 5, ' ') << "] "
                                  << std::fixed << std::setprecision(1) << progress << "% "
                                  << std::flush;
                    }
                }
            });
        }

        for (auto& t : threads) t.join();
        std::cout << std::endl;
    }

private:
    int numThreads;
};

int main() {
    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::string> boards = loadBoards("sudoku.txt", 100);

    // Sequential solving with timing
    std::cout << "Solving sequentially...\n";
    Timer seqTimer;
    SequentialSolver seqSolver;
    
    seqTimer.start();
    seqSolver.solveBoards(boards);
    seqTimer.stop();
    double sequentialTime = seqTimer.elapsedMilliseconds();

    // Parallel solving with progress and timing
    std::cout << "\nSolving in parallel with " << numThreads << " threads...\n";
    Timer parTimer;
    MultiThreadSolverWithProgress parSolver(numThreads);
    
    parTimer.start();
    parSolver.solveBoardsWithProgress(boards);
    parTimer.stop();
    double parallelTime = parTimer.elapsedMilliseconds();

    // Summary table
    std::cout << "\n================ Execution Time Summary ================\n";
    std::cout << std::left << std::setw(30) << "Solver"
              << std::setw(15) << "Time (ms)\n";
    std::cout << "--------------------------------------------------------\n";
    std::cout << std::left << std::setw(30) << "SequentialSolver"
              << std::setw(15) << sequentialTime << "\n";
    std::cout << std::left << std::setw(30) << "MultiThreadSolver (" 
              << numThreads << " threads)" << std::setw(15) << parallelTime << "\n";
    std::cout << "========================================================\n";

    // Calculate and display speedup
    if (sequentialTime > 0 && parallelTime > 0) {
        double speedup = sequentialTime / parallelTime;
        std::cout << "\nSpeedup: " << std::fixed << std::setprecision(2) 
                  << speedup << "x\n";
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.get();

    return 0;
}