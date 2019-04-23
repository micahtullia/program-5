CC=g++
CXXFLAGS=-g --std=c++11
WIDGET=term.o application.o keystream.o widget.o
TARGETS=sokoban

all: $(TARGETS)
sokoban: $(WIDGET) sokoban.o boulder.o level.o player.o hole.o
clean:
	rm -f $(TARGETS) *.o