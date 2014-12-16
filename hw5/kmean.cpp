#include "kmean.h"

#define SHOW_DATA 0
#define SHOW_POINTS 0
#define SHOW_COUNTS 0

#define ITERATIONS 10

void displayData(List *data){
	int count = 0;
	ListElem *current = data->head;
	printf("\nK: %d\n", data->size); 
	printf("Means (size: %d X %d)\n", data->size, data->head->item->elems);
	while(current != NULL){
		if(SHOW_COUNTS && current->item->sublist != NULL)
			printf("(%d)", current->item->sublist->size);
		for(int i = 0; i < current->item->elems; i++) {
			printf("   %f", current->item->value[i]);
		}
		printf("\n");
		current = current->next;
	}
	//printf("\n");
	current = data->head;
	while(current != NULL){
		printf("%d\t", count);
		printf("%f\n", getSetDistance(current));
		count++;
		current = current->next;
	}
}
/*
void displayData(List *data){
	int count = 0;
	ListElem *current = data->head;
	cout << "\nK: " << data->size << endl;
	cout << "Means (size: " << data->size << " X " << data->head->item->elems << ")" << endl;
	while(current != NULL){
		//cout << count << ":";
		if(SHOW_COUNTS && current->item->sublist != NULL)cout << "(" << current->item->sublist->size << ")";
		for(int i = 0; i < current->item->elems; i++) {
			cout << "   " << current->item->value[i];
		}
		cout << endl;
		//count++;
		current = current->next;
	}
	cout << endl;
	current = data->head;
	while(current != NULL){
		cout << count << "\t";
		cout << getSetDistance(current) << endl;
		count++;
		current = current->next;
	}
}*/

int getCount(List* list){
	int count = 0;
	ListElem *current = list->head;
	while(current != NULL){
		count++;
		current = current->next; 
	}
	return count;
}

float getMin(List *data, int column){
	ListElem *current = data->head;
	float min = current->item->value[column];
	while(current != NULL){
		if(current->item->value[column] < min) min = current->item->value[column];
		current = current->next;
	}
	return min;
}

float getMax(List *data, int column){
	ListElem *current = data->head;
	float max = current->item->value[column];
	while(current != NULL){
		if(current->item->value[column] > max) max = current->item->value[column];
		current = current->next;
	}
	return max;
}

void addToList(List *list, Point *point){
	ListElem *listElem = (ListElem *)calloc(1, sizeof(ListElem));
	listElem->item = point;
	if(list->head == NULL){
		list->head = listElem;
		list->tail = listElem;
	} else {
		list->tail->next = listElem;
		list->tail = listElem;
	}
	list->size++;
}

List *makePoints(List *data, int points){
	int items = data->head->item->elems;
	float min[items];
	float max[items];
	for(int i = 0; i < items; i++){
		min[i] = getMin(data, i);
		max[i] = getMax(data, i);
	}
	List *pointList = (List*)calloc(1, sizeof(List));
	for(int p = 0; p < points; p++){
		Point *point = (Point *)calloc(items, sizeof(Point));
		point->elems = data->head->item->elems;
		point->value = (float *)calloc(data->head->item->elems, sizeof(float));
		for(int i = 0; i < point->elems; i++){
			point->value[i] = ((max[i] - min[i]) * rand() / float(RAND_MAX)) + min[i];
		}
		point->sublist = (List *)calloc(1, sizeof(List));
		addToList(pointList, point);
	}
	return pointList;
}

float distance(Point *p1, Point *p2){
	float value = 0;
	for(int i = 0; i < p1->elems; i++){
		value += pow((p1->value[i] - p2->value[i]), 2);
	}
	value = sqrt(value);
	return value;
}

float getTotalDistance(List *data){
	float sum = 0.0;
	ListElem *currentPoint = data->head;
	ListElem *currentSublist;
	while(currentPoint != NULL){
		currentSublist = currentPoint->item->sublist->head;
		while(currentSublist != NULL){
			sum += distance(currentPoint->item, currentSublist->item);
			currentSublist = currentSublist->next;
		}
		currentPoint = currentPoint->next;
	}
	return sum;
}

