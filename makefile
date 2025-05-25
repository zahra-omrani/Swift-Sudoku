# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -O2 -g -fopenmp
VTUNE_INCLUDE = -I/opt/intel/oneapi/vtune/latest/include
VTUNE_LIBS = -L/opt/intel/oneapi/vtune/latest/lib64 -littnotify

# Source files
SRCS = src/Board.cpp src/MultiThreadSolver.cpp src/SequentialSolver.cpp src/solveBoards.cpp src/Timer.cpp

# Targets
.PHONY: all clean

all: sudoku_solver

sudoku_solver: src/main.cpp $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpthread

sudoku_solver_vtune: src/main.cpp $(SRCS)
	$(CXX) $(CXXFLAGS) $(VTUNE_INCLUDE) -o $@ $^ -lpthread $(VTUNE_LIBS)
	@echo "Note: Run with 'source /opt/intel/oneapi/setvars.sh && ./sudoku_solver_vtune'"

clean:
	rm -f sudoku_solver sudoku_solver_vtune performance_results.csv