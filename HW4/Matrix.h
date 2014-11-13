#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cmath>

class Matrix {
	public :
		int width;
		int height;
		float m[10][10];
		
		Matrix (float input[], int h);
		Matrix (int w, int h);
		Matrix dotProduct(Matrix input);
		Matrix s(Matrix input);
		Matrix flip();
		void print();
};