float getSetDistance(ListElem *parent){
	float sum = 0.0;
	ListElem *currentPoint = parent->item->sublist->head;
	while(currentPoint != NULL){
		sum += distance(currentPoint->item, parent->item);
		currentPoint = currentPoint->next;
	}
	return sum;
}

Point *findNearestPoint(List *meanPoint, Point *point){
	ListElem *current = meanPoint->head;
	ListElem *closest = current;
	float shortest = distance(meanPoint->head->item, point);
	while(current != NULL){
		if(distance(current->item, point) < shortest){
			shortest = distance(current->item, point);
			closest = current;
		}
		current = current->next;
	}
	return closest->item;
}

void meanPoints(Point *meanPoint){
	ListElem *current;
	float value;
	int count;
	for(int c = 0; c < meanPoint->elems; c++){
		current = meanPoint->sublist->head;
		value = 0.0;
		count = 0;
		while(current != NULL){
			value += current->item->value[c];
			count++;
			current = current->next;
		}
		value = value / count;
		meanPoint->value[c] = value;
	}
}

int main(int argc, char *argv[]){
	srand((unsigned)time(NULL));
	//char *fname = (char *)"setone.dat";
	/*char *fname = (char *)calloc(128, sizeof(char));
	if(argc > 1) fname =  argv[1];
	else cin >> fname;
	cout << fname << endl;*/
	List *points;
	List *data = (List *)calloc(1, sizeof(List));
	/*DAO *dao = new DAO();
	data = dao->readFirstLineParam(fname);
	//data = dao->readAllLinesFloatData(fname, items);*/
	int lines, columns;
	columns = 3;
	cin >> lines;
	
	for(int l = 0; l < lines; l++){
		//cin >> getline(infile, line);
		ListElem *listElem = (ListElem *)calloc(1, sizeof(ListElem));
		Point *point = (Point *)calloc(1, sizeof(Point));
		point->elems = columns;
		point->value = (float *)calloc(columns, sizeof(float));
		
		cin >> point->value[0] >> point->value[1] >> point->value[2];
		//cout >> point->value[0] >> " " >> point->value[1] >> " " >> point->value[2] >> endl;
		//istringstream iss(line);
		/*for(int i = 0; i < columns; i++){
			cin >> point->value[i];
			cout << point->value[i] << "   ";
		}*/
		//cout << endl;
		listElem->item = point;
		if(data->head == NULL){
			data->head = listElem;
			data->tail = listElem;
		} else {
			data->tail->next = listElem;
			data->tail = listElem;
		}
		data->size++;
	}
	
	
	
	
	
		if(SHOW_DATA)displayData(data);
	
	ListElem *current;
	Point *nearest;
	
	for(int categories = 2; categories <= 5; categories++){
		points = makePoints(data, categories);
			if(SHOW_POINTS)displayData(points);
		for(int i = 0; i < 10; i++){
			current = data->head;
			while(current != NULL){
				nearest = findNearestPoint(points, current->item);
				addToList(nearest->sublist, current->item);
				current = current->next;
			}
			
			current = points->head;
			while(current != NULL){
				current->item->sublist->size = getCount(current->item->sublist);
				if(current->item->sublist->size > 0) meanPoints(current->item);
				if(i < 9){
					current->item->sublist->head = NULL;
					current->item->sublist->tail = NULL;
				}
				current = current->next;
			}
			if(SHOW_POINTS)displayData(points);
		}
		if(SHOW_POINTS){
			current = points->head;
			while(current != NULL){
				displayData(current->item->sublist);
				current = current->next;
			}
		}
	
		displayData(points);
		//cout << "Total distance: " << getTotalDistance(points) << endl << endl;
	
	}
	return 0;
}