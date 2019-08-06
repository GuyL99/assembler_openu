assembler: asmbl.o 
	gcc -g -ansi -Wall -pedantic asmbl.o -o assembler
	@echo "done!"
asmbl.o: pre.c circ1.c output.c symch.c second.c dectobinary.c assem.c helpers.h
	gcc -c -ansi -Wall -pedantic assem.c -o asmbl.o

