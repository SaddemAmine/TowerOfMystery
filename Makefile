# -*- Makefile -*-

prog: main.o fn.o
	gcc main.o fn.o -o prog -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g

main.o: main.c
	gcc -c main.c -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g

fn.o: fn.c
	gcc -c fn.c -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g

test: test.c
	gcc test.c -o test -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g

clean:
	rm *.o prog -f
