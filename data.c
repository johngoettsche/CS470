/*
 * John Goettsche
 * CS 470
 * Assignment 2
 */
 
#include <stdio.h>
#include <stdlib.h>

#include "data.h"

/*
 * adds a board to the queue.
 */
 
Queue *createQueue(){
	Queue *newQueue;
	Node *newNode;
	if((newQueue = (Queue *)calloc(1, sizeof(Queue))) == NULL) return NULL;
	newQueue->head = NULL;
	newQueue->tail = NULL;
	return newQueue;
}
 
int put(Queue *queue, Board *newBoard){
	Node *newNode;
	if((newNode = (Node *)calloc(1, sizeof(Node))) == NULL) return 1;
	newNode->b = newBoard;
	if(queue->tail == NULL){
		queue->head = newNode;
		queue->tail = newNode;
		queue->head->next = NULL;
	} else {
		newNode->next = NULL;
		queue->tail->next = newNode;
		queue->tail = queue->tail->next;
	}
	return 0;
}

int insert(Queue *queue, Board *newBoard){
	Node *current = queue->head;
	Node *newNode;
	if((newNode = (Node *)calloc(1, sizeof(Node))) == NULL) return 1;
	newNode->b = newBoard;
	newNode->next = NULL;
	if(current == NULL){
		queue->head = newNode;
		queue->tail = newNode;
		queue->head->next = NULL;
	} else {
		while(current->b->f <= newBoard->f && current->next != NULL) current = current->next;
		newNode->next = current->next;
		current->next = newNode;
		if(newNode->next == NULL) {
			queue->tail = newNode;
		}
	}
	return 0;
}

void pop(Queue *queue){
	queue->head = queue->head->next;
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

int lookupBoard(HashTable *hashTable, Board *board){
	Node *list;
	int hashValue = hash(hashTable, board);
	for(list = hashTable->table[hashValue]; list != NULL; list = list->next){
		if(board->value == list->b->value) {
				return list->b->f;
		}
	}
	return -1;
}

int addBoard(HashTable *hashTable, Board *board){
   Node *newList;
	int exist;
	int hashValue = hash(hashTable, board);
	if((newList = (Node *)calloc(1, sizeof(Node))) == NULL) return 1;
	if((exist = lookupBoard(hashTable, board)) == -1) {
		newList->b = board;
		newList->next = hashTable->table[hashValue];
		hashTable->table[hashValue] = newList;
		return 0;
	}
	return 1;
}