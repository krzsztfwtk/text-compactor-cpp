CXX=g++
CXXFLAGS=-std=c++20 -Wall -Wextra -pedantic-errors -O1

SRCS=$(filter-out ../sources/main.cpp, $(wildcard ../sources/*.cpp))
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
