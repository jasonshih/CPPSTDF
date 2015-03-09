CC=g++ -g -Wall -O0
# for profiling
# CC=g++ -g -Wall -O0 -pg
CPPFLAGS += -DOLD_STDF_VERSION=1 -Wall -I../include

all:
	$(CC) $(CPPFLAGS) *.cpp -o runner

clean:
	$(RM) runner

.PHONY: all clean
