/*
 * John Goettsche
 * CS 470
 * Assignment 2
 */

#define SIZE 3

typedef struct Board Board;
struct Board{
		int openX; //open space x-coordinate
		int openY; //open space y-coordinate
		int value; //board unique value
		int depth; //board depth
		int *path; //path required to reach this board
		int f, h; //f = g(depth) + h
		int numbers[(SIZE * SIZE)]; //data transfer array
		int tile[SIZE + 2][SIZE + 2]; //board configuration
};

extern Board *goal;

void insertTiles(Board *, int *);
void setNumbers(Board *);
int setPatternValue(Board *);
void completeBoard(Board *, Board *, int, int);
int getH(Board *);
int getHout(Board *);
int getHmanhattan(Board *);
int getHgreat2(Board *);
int getHgreat3(Board *);
void printBoard(Board *);
Board *copyBoard(Board *);
void printPath(Board *);
