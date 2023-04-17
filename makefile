CXX = g++
CXXFLAGS =-std=c++20 -Wall -Wextra -pedantic-errors -O3

SRCDIR = src
BINDIR = bin
EXEC = $(BINDIR)/main
SRCS = $(wildcard $(SRCDIR)/*.cpp)

$(EXEC): $(SRCS)
	echo "Building to $(EXEC)"
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXEC)

.PHONY: all clean

all: $(EXEC)

run: $(EXEC)
	./$(EXEC)
