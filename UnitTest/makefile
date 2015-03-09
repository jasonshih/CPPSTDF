CC=g++ -g -Wall -O0
# for profiling
# CC=g++ -g -Wall -O0 -pg
CPPFLAGS += -Wall -I../include -I../src

all: runner

runner: runner.cpp
	$(CC) $(CPPFLAGS) $^ -o $@

runner.cpp: Test*.hpp
	cxxtestgen.pl --error-printer -o $@ $^

clean:
	$(RM) runner.cpp runner *.txt

.PHONY: all
