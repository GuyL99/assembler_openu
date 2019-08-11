assembler: asmbl.o 
	gcc -g -ansi -Wall -pedantic asmbl.o -o assembler
	@echo "done compiling!"
	@echo "<=====================>"
asmbl.o: prerun.o circ1.o circ2.o reinit.c assem.c helpers.h
	gcc -c -ansi -Wall -pedantic assem.c -o asmbl.o
	@echo "finished compiling the main"
	@echo "<===================-->"
circ2.o: output.c second.c helpers.h  
	gcc -c -ansi -Wall -pedantic second.c -o circ2.o
	@echo "finished compiling the second run"
	@echo "<=================---->"
circ1.o: symch.c circ1.c helpers.h
	gcc -c -ansi -Wall -pedantic circ1.c -o circ1.o
	@echo "finished compiling the first run"
	@echo "<==========----------->"
prerun.o: pre.c helpers.h
	@echo "<--------------------->"
	gcc -c -ansi -Wall -pedantic pre.c -o prerun.o
	@echo "finished compiling the prerun"
	@echo "<=====---------------->"
