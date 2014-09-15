#include <stdio.h>
#include <stdlib.h>
#include "data.h"

int main(){
	int nos[SIZE * SIZE] = { 7, 2, 4, 5, 6, 0, 8, 3, 1 };
	int g[SIZE * SIZE] = { 2, 4, 1, 7, 8, 6, 5, 0, 3 };
	
	Board *goal = (Board *)calloc(1, sizeof(Board));
	insertTiles(goal, g);
	setNumbers(goal);
	setNumbers(goal);
	
	Board *board = (Board *)calloc(1, sizeof(Board));
	insertTiles(board, nos);
	setNumbers(board);
	board->depth = 0;
	setNumbers(board);
	
	Board *solution = (Board *)calloc(1, sizeof(Board));
	
	printf("\nSTART:\n");
	printBoard(board);
	printf("\nGOAL:\n");
	printBoard(goal);
	
	Node *head = (Node *)calloc(1, sizeof(Node));
	put(head, board);
	Board *current;
	
	int success = 0;
	while(!success){	
		current = head->b;
		
		int x = current->openX;
		int y = current->openY;
		int mov;
		if(!success && current->tile[x][y - 1] > 0){
			Board *newBoard = (Board *)calloc(1, sizeof(Board));
			insertTiles(newBoard, current->numbers);
			newBoard->tile[x][y - 1] = current->tile[x][y];
			newBoard->tile[x][y] = current->tile[x][y - 1];
			mov = newBoard->tile[x][y];
			completeBoard(current, newBoard, mov);
			if(newBoard->value == goal->value){
				success = 1;
				solution = newBoard;
			}
			put(head, newBoard);
		}
		if(!success && current->tile[x + 1][y] > 0){
			Board *newBoard = (Board *)calloc(1, sizeof(Board));
			insertTiles(newBoard, current->numbers);
			newBoard->tile[x + 1][y] = current->tile[x][y];
			newBoard->tile[x][y] = current->tile[x + 1][y];
			mov = newBoard->tile[x][y];
			completeBoard(current, newBoard, mov);
			if(newBoard->value == goal->value){
				success = 1;
				solution = newBoard;
			}
			put(head, newBoard);
		}
		if(!success && current->tile[x][y + 1] > 0){
			Board *newBoard = (Board *)calloc(1, sizeof(Board));
			insertTiles(newBoard, current->numbers);
			newBoard->tile[x][y + 1] = current->tile[x][y];
			newBoard->tile[x][y] = current->tile[x][y + 1];
			mov = newBoard->tile[x][y];
			completeBoard(current, newBoard, mov);
			if(newBoard->value == goal->value){
				success = 1;
				solution = newBoard;
			}
			put(head, newBoard);
		}
		if(!success && current->tile[x - 1][y] > 0){
			Board *newBoard = (Board *)calloc(1, sizeof(Board));
			insertTiles(newBoard, current->numbers);
			newBoard->tile[x - 1][y] = current->tile[x][y];
			newBoard->tile[x][y] = current->tile[x - 1][y];
			mov = newBoard->tile[x][y];
			completeBoard(current, newBoard, mov);
			if(newBoard->value == goal->value){
				success = 1;
				solution = newBoard;
			}
			put(head, newBoard);
		}
		head = head->next; //pop
	}
	printf("\nSOLUTION:  ");
	printPath(solution);
	printf("NUM MOVES:  %d\n", solution->depth);
	int ql = getQueueLength(head);
	printf("QUEUE LEN:  %d\n", ql);
	return 0;
}