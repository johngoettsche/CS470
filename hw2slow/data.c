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
	if((newQueue = (Queue *)calloc(1, sizeof(Queue))) == NULL) return NULL;
	newQueue->head = NULL;
	return newQueue;
}
 
int put(Queue *queue, Board *newBoard){
	Node *newNode;
	if((newNode = (Node *)calloc(1, sizeof(Node))) == NULL) return 1;
	newNode->b = newBoard;
	if(queue->head == NULL){
		queue->head = newNode;
		queue->head->next = NULL;
	} else newNode->next = NULL;
	return 0;
}

int insert(Queue *queue, Board *newBoard){
	Node *current = queue->head;
	Node *newNode;
	if((newNode = (Node *)calloc(1, sizeof(Node))) == NULL) {
		printf("INSERT ERROR\n");
		return 1;
	}
	newNode->b = newBoard;
	newNode->next = NULL;
	if(current == NULL){
		queue->head = newNode;
		queue->head->next = NULL;
	} else {
		while(current->b->f <= newBoard->f && current->next != NULL) current = current->next;
		newNode->next = current->next;
		current->next = newNode;
	}
	return 0;
}

int replace(Queue *queue, Board *newBoard){
	Node *current = queue->head;
	Node *newNode;
	if((newNode = (Node *)calloc(1, sizeof(Node))) == NULL){
		printf("REPLACE ERROR\n");
		return 1;
	}
	newNode->b = newBoard;
	newNode->next = NULL;
	while(current->b->f <= newBoard->f && current->next != NULL) {
		if(current->b->value == newNode->b->value) {
			return 0;
		}
		current = current->next;
	}
	newNode->next = current->next;
	current->next = newNode;
	current = newNode->next;
	while(current != NULL){
		if(current->b->value == newNode->b->value) {
			if(current->next != NULL)current->next = current->next->next;
		}
		current = current->next;
	}
	return 0;
}

void freeQueue(Queue *queue){
	Node *current = queue->head;
	Node *prev;
	while(current){
		prev = current;
		if(current->next) current = current->next;
		else current = NULL;
		free(prev->b);
		free(prev);
	}
}

void pop(Queue *queue){
	Node *oldNode = queue->head;
	queue->head = queue->head->next;
	free(oldNode);
}

int getQueueLength(Queue *queue){
	int length = 0;
	Node *current = queue->head;
	if(current != NULL) {
		length++;
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
	return (HashTable *)newHashTable;
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

int addBoard(HashTable *h_table, Board *board){
   Node *newList;
	int exist;
	int hashValue = hash(h_table, board);
	if((newList = (Node *)calloc(1, sizeof(Node))) == NULL) {
		printf("failed to create node for table\n");
		return 1;
	}
	if((exist = lookupBoard(h_table, board)) == -1) {
		newList->b = board;
		newList->next = h_table->table[hashValue];
		h_table->table[hashValue] = newList;
		return 0;
	}
	return 0;
}