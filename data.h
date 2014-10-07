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

typedef struct Queue Queue;
struct Queue{
	Node *head;
	Node *tail;
};

typedef struct HashTable HashTable;
struct HashTable{
	int size;
	Node **table;
};

typedef struct Move Move;
struct Move{
	int x;
	int y;
};
