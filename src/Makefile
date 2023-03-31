CC = gcc
CFLAGS = -Wall -Werror -Wextra
SOURCES = game_of_life.c

all: clean 
	$(CC) $(CFLAGS) -o game_of_life $(SOURCES) -lncurses

clean:
	-rm -rf *.o game_of_life