CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall
SRCDIR = src
INCDIR = include
TARGET = sudoku

SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
