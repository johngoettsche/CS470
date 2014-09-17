/*
 * John Goettsche
 * CS 470
 * Assignment 1
 */

#include "board.h"

typedef struct Node Node;
struct Node{
	Board *b;
	Node *next;
};

typedef struct HashTable HashTable;
struct HashTable{
	int size;
	Node **table;
};
