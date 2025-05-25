## Swift Sudoku

This project is a high-performance parallel Sudoku solver designed to process and solve multiple Sudoku boards efficiently. It leverages multithreading to optimize performance and supports configurable thread counts.

### Features
- **Parallel Processing**: Solves multiple Sudoku boards simultaneously using multithreading.
- **Performance Measurement**: Includes a timer to measure execution time for performance analysis.
- **Configurable Thread Count**: Automatically detects the optimal number of threads based on hardware concurrency.

### How It Works
1. **Load Sudoku Boards**: The program reads Sudoku boards from a file (e.g., `sudoku.txt`).
2. **Solve Boards**: Boards are solved in parallel using the `ParallelSolver` class.
3. **Performance Tracking**: Execution time is measured and reported.

### Prerequisites
- C++17 or later
- A compiler supporting multithreading (e.g., GCC, Clang, MSVC)
- `sudoku.txt` file containing Sudoku puzzles

### Usage
1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-folder>
