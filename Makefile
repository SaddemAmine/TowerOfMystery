# -*- Makefile -*-

prog: main.o fn.o
	gcc main.o fn.o -o prog -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image -g

main.o: main.c
	gcc main.c -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -g

fn.o: fn.c
	gcc fn.c -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -g
clean:
	rm *.o prog -f
