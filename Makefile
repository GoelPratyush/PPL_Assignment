main: string_utils.o grammar.o tokenizer.o main.c
	gcc string_utils.o grammar.o tokenizer.o main.c -o main

tokenizer.o: tokenizer.c tokenizer.h
	gcc -c tokenizer.c

grammar.o: string_utils.o grammar.c grammar.h
	gcc -c grammar.c

string_utils.o: string_utils.c string_utils.h globals.h
	gcc -c string_utils.c

clean:
	rm -rf main
	rm -rf *.o
