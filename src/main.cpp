#include "Board.h"
#include "SequentialSolver.h"
#include "SingleThreadSolver.h"
#include "MultiThreadSolverV1.h"
#include "MultiThreadSolverV2.h"
#include "MultiThreadSolverV3.h"
#include "Timer.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip> // for std::setprecision

void printStats(const std::vector<double>& times, const std::string& label) {
    double avg = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
    double min = *std::min_element(times.begin(), times.end());
    double max = *std::max_element(times.begin(), times.end());

    std::vector<double> sorted = times;
    std::sort(sorted.begin(), sorted.end());
    double median = sorted.size() % 2 == 0 ?
                    (sorted[sorted.size() / 2 - 1] + sorted[sorted.size() / 2]) / 2.0 :
                    sorted[sorted.size() / 2];

    std::cout << std::fixed << std::setprecision(6);  // Show 6 decimal digits

    std::cout << "Statistics for " << label << ":\n";
    std::cout << "  Average time: " << avg << " ms\n";
    std::cout << "  Minimum time: " << min << " ms\n";
    std::cout << "  Maximum time: " << max << " ms\n";
    std::cout << "  Median time : " << median << " ms\n\n";
}

template <typename Solver>
void benchmarkSolver(Solver& solver, const int (&puzzle)[9][9], const std::string& label, int runs = 100) {
    std::vector<double> times;

    for (int i = 0; i < runs; ++i) {
        Board board;
        board.loadFromArray(puzzle);

        Timer timer;
        timer.start();
        solver.solve(board);
        timer.stop();

        if (i == 0) {
            std::cout << label << " result:\n";
            board.print();
        }

        times.push_back(static_cast<double>(timer.elapsedMilliseconds()));
    }

    printStats(times, label);
}

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

    const int runs = 1000;

    // === NEW: Ask user how many threads to use ===
    int thread_count;
    std::cout << "Enter the number of threads for MultiThreadSolverV3: ";
    std::cin >> thread_count;
    std::cin.ignore(); // flush newline for later std::cin.get()

    SequentialSolver sequentialSolver;
    SingleThreadSolver singleThreadSolver;
    MultiThreadSolverV3 multiThreadSolverV3(thread_count);  // pass thread count

    std::cout << "Running SequentialSolver " << runs << " times...\n";
    benchmarkSolver(sequentialSolver, puzzle, "SequentialSolver", runs);

    std::cout << "Running SingleThreadSolver " << runs << " times...\n";
    benchmarkSolver(singleThreadSolver, puzzle, "SingleThreadSolver", runs);

    std::cout << "Running MultiThreadSolverV3 with " << thread_count << " threads " << runs << " times...\n";
    benchmarkSolver(multiThreadSolverV3, puzzle, "MultiThreadSolverV3", runs);

    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;
}
