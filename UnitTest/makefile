CC=g++ -g -Wall -O0
# for profiling
# CC=g++ -g -Wall -O0 -pg

all: runner

runner: runner.cpp
	$(CC) $^ -o $@

runner.cpp: Test*.hpp
	cxxtestgen.pl --error-printer -o $@ $^

clean:
	$(RM) runner.cpp runner *.txt

.PHONY: all
