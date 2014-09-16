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