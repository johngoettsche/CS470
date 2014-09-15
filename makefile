Eights : eights.o board.o data.o
	gcc -o Eights eights.o board.o data.o

eights.o : eights.c
	gcc -c eights.c
	
board.o : board.c
	gcc -c board.c
	
data.o : data.c
	gcc -c data.c