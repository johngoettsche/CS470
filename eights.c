/*
 * John Goettsche
 * CS 470
 * Assignment 1
 * basic search for 8 puzzle
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
	//set up hash table
	HashTable *hashTable;
	int tableSize = pow(SIZE, 6) - SIZE + 1;
	hashTable = (HashTable *)createHashTable(tableSize);

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
	Queue *queue = (Queue *)createQueue();
	int error = put(queue, board);
	printf("%d\n", error);
	if(queue->head == NULL)printf("no current head\n");

	//Board *tail = head;
	Node *current;
	
	//iterate through queue until done
	int success = 0;
	printf("starting while\n");
	while(!success){	
		printf("set current\n");
		if(queue->head == NULL)printf("no current head\n");
		current = queue->head;
		
		if(current == NULL)printf("no current node\n");
		if(current->b == NULL)printf("no current board\n");
		if(current->b->openX == NULL)printf("no openX\n");
		
		int x = current->b->openX;
		int y = current->b->openY;
		int mov;
		//may move tile to the north
		printf("moves\n");
		if(!success && current->b->tile[x][y - 1] > 0){
			Board *newBoard = (Board *)calloc(1, sizeof(Board));
			insertTiles(newBoard, current->b->numbers);
			newBoard->tile[x][y - 1] = current->b->tile[x][y];
			newBoard->tile[x][y] = current->b->tile[x][y - 1];
			mov = newBoard->tile[x][y];
			completeBoard(current->b, newBoard, mov);
			if(newBoard->value == goal->value){
				success = 1;
				solution = newBoard;
			}
			if(!success && lookupBoard(hashTable, newBoard) == NULL){
				error = put(queue, newBoard);
				addBoard(hashTable, newBoard);
			}
		}
		//may move tile to the east
		if(!success && current->b->tile[x + 1][y] > 0){
			Board *newBoard = (Board *)calloc(1, sizeof(Board));
			insertTiles(newBoard, current->b->numbers);
			newBoard->tile[x + 1][y] = current->b->tile[x][y];
			newBoard->tile[x][y] = current->b->tile[x + 1][y];
			mov = newBoard->tile[x][y];
			completeBoard(current->b, newBoard, mov);
			if(newBoard->value == goal->value){
				success = 1;
				solution = newBoard;
			}
			if(!success && lookupBoard(hashTable, newBoard) == NULL){
				error = put(queue, newBoard);
				//tail = put(tail, newBoard);
				addBoard(hashTable, newBoard);
			}
		}
		//may move tile to the south
		if(!success && current->b->tile[x][y + 1] > 0){
			Board *newBoard = (Board *)calloc(1, sizeof(Board));
			insertTiles(newBoard, current->b->numbers);
			newBoard->tile[x][y + 1] = current->b->tile[x][y];
			newBoard->tile[x][y] = current->b->tile[x][y + 1];
			mov = newBoard->tile[x][y];
			completeBoard(current->b, newBoard, mov);
			if(newBoard->value == goal->value){
				success = 1;
				solution = newBoard;
			}
			if(!success && lookupBoard(hashTable, newBoard) == NULL){
				error = put(queue, newBoard);
				//tail = put(tail, newBoard);
				addBoard(hashTable, newBoard);
			}
		}
		//may move tile to the west
		if(!success && current->b->tile[x - 1][y] > 0){
			Board *newBoard = (Board *)calloc(1, sizeof(Board));
			insertTiles(newBoard, current->b->numbers);
			newBoard->tile[x - 1][y] = current->b->tile[x][y];
			newBoard->tile[x][y] = current->b->tile[x - 1][y];
			mov = newBoard->tile[x][y];
			completeBoard(current->b, newBoard, mov);
			if(newBoard->value == goal->value){
				success = 1;
				solution = newBoard;
			}
			if(!success && lookupBoard(hashTable, newBoard) == NULL){
				error = put(queue, newBoard);
				//tail = put(tail, newBoard);
				addBoard(hashTable, newBoard);
			}
		}
		printf("pop\n");
		pop(queue);
		//head = head->next; //pop
	}
	//print out results
	printf("\nSOLUTION:  ");
	printPath(solution);
	printf("NUM MOVES:  %d\n", solution->depth);
	int ql = getQueueLength(queue);
	printf("QUEUE LEN:  %d\n", ql);
	return 0;
}