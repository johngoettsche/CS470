/* pow
 * John Goettsche
 * CS 470
 * Assignment 2
 * board setup
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "board.h"

extern Board *goal;

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
	newBoard->f = newBoard->depth + getH(newBoard);
}

/* h = 0 
int getH(Board *board){
	return 0;
}*/

/* h = out of place 
int getH(Board *board){
	int h = 0;
	int x, y;
	for(x = 1; x <= SIZE; x++)
		for(y = 1; y <= SIZE; y++)
			if(board->tile[x][y] != goal->tile[x][y]) h++;
	return h;
}*/

/* h = Manhattan distance 
int getH(Board *board){
	int h = 0;
	int x, bx, gx, y, by, gy, n;
	for(n = 1; n < SIZE * SIZE; n++) {
		for(x = 1; x <= SIZE; x++) {
			for(y = 1; y <= SIZE; y++) {
				if (n == board->tile[x][y]) {
					bx = x;
					by = y;
				}
			}
		}
		for(x = 1; x <= SIZE; x++) {
			for(y = 1; y <= SIZE; y++) {
				if (n == goal->tile[x][y]) {
					gx = x;
					gy = y;
				}
			}
		}
		h += abs(bx - gx) + abs(by - gy);
	}
	return h;
}*/

/* h = greatest * 2 
int getH(Board *board){
	int h = 0;
	int x, bx, gx, y, by, gy, n;
	for(n = 1; n < SIZE * SIZE; n++) {
		for(x = 1; x <= SIZE; x++) {
			for(y = 1; y <= SIZE; y++) {
				if (n == board->tile[x][y]) {
					bx = x;
					by = y;
				}
			}
		}
		for(x = 1; x <= SIZE; x++) {
			for(y = 1; y <= SIZE; y++) {
				if (n == goal->tile[x][y]) {
					gx = x;
					gy = y;
				}
			}
		}
		if(abs(bx - gx) > abs(by - gy)) h += abs(bx - gx) * 2;
		else h += abs(by - gy) * 2;
	}
	return h;
}*/

/* h = greatest * 3 */
int getH(Board *board){
	int h = 0;
	int x, bx, gx, y, by, gy, n;
	for(n = 1; n < SIZE * SIZE; n++) {
		for(x = 1; x <= SIZE; x++) {
			for(y = 1; y <= SIZE; y++) {
				if (n == board->tile[x][y]) {
					bx = x;
					by = y;
				}
			}
		}
		for(x = 1; x <= SIZE; x++) {
			for(y = 1; y <= SIZE; y++) {
				if (n == goal->tile[x][y]) {
					gx = x;
					gy = y;
				}
			}
		}
		if(abs(bx - gx) > abs(by - gy)) h += abs(bx - gx) * 3;
		else h += abs(by - gy) * 3;
	}
	return h;
}

void printBoard(Board *board){
	int x;
	int y;
	for(y = 1; y <= SIZE; y++){
		for(x = 1; x <= SIZE; x++){
			if(board->tile[x][y] > 0) printf("%d", board->tile[x][y]);
			else printf(".");
			if(x < SIZE) printf(" ");
		}
		printf("\n");
	}
	//printf("%d\n", board->value);
}

void printPath(Board *board){
	int i;
	for(i = 0; i < board->depth; i++){
		if(i > 0) printf(" ");
		printf("%d", board->path[i]);
	}
	printf("\n");
}

