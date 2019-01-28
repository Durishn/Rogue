all:
	gcc -Wall -g -ansi src/rogue.c src/roguefunctions.c src/roguegameplayfunctions.c -o bin/rogue -Iinclude -lncurses