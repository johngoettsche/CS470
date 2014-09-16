/*
 * John Goettsche
 * CS 470
 * Assignment 1
 * basic search for 8 puzzle
 */

#include <stdio.h>
#include <stdlib.h>
#include "data.h"

/*
 * function reads standard input.
 */
char *readData(){
	char *input;
	char *nums;
	input = (char *)calloc(SIZE * SIZE * 2 + 1, sizeof(char));
	input = fgets(input, SIZE * SIZE * 2 + 1, stdin);
	nums = (char *)calloc(SIZE * SIZE, sizeof(char));
	int i;
	// converts raw data to a string of characters negating the spaces.
	for(i = 0; i < SIZE * SIZE * 2; i += 2) nums[i / 2] = input[i];
	return nums;
}

int main(){
	int nos[SIZE * SIZE];
	int g[SIZE * SIZE];
	char *nums = (char *)calloc(SIZE * SIZE, sizeof(char));
	nums = readData();
	char *gl = (char *)calloc(SIZE * SIZE, sizeof(char));
	gl = readData();
	int i;
	//converts char* to int*
	for(i = 0; i < SIZE * SIZE; i++) nos[i] = (int)nums[i] - '0';
	for(i = 0; i < SIZE * SIZE; i++) g[i] = (int)gl[i] - '0';
	
	Board *goal = (Board *)calloc(1, sizeof(Board));
	insertTiles(goal, g);
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
	
	//set up queue
	Node *head = (Node *)calloc(1, sizeof(Node));
	head = put(head, board);
	Board *tail = head;
	Board *current;
	
	//iterate through queue until done
	int success = 0;
	while(!success){	
		current = head->b;
		
		int x = current->openX;
		int y = current->openY;
		int mov;
		//may move tile to the north
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
			tail = put(tail, newBoard);
		}
		//may move tile to the east
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
			tail = put(tail, newBoard);
		}
		//may move tile to the south
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
			tail = put(tail, newBoard);
		}
		//may move tile to the west
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
			tail = put(tail, newBoard);
		}
		head = head->next; //pop
	}
	//print out results
	printf("\nSOLUTION:  ");
	printPath(solution);
	printf("NUM MOVES:  %d\n", solution->depth);
	int ql = getQueueLength(head);
	printf("QUEUE LEN:  %d\n", ql);
	return 0;
}