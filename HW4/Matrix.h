#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <cmath>
#include <float.h>

class Matrix {
	public :
		int width;
		int height;
		float m[6][6];
		
		Matrix (float input[], int h);
		Matrix (int w, int h);
		Matrix (Matrix *input);
		~Matrix();
		Matrix *mult(Matrix *input);
		Matrix *mult(float input);
		Matrix *add(Matrix *input);
		Matrix *dotProduct(Matrix *input);
		Matrix *s();
		Matrix *flip();
		void print();
};