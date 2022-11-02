CFLAGS = -std=c++17 -ggdb -D__LINUX_ALSA__
LDFLAGS = -lSDL2 -lasound -lpthread
SRCFILES = $(wildcard *.cpp) $(wildcard modules/*.cpp)

.PHONY: main

all: main

main:
	g++ $(CFLAGS) $(SRCFILES) -o main $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o main