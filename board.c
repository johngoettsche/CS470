#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "board.h"

insertTiles(Board *board, int *nums){
	int i = 0;
	int y;
	int x;
	for(y = 1; y <= SIZE; y++){
		for(x = 1; x <= SIZE; x++){
			board->numbers[i] = nums[i];
			board->tile[x][y] = nums[i];
			if(board->tile[x][y] == 0){
				board->openX = x;
				board->openY = y;
			}
			i++;
		}
	}
	board->value = setPatternValue(board);
}
	
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

printBoard(Board *board){
	int x;
	int y;
	printf("-----------------------\n");
	for(y = 1; y <= SIZE; y++){
		for(x = 1; x <= SIZE; x++){
			if(board->tile[x][y] > 0) printf("%d\t", board->tile[x][y]);
			else printf(" \t");
		}
		printf("\n");
	}
}

