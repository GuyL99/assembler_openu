assembler: asmbl.o
	gcc -g -ansi -Wall -pedantic asmbl.o -o assembler
asmbl.o: pre.c assem.c helpers.h
	gcc -c -ansi -Wall -pedantic assem.c -o asmbl.o

