#include "MatrixTest.h"

int main(){
	Matrix *a = new Matrix(2, 2);
	a->m[0][0] = 1;
	a->m[0][1] = 2;
	a->m[1][0] = 3;
	a->m[1][1] = 4;
	a->print();
	Matrix *b = new Matrix(1, 2);
	b->m[0][0] = 5;
	b->m[0][1] = 7;
	b->print();
	Matrix *c = a->dotProduct(b);
	c->print();
}