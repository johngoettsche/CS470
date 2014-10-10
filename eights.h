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

char *readData();
Board *makeBoardOnMove(Node *, Move, int);
int main();