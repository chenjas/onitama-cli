.PHONY: all

CXXFLAGS=-Wall -g

all: onitama-cli

onitama-cli: onitama-cli.o game.o card.o state.o player.o board.o
	g++ $(CXXFLAGS) -o onitama-cli $^

%.o: %.c game.h card.h state.h player.h board.h
	g++ $(CXXFLAGS) -c $<

clean:
	rm -f *.o onitama-cli *.exe

