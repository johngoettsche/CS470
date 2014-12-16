#include "DAO.h"

List *DAO::readAllLinesFloatData(char *fname, int items){
	string line;
	List *data = (List *)calloc(1, sizeof(List));
	data->size = 0;
	ifstream infile(fname);
	while (getline(infile, line)){
		ListElem *listElem = (ListElem *)calloc(1, sizeof(ListElem));
		Point *point = (Point *)calloc(1, sizeof(Point));
		point->elems = items;
		point->value = (float *)calloc(items, sizeof(float));
		istringstream iss(line);
		for(int i = 0; i < items; i++){
			if (!(iss >> point->value[i])) { break; } // error
		}
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
	infile.close();
	return data;
}

List *DAO::readFirstLineParam(char *fname){
	int lines, columns;
	string line;
	List *data = (List *)calloc(1, sizeof(List));
	data->size = 0;
	ifstream infile(fname);
	getline(infile, line);
	istringstream iss(line);
	iss >> lines >> columns;
	for(int l = 0; l < lines; l++){
		getline(infile, line);
		ListElem *listElem = (ListElem *)calloc(1, sizeof(ListElem));
		Point *point = (Point *)calloc(1, sizeof(Point));
		point->elems = columns;
		point->value = (float *)calloc(columns, sizeof(float));
		istringstream iss(line);
		for(int i = 0; i < columns; i++){
			if (!(iss >> point->value[i])) { break; } // error
		}
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
	infile.close();
	return data;
}
