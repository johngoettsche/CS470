/*
 * John Goettsche
 * CS 470
 * Assignment 1
 * board setup
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "board.h"

/* 
 * inserts the tile values from an array of integers as input.
 */
insertTiles(Board *board, int *nums){
	int i = 0;
	int y;
	int x;
	for(y = 1; y <= SIZE; y++){
		for(x = 1; x <= SIZE; x++){
			board->tile[x][y] = nums[i];
			i++;
		}
	}
}

/* 
 * numbers is an array of integers based on the configuration
 * of the board, it is used to transfer the configuration from
 * parent to child.
 */
setNumbers(Board *board){
	int i = 0;
	int x, y;
	for(y = 1; y <= SIZE; y++){
		for(x = 1; x <= SIZE; x++){
			if(board->tile[x][y] == 0){
				board->openX = x;
				board->openY = y;
			}
			board->numbers[i] = board->tile[x][y];
			i++;
		}
	}
	board->value = setPatternValue(board);
}

/* 
 * each board has an integer value based upon its configuration,
 * this function sets that value
 */
int setPatternValue(Board *board){
	int count = 0;
	int result = 0;
	int y;
	int x;
	for(y = 1; y <= SIZE; y++)
		for(x = 1; x <= SIZE; x++){
			result += board->tile[x][y] * pow(10, SIZE * SIZE - count - 1);
			count++;
		}		
	return result;
}

/* 
 * sets the depth and path history
 */
void completeBoard(Board *current, Board *newBoard, int mov){
	int i;
	newBoard->depth = current->depth + 1;
	newBoard->path = (int *)calloc(newBoard->depth, sizeof(int));
	setNumbers(newBoard);
	for(i = 0; i < current->depth; i++){
		newBoard->path[i] = current->path[i];
	}
	newBoard->path[newBoard->depth - 1] = mov;
}

void printBoard(Board *board){
	int x;
	int y;
	//printf("----\n");
	for(y = 1; y <= SIZE; y++){
		for(x = 1; x <= SIZE; x++){
			if(board->tile[x][y] > 0) printf("%d", board->tile[x][y]);
			else printf(".");
		}
		printf("\n");
	}
}

void printPath(Board *board){
	int i;
	for(i = 0; i < board->depth; i++){
		if(i > 0) printf(", ");
		printf("%d", board->path[i]);
	}
	printf("\n");
}

