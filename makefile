Eights : eights.o board.o data.o
	gcc -o puzzle eights.o board.o data.o -lm
	
eights.o : eights.c
	gcc -c eights.c -lm
	
board.o : board.c
	gcc -c board.c -lm
	
data.o : data.c
	gcc -c data.c