#include <iostream>
#include <ctime>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>

//#include "structs.h"
#include "DAO.h"

using namespace std;

void displayData(List *data);
float getMin(List *data, int column);
float getMax(List *data, int column);
void addToList(List *list, Point *point);
List *makePoints(List *data, int points);
float distance(Point *p1, Point *p2);
float getTotalDistance(List *data);
float getSetDistance(ListElem *parent);
Point *findNearestPoint(List *meanPoint, Point *point);
void meanPoints(Point *meanPoint);