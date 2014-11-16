#include "Matrix.h"

using namespace std;

Matrix::Matrix(float input[], int h){
	width = 1;
	height = h;
	for(h = 0; h < height; h++){
		m[0][h] = input[h];
	}
}

Matrix::Matrix(int w, int h){
	width = w;
	height = h;
	cout << w << ", " << h << endl;
	srand(time(NULL));
	for(h = 0; h < height; h++){
		for(w = 0; w < width; w++){
			m[w][h] = rand()/float(RAND_MAX);
		}
	}
}

Matrix Matrix::dotProduct(Matrix input){
	if(height == input.height){
		int newWidth = width;
		int newHeight = input.width;
		Matrix output(newWidth, newHeight);
		float sum;
		for(int h = 0; h < newHeight; h++){
			for(int w = 0; w < newWidth; w++){
				sum = 0;
				for(int y = 0; y < height; y++){
					sum += m[w][y] * input.m[h][y];
				}
				output.m[w][h] = sum;
			}
		}
		return output;
	} else {
		cout << "Matrixies are not of the same height" << endl;
		exit(1);
	}
}

Matrix Matrix::s(Matrix input){
	if(height == input.height){
		int newWidth = width;
		int newHeight = input.width;
		Matrix output(newWidth, newHeight);
		float sum;
		for(int h = 0; h < newHeight; h++){
			for(int w = 0; w < newWidth; w++){
				sum = 0;
				for(int y = 0; y < height; y++){
					sum += 4 * exp(-4 * (m[w][y] * input.m[h][y])) / pow((1 + exp(-4 * (m[w][y] * input.m[h][y]))), 2);
				}
				if(abs(sum) < 0.00001) sum = 0.0;
				//if(sum > 100) sum = 100;
				//if(sum < -100) sum = -100;
				output.m[w][h] = sum;
			}
		}
		return output;
	} else {
		cout << "Matrixies are not of the same height" << endl;
		exit(1);
	}
}

Matrix Matrix::flip(){
	Matrix output(height, width);
	for(int h = 0; h < height; h++){
		for(int w = 0; w < width; w++){
			output.m[h][w] = m[w][h];
		}
	}
	return output;
}

void Matrix::print(){
	for(int h = 0; h < height; h++){
		for(int w = 0; w < width; w++){
			cout << m[w][h] << " ";
		}
		cout << endl;
	}
	cout << endl;
}