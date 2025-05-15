CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

TEST_SRC = tests/test.cpp
TEST_BIN = run_tests
CATCH_SRC = src/catch_amalgamated.cpp
PROJECT_SRC = $(filter-out src/main.cpp src/catch_amalgamated.cpp, $(wildcard src/*.cpp))

test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $(TEST_BIN) $(TEST_SRC) $(CATCH_SRC) $(PROJECT_SRC)
	./$(TEST_BIN)

clean:
	rm -f $(TEST_BIN)
