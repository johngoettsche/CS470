#include <stdio.h>
#include <stdlib.h>

#include "data.h"

void put(Node *head, Board *newBoard){
	if(head->b == NULL){
		head->b = newBoard;
		head->next = NULL;
	} else {
		Node *current = (Node *)calloc(1, sizeof(Node));
		current = head;
		Node *newNode = (Node *)calloc(1, sizeof(Node));
		newNode->b = newBoard;
		newNode->next = NULL;
		while(current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
	}
}

int getQueueLength(Node *head){
	int length = 0;
	while(head->next != NULL){
		length++;
		head = head->next;
	}
	return length;
}