# -*- Makefile -*-

prog: main.o fn.o
	gcc main.o fn.o -o prog -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g -lm

main.o: main.c
	gcc -c main.c -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g -lm

fn.o: fn.c
	gcc -c fn.c -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g -lm

test: test.c
	gcc test.c -o test -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g -lm

clean:
	rm *.o prog -f
