#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <algorithm>
#include <chrono>
#include <memory>
#include <map>
#include <mutex>
#include <condition_variable>
#include <queue>          // Added for std::queue
#include <functional>     // Added for std::function
#include <utility>

// VTune macros
#ifdef USE_VTUNE
#include <ittnotify.h>
static __itt_domain* domain = __itt_domain_create("Sudoku.Profiling");
#define VTUNE_TASK_BEGIN(name) __itt_task_begin(domain, __itt_null, __itt_null, __itt_string_handle_create(name))
#define VTUNE_TASK_END() __itt_task_end(domain)
#else
#define VTUNE_TASK_BEGIN(name)
#define VTUNE_TASK_END()
#endif

#include "Board.h"
#include "Timer.h"

constexpr int DEFAULT_BOARD_COUNT = 10000;
constexpr int WARMUP_RUNS = 1;
constexpr int WORK_CHUNK_SIZE = 10;

#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>

class ThreadPool {
public:
    explicit ThreadPool(size_t threads) 
        : stop(false), 
          active_threads(std::min(threads, static_cast<size_t>(std::thread::hardware_concurrency()))),
          busy_count(0) {
        
        workers.reserve(active_threads);
        for(size_t i = 0; i < active_threads; ++i) {
            workers.emplace_back([this] { worker_loop(); });
        }
    }

    ~ThreadPool() {
        shutdown();
    }

    template<class F>
    void enqueue(F&& task) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.emplace(std::forward<F>(task));
        }
        condition.notify_one();
    }

    template<class F, class... Args>
    void enqueue_batch(size_t batch_size, F&& func, Args&&... args) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        for(size_t i = 0; i < batch_size; ++i) {
            tasks.emplace([=] { func(args...); });
        }
        condition.notify_all();
    }

    size_t getThreadCount() const { return active_threads; }
    size_t getPendingTasks() const { return tasks.size(); }
    size_t getBusyThreads() const { return busy_count.load(); }

    void shutdown() {
        if(stop) return;
        
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        
        condition.notify_all();
        for(auto& worker : workers) {
            if(worker.joinable()) worker.join();
        }
    }

private:
    void worker_loop() {
        while(true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                condition.wait(lock, [this] { 
                    return stop || !tasks.empty(); 
                });

                if(stop && tasks.empty()) return;
                
                task = std::move(tasks.front());
                tasks.pop();
                ++busy_count;
            }

            try {
                task();
            } catch (...) {
                --busy_count;
                throw;
            }

            --busy_count;
        }
    }

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    mutable std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
    std::atomic<size_t> busy_count;
    size_t active_threads;
};

class ParallelSolver {
public:
    void solveBoards(const std::vector<std::string>& boards, int threadCount) {
        const size_t batch_size = 32; // Boards per batch
        std::atomic<size_t> next_batch{0};
        std::vector<std::thread> workers;
        
        threadCount = std::min(threadCount, static_cast<int>(std::thread::hardware_concurrency()));
        workers.reserve(threadCount);

        auto worker_task = [&]() {
            Board solver;
            while(true) {
                const size_t batch_start = next_batch.fetch_add(batch_size);
                if(batch_start >= boards.size()) break;
                
                const size_t batch_end = std::min(batch_start + batch_size, boards.size());
                for(size_t i = batch_start; i < batch_end; ++i) {
                    solver.loadFromString(boards[i]);
                    solver.solve();
                }
            }
        };

        // Set thread affinity (Linux example)
        for(int i = 0; i < threadCount; ++i) {
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

        for(auto& worker : workers) {
            if(worker.joinable()) worker.join();
        }
    }
};



std::vector<std::string> loadBoards(const std::string& filename, int count) {
    std::vector<std::string> boards;
    boards.reserve(count);  // Critical pre-allocation
    
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return boards;
    }

    std::string line;
    while(boards.size() < static_cast<size_t>(count) && std::getline(file, line)) {
        if(!line.empty()) {
            boards.emplace_back(std::move(line));  // Move semantics
        }
    }
    return boards;
}

void runWarmup(const std::vector<std::string>& boards, int threadCount) {
    ParallelSolver solver;
    for(int i = 0; i < WARMUP_RUNS; ++i) {
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

int main() {
    // Load boards first
    auto boards = loadBoards("sudoku.txt", 10000);
    if(boards.empty()) return 1;

    // Test with optimal thread count
    const int max_threads = std::thread::hardware_concurrency();
    ParallelSolver solver;

    auto start = std::chrono::high_resolution_clock::now();
    solver.solveBoards(boards, max_threads);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Solved " << boards.size() << " boards in "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
              << "ms\n";

    return 0;
}