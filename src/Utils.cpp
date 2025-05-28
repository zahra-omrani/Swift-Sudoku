#include "Utils.h"
#include "ParallelSolver.h"
#include "Timer.h"

#include <fstream>
#include <iostream>

#ifdef USE_VTUNE
#include <ittnotify.h>
static __itt_domain* domain = __itt_domain_create("Sudoku.Profiling");
#define VTUNE_TASK_BEGIN(name) __itt_task_begin(domain, __itt_null, __itt_null, __itt_string_handle_create(name))
#define VTUNE_TASK_END() __itt_task_end(domain)
#else
#define VTUNE_TASK_BEGIN(name)
#define VTUNE_TASK_END()
#endif

std::vector<std::string> loadBoards(const std::string& filename, int count) {
    std::vector<std::string> boards;
    boards.reserve(count);

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return boards;
    }

    std::string line;
    while (boards.size() < static_cast<size_t>(count) && std::getline(file, line)) {
        if (!line.empty()) {
            boards.emplace_back(std::move(line));
        }
    }

    return boards;
}

void runWarmup(const std::vector<std::string>& boards, int threadCount) {
    ParallelSolver solver;
    for (int i = 0; i < 1; ++i) {  // WARMUP_RUNS = 1
        solver.solveBoards(boards, threadCount);
    }
}

double measureParallel(const std::vector<std::string>& boards, int threadCount) {
    VTUNE_TASK_BEGIN("Parallel");
    Timer timer;
    ParallelSolver solver;

    timer.start();
    solver.solveBoards(boards, threadCount);
    timer.stop();

    VTUNE_TASK_END();
    return timer.elapsedMilliseconds();
}
