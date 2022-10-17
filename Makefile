CFLAGS = -std=c++17 -ggdb
LDFLAGS = -lSDL2
SRCFILES = $(wildcard *.cpp) $(wildcard modules/*.cpp)

.PHONY: main

all: main

main:
	g++ $(CFLAGS) $(SRCFILES) -o main $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o main