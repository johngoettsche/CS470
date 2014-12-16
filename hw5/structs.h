
typedef struct Point{
	int elems;
	float *value;
	struct List *sublist;
}Point;

typedef struct ListElem{
	Point *item;
	struct ListElem *next;
}ListElem;

typedef struct List{
	int size;
	ListElem *head;
	ListElem *tail;
}List;