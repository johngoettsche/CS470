#include <stdio.h>
#include <stdlib.h>
#include "data.h"

int main(){
	int nos[SIZE * SIZE] = { 1, 2, 3, 4, 0, 5, 6, 7, 8 };
	  
	Board *board = (Board *)calloc(1, sizeof(Board));
	insertTiles(board, nos);
	Node *head = (Node *)calloc(1, sizeof(Node));
	put(head, board);
	Board *current;
	
	int count = 0;
	while(count < 10){
		
		current = head->b;
		printBoard(current);
		
		int x = current->openX;
		int y = current->openY;
		if(current->tile[x][y - 1] > 0){
			Board *newBoard = (Board *)calloc(1, sizeof(Board));
			insertTiles(newBoard, current->numbers);
			newBoard->tile[x][y - 1] = current->tile[x][y];
			newBoard->tile[x][y] = current->tile[x][y - 1];
			put(head, newBoard);
		}
		if(current->tile[x + 1][y] > 0){
			Board *newBoard = (Board *)calloc(1, sizeof(Board));
			insertTiles(newBoard, current->numbers);
			newBoard->tile[x + 1][y] = current->tile[x][y];
			newBoard->tile[x][y] = current->tile[x + 1][y];
			put(head, newBoard);
		}
		if(current->tile[x][y + 1] > 0){
			Board *newBoard = (Board *)calloc(1, sizeof(Board));
			insertTiles(newBoard, current->numbers);
			newBoard->tile[x][y + 1] = current->tile[x][y];
			newBoard->tile[x][y] = current->tile[x][y + 1];
			put(head, newBoard);
		}
		if(current->tile[x - 1][y] > 0){
			Board *newBoard = (Board *)calloc(1, sizeof(Board));
			insertTiles(newBoard, current->numbers);
			newBoard->tile[x - 1][y] = current->tile[x][y];
			newBoard->tile[x][y] = current->tile[x - 1][y];
			put(head, newBoard);
		}
		head = head->next;
		count++;
	}
	printf("end of program");
	return 0;
}