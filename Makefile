.PHONY: all

CFLAGS=-Wall

all: onitama-cli

onitama-cli: onitama-cli.o game.o card.o
	g++ $(CFLAGS) -o onitama-cli $^

%.o: %.c game.h card.h
	g++ $(CFLAGS) -c $<

clean:
	rm -f *.o onitama-cli

