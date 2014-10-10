Eights : eights.o board.o data.o
	gcc -o puzzle eights.o board.o data.o -lm
	
eights.o : eights.c
	gcc -g -Wall -c eights.c -lm
	
board.o : board.c
	gcc -g -Wall -c board.c -lm
	
data.o : data.c
	gcc -g -Wall -c data.c