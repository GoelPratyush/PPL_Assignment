main: string_utils.o grammar.o
	gcc string_utils.o grammar.o main.c -o main

grammar.o: string_utils.o grammar.c grammar.h
	gcc -c grammar.c

string_utils.o: string_utils.c string_utils.h globals.h
	gcc -c string_utils.c

clean:
	rm -rf *.o
