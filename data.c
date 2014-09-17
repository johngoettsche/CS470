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
Node *put(Node *tail, Board *newBoard){
	if(tail->b == NULL){
		tail->b = newBoard;
		tail->next = NULL;
	} else {
		Node *newNode = (Node *)calloc(1, sizeof(Node));
		newNode->b = newBoard;
		newNode->next = NULL;
		tail->next = newNode;
		return newNode;
	}
	return tail;
}

int getQueueLength(Node *head){
	int length = 0;
	while(head->next != NULL){
		length++;
		head = head->next;
	}
	return length;
}

HashTable *createHashTable(int size){
	int i;
	HashTable *newHashTable;
	if(size < 1) return NULL;
	if((newHashTable = calloc(1, sizeof(HashTable))) == NULL) return NULL;
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
	current = lookupBoard(hashTable, board);
	if(current != NULL) return 2;
	newList->b = board;
	newList->next = hashTable->table[hashValue];
	hashTable->table[hashValue] = newList;
}