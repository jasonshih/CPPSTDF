CC=g++ -g -Wall -O0

all: runner

runner: runner.cpp
	$(CC) $^ -o $@

runner.cpp: Test*.hpp
	cxxtestgen.pl --error-printer -o $@ $^

clean:
	$(RM) runner.cpp runner *.txt

.PHONY: all
