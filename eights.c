/*
 * John Goettsche
 * CS 470
 * Assignment 2
 * A* search for 8 puzzle
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data.h"

int success = 0;
Board *solution = NULL;
Board *goal;
Board *start;
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

Board *move(Node *current, Move thisMove, int f){
	Board *newBoard;
	int x = thisMove.x;
	int y = thisMove.y;
	int currentX = current->b->openX;
	int currentY = current->b->openY;
	int mov;
	if(current->b->tile[currentX + x][currentY + y] > 0){
		if((newBoard = (Board *)calloc(1, sizeof(Board))) == NULL) exit(1);
		insertTiles(newBoard, current->b->numbers);
		newBoard->tile[currentX + x][currentY + y] = current->b->tile[currentX][currentY];
		newBoard->tile[currentX][currentY] = current->b->tile[currentX + x][currentY + y];
		mov = newBoard->tile[currentX][currentY];
		completeBoard(current->b, newBoard, mov, f);
		return newBoard;
	}
	return NULL;
}

int main(){
	//set up moves
	Move moves[4] ={{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
	
	//set up hash table
	HashTable *hashTable;
	int tableSize = pow(SIZE, 10) - SIZE + 1;

	int nos[SIZE * SIZE];
	int g[SIZE * SIZE];
	char *nums = (char *)calloc(SIZE * SIZE, sizeof(char));
	//char nums[9] = {'7', '2', '4', '5', '6', '0', '8', '3', '1'};
	nums = readData();
	char *gl = (char *)calloc(SIZE * SIZE, sizeof(char));
	//char gl[9] =  {'2', '4', '1', '7', '8', '6', '5', '0', '3'};
	gl = readData();
	int i;
	//converts char* to int*
	for(i = 0; i < SIZE * SIZE; i++) nos[i] = (int)nums[i] - '0';
	for(i = 0; i < SIZE * SIZE; i++) g[i] = (int)gl[i] - '0';
	
	goal = (Board *)calloc(1, sizeof(Board));
	insertTiles(goal, g);
	setNumbers(goal);
	
	start = (Board *)calloc(1, sizeof(Board));
	insertTiles(start, nos);
	setNumbers(start);
	start->depth = 0;
	
	Queue *queue;
	
	int f;
	for (f = 0; f < 5; f++){
		success = 0;
		hashTable = (HashTable *)createHashTable(tableSize);
		solution = (Board *)calloc(1, sizeof(Board));
		Board *board = (Board *)calloc(1, sizeof(Board));
		board = start;
		switch(f){
			case 0:
				board->f = getH(board);
				break;
			case 1:
				board->f = getHout(board);
				break;
			case 2:
				board->f = getHmanhattan(board);
				break;
			case 3:
				board->f = getHgreat2(board);
				break;
			case 4:
				board->f = getHgreat3(board);
				break;
			default:
				printf("error\n");
		}
		//set up queue
		queue = (Queue *)createQueue();
		int error = insert(queue, board);
		Node *current;
		Board *newBoard;
		int m;
		int fVal;
		int tries = 0;
		//iterate through queue until done
		while(!success){	
	//printf("*");
			current = queue->head;
			if((fVal = lookupBoard(hashTable, current->b)) == -1){
				//tries++;
				error = addBoard(hashTable, current->b);
				for(m = 0; m < 4; m++){
					if(!success) {
						if((newBoard = (Board *)calloc(1, sizeof(Board))) == NULL) return 1;
						if(newBoard = move(current, moves[m], f)){
							//tries++;
							if(newBoard->value == goal->value){
								success = 1;
								solution = newBoard;
							}
							if((fVal = lookupBoard(hashTable, newBoard)) == -1){
								tries++;
								error = insert(queue, newBoard);
								/*error = addBoard(hashTable, newBoard);*/
							} else if(newBoard->f < fVal) {
								tries++;
								replace(queue, newBoard); 
							} 
						}
					}
				}
			
			}
			pop(queue);
			if(queue->head == NULL)printf("Empty Queue\n");
		}
		//print out results
		printf("\nTRIES:  %d\n", tries);
		printf("COST:  %d\n", solution->depth);
		printf("EST. DIST. START TO GOAL:  %d\n", start->f);
		printf("\nSOLUTION:  ");
		printPath(solution);
		int ql = getQueueLength(queue);
		printf("QUEUE LEN:  %d\n\n", ql);
		//printBoard(solution);
	}
	return 1;
}
