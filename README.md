# 🧠 Swift Sudoku – High-Performance Parallel Solver in C++

This project is a **high-performance parallel Sudoku solver** designed to efficiently process and solve **thousands of Sudoku boards**. It leverages **multithreading** to optimize performance and supports **configurable thread counts** based on your system's hardware.

> 🏛️ **Developed as part of the Computer Architecture course**  
> 🎓 Master’s Program in **Artificial Intelligence and Data Engineering**  
> 🏫 **University of Pisa**

---

## 🚀 Key Features

- ⚙️ **Parallel Processing**: Solves multiple Sudoku boards simultaneously using task-based multithreading.
- 🧪 **Performance Measurement**: Built-in timers to analyze speed and thread efficiency.
- 🧠 **MRV Heuristic**: Uses Minimum Remaining Values to guide backtracking for faster solving.
- 🖥️ **Auto Thread Configuration**: Automatically detects and utilizes optimal thread count via hardware concurrency.
- 📄 **Batch Input Support**: Reads standard 81-character puzzles from a file (e.g., `sudoku.txt`).

---

## 🧩 How It Works

1. **Load Boards**: The solver reads puzzles from a file (`sudoku.txt`), each in a single line of 81 characters.
2. **Distribute Work**: Boards are distributed across multiple threads. Each thread solves independent puzzles.
3. **Solve with Speed**: MRV-enhanced backtracking ensures correctness with maximum speed.
4. **Track Performance**: Execution time is logged and analyzed for different thread counts.

---

## 📊 Performance Results

Tested on **10,000 puzzles** using an **Intel® Core™ i7-10th Gen** CPU.

- ⏱️ ~3.5× **speedup** using just 4 threads vs. sequential
- 📈 70%+ **efficiency** scaling with increasing threads
- ⚡ Smooth batch solving with near-zero contention

### ❌ Before Multithreading

<img src="before_mt.png" alt="Before Multithreading Performance" width="600"/>

### ✅ After Multithreading

<img src="after_mt.png" alt="After Multithreading Performance" width="600"/>

---

## 🛠️ Prerequisites

- C++17 or later
- A compiler supporting multithreading (e.g., GCC, Clang, MSVC)
- Input file: `sudoku.txt` with one 81-char puzzle per line

---

## ⚙️ How to Build and Run

### 🧱 Clone the Repository

```bash
git clone <repository-url>
cd <repository-folder>
