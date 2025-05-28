#include "ParallelSolver.h"
#include "Board.h"

#include <thread>
#include <vector>
#include <atomic>
#include <algorithm>

#ifdef __linux__
#include <pthread.h>
#endif

void ParallelSolver::solveBoards(const std::vector<std::string>& boards, int threadCount) {
    const size_t batch_size = 32;
    std::atomic<size_t> next_batch{0};
    std::vector<std::thread> workers;

    threadCount = std::min(threadCount, static_cast<int>(std::thread::hardware_concurrency()));
    workers.reserve(threadCount);

    auto worker_task = [&]() {
        Board solver;
        while (true) {
            const size_t batch_start = next_batch.fetch_add(batch_size);
            if (batch_start >= boards.size()) break;

            const size_t batch_end = std::min(batch_start + batch_size, boards.size());
            for (size_t i = batch_start; i < batch_end; ++i) {
                solver.loadFromString(boards[i]);
                solver.solve();
            }
        }
    };

    for (int i = 0; i < threadCount; ++i) {
        workers.emplace_back([&, i] {
#ifdef __linux__
            cpu_set_t cpuset;
            CPU_ZERO(&cpuset);
            CPU_SET(i % std::thread::hardware_concurrency(), &cpuset);
            pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
#endif
            worker_task();
        });
    }

    for (auto& worker : workers) {
        if (worker.joinable()) worker.join();
    }
}
