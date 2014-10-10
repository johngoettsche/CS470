/*
 * John Goettsche
 * CS 470
 * Assignment 2
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

Queue *createQueue();
int put(Queue *, Board *);
int insert(Queue *, Board *);
int replace(Queue *, Board *);
void freeQueue(Queue *);
void pop(Queue *);
int getQueueLength(Queue *);
HashTable *createHashTable(int);
int hash(HashTable *, Board *);
int lookupBoard(HashTable *, Board *);
int addBoard(HashTable *, Board *);
