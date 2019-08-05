assembler: asmbl.o 
	gcc -g -ansi -Wall -pedantic asmbl.o -o assembler
asmbl.o: pre.c circ1.c assem.c symch.c second.c dectobinary.c helpers.h
	gcc -c -ansi -Wall -pedantic assem.c -o asmbl.o

