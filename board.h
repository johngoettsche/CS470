/*
 * John Goettsche
 * CS 470
 * Assignment 1
 */

#define SIZE 3

typedef struct Board Board;
struct Board{
		int openX; //open space x-coordinate
		int openY; //open space y-coordinate
		int value; //board unique value
		int depth; //board depth
		int *path; //path required to reach this board
		int numbers[(SIZE * SIZE)]; //data transfer array
		int tile[SIZE + 2][SIZE + 2]; //board configuration
};