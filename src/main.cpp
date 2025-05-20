#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <iomanip>
#include <mutex>
#include <atomic>
#include <map>
#include <algorithm> // <--- ADD THIS LINE FOR std::sort

#include "SequentialSolver.h"
#include "MultiThreadSolver.h"
#include "Timer.h"
#include "Board.h"

// Re-using the loadBoards function
std::vector<std::string> loadBoards(const std::string& filename, int count) {
    std::vector<std::string> boards;
    std::ifstream file(filename);
    std::string line;
    while (boards.size() < static_cast<size_t>(count) && std::getline(file, line)) {
        if (!line.empty()) boards.push_back(line);
    }
    return boards;
}

int main() {
    int numBoardsToSolve = 100; // As in your example table
    std::vector<std::string> boards = loadBoards("sudoku.txt", numBoardsToSolve);

    // Store results for different thread counts
    // Key: thread count, Value: time in ms
    std::map<int, double> executionTimes;

    // --- 1. Sequential Solving (Threads = 1) ---
    std::cout << "Solving sequentially (1 thread) for " << numBoardsToSolve << " boards...\n";
    Timer seqTimer;
    SequentialSolver seqSolver;

    seqTimer.start();
    seqSolver.solveBoards(boards);
    seqTimer.stop();
    double sequentialTime = seqTimer.elapsedMilliseconds();
    executionTimes[1] = sequentialTime;
    std::cout << "Sequential time: " << sequentialTime << " ms\n\n";

    // --- 2. Parallel Solving with different thread counts ---
    // You can customize these thread counts based on your system's cores
    std::vector<int> threadCountsToTest = {2, 4, 8, 12, 16}; // Example thread counts
    // Add hardware_concurrency() if it's not already in the list
    int maxHardwareConcurrency = std::thread::hardware_concurrency();
    if (std::find(threadCountsToTest.begin(), threadCountsToTest.end(), maxHardwareConcurrency) == threadCountsToTest.end()) {
        threadCountsToTest.push_back(maxHardwareConcurrency);
    }
    // Sort to ensure consistent output order
    std::sort(threadCountsToTest.begin(), threadCountsToTest.end());


    for (int currentThreads : threadCountsToTest) {
        if (currentThreads == 1) continue; // Already done sequentially

        std::cout << "Solving in parallel with " << currentThreads << " threads for " << numBoardsToSolve << " boards...\n";
        Timer parTimer;
        MultiThreadSolver parSolver(currentThreads);

        parTimer.start();
        parSolver.solveBoards(boards); // Use your MultiThreadSolver
        parTimer.stop();
        double parallelTime = parTimer.elapsedMilliseconds();
        executionTimes[currentThreads] = parallelTime;
        std::cout << "Parallel time (" << currentThreads << " threads): " << parallelTime << " ms\n\n";
    }

    // --- 3. Generate and Display Performance Table ---
    std::cout << "\n================ Performance Table ================\n";
    std::cout << std::left << std::setw(10) << "Boards"
              << std::setw(10) << "Threads"
              << std::setw(15) << "Time (ms)"
              << std::setw(10) << "Speedup"
              << std::setw(10) << "Efficiency\n";
    std::cout << "---------------------------------------------------\n";

    double baseTime = executionTimes[1]; // Sequential time for speedup calculation

    for (const auto& pair : executionTimes) {
        int threads = pair.first;
        double time = pair.second;
        double speedup = (baseTime > 0) ? (baseTime / time) : 0.0;
        double efficiency = (threads > 0 && speedup > 0) ? (speedup / threads) : 0.0;

        std::cout << std::left << std::setw(10) << numBoardsToSolve
                  << std::setw(10) << threads
                  << std::setw(15) << std::fixed << std::setprecision(0) << time // Time as integer
                  << std::setw(10) << std::fixed << std::setprecision(2) << speedup
                  << std::setw(10) << std::fixed << std::setprecision(2) << efficiency << "\n";
    }
    std::cout << "===================================================\n";

    std::cout << "\nPress Enter to exit...";
    std::cin.get();

    return 0;
}