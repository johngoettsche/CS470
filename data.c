/*
 * John Goettsche
 * CS 470
 * Assignment 1
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "data.h"

/*
 * adds a board to the queue.
 */
 
Queue *createQueue(){
	Queue *newQueue;
	if((newQueue = (Queue *)calloc(1, sizeof(Queue))) == NULL) return NULL;
	newQueue->head = NULL;
	newQueue->tail = NULL;
	return newQueue;
}
 
int put(Queue queue, Board *newBoard){
	Node *newNode;
	if((newNode = (Node *)calloc(1, sizeof(Node))) == NULL) return 1;
	newNode->b = newBoard;
	if(queue.tail == NULL){
		printf("adding first node to queue\n");
		queue.head = newNode;
		queue.tail = newNode;
		newNode->next = NULL;
	} else {
		printf("adding a node to queue\n");
		newNode->next = NULL;
		queue.tail->next = newNode;
	}
	return 0;
}

void pop(Queue queue){
	queue.head = queue.head->next;
}

int getQueueLength(Queue *queue){
	int length = 0;
	Node *current = queue->head;
	if(current != NULL) {
		while(current->next != NULL){
			length++;
			current = current->next;
		}
	}
	return length;
}

HashTable *createHashTable(int size){
	int i;
	HashTable *newHashTable;
	if(size < 1) return NULL;
	if((newHashTable = (HashTable *)calloc(1, sizeof(HashTable))) == NULL) return NULL;
	if((newHashTable->table = calloc(size, sizeof(HashTable))) == NULL) return NULL;
	for(i = 0; i < size; i++) newHashTable->table[i] = NULL;
	newHashTable->size = size;
	return newHashTable;
}

int hash(HashTable *hashTable, Board *board){
	return board->value % hashTable->size;
}

Board *lookupBoard(HashTable *hashTable, Board *board){
	Node *list;
	int hashValue = hash(hashTable, board);
	for(list = hashTable->table[hashValue]; list != NULL; list = list->next){
		if(board->value == list->b->value) return board;
	}
	return NULL;
}

int addBoard(HashTable *hashTable, Board *board){
   Node *newList;
	Node *current;
	int hashValue = hash(hashTable, board);
	if((newList = (Node *)calloc(1, sizeof(Node))) == NULL) return 1;
	current->b = lookupBoard(hashTable, board);
	if(current->b != NULL) return 2;
	newList->b = board;
	newList->next = hashTable->table[hashValue];
	hashTable->table[hashValue] = newList;
}