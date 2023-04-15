CXX=g++
CXXFLAGS=-std=c++20 -Wall -Wextra -pedantic-errors -O1

SRCS=$(filter-out ../src/main.cpp, $(wildcard ../src/*.cpp))
TESTS=$(wildcard *.cpp)
EXES=$(patsubst %.cpp, %, $(TESTS))

all: $(EXES)
	@for exe in $(EXES); do \
		echo "Running $$exe..."; \
		./$$exe; \
		rm -f $$exe; \
	done

%: %.cpp $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(EXES)
