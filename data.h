#include "board.h"

typedef struct Node Node;
struct Node{
	Board *b;
	Node *next;
};
