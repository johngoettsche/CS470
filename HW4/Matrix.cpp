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
	//cout << w << ", " << h << endl;
	srand(time(NULL));
	for(h = 0; h < height; h++){
		for(w = 0; w < width; w++){
			m[w][h] = rand()/float(RAND_MAX);
		}
	}
}

Matrix::Matrix(Matrix *input){
	width = input->width;
	height = input->height;
	for(int h = 0; h < height; h++){
		for(int w = 0; w < width; w++){
			m[w][h] = input->m[w][h];
		}
	}
}

Matrix::~Matrix(){
	
}

Matrix *Matrix::dotProduct(Matrix *input){
	if(height == input->height){
		int newWidth = width;
		int newHeight = input->width;
		Matrix *output = new Matrix(newWidth, newHeight);
		float sum;
		for(int h = 0; h < newHeight; h++){
			for(int w = 0; w < newWidth; w++){
				sum = 0;
				for(int y = 0; y < height; y++){
					sum += m[w][y] * input->m[h][y];
				}
				if(abs(sum) < 0.001) sum = 0.0;
				output->m[w][h] = sum;
				if(output->m[w][h] > 2.0) output->m[w][h] = 2.0;
				if(output->m[w][h] < -2.0) output->m[w][h] = -2.0;
			}
		}
		return output;
	} else {
		cout << "Matrixies are not of the same height" << endl;
		exit(1);
	}
}

Matrix *Matrix::s(Matrix *input){
	if(height == input->height){
		int newWidth = width;
		int newHeight = input->width;
		Matrix *output = new Matrix(newWidth, newHeight);
		float sum;
		for(int h = 0; h < newHeight; h++){
			for(int w = 0; w < newWidth; w++){
				sum = 0;
				for(int y = 0; y < height; y++){
					if ((-4 * pow(2.718, (-4 * (m[w][y] * input->m[h][y])))) != 0)
						sum += 1 / (-4 * pow(2.718, (-4 * (m[w][y] * input->m[h][y]))));
					else sum = 100.0;
				}
				if(abs(sum) < 0.001) sum = 0.0;
				output->m[w][h] = sum;
				//if(output->m[w][h] > 2.0) output->m[w][h] = 2.0;
				//if(output->m[w][h] < -2.0) output->m[w][h] = -2.0;
			}
		}
		return output;
	} else {
		cout << "Matrixies are not of the same height" << endl;
		exit(1);
	}
}

Matrix *Matrix::flip(){
	Matrix *output = new Matrix(height, width);
	for(int h = 0; h < height; h++){
		for(int w = 0; w < width; w++){
			output->m[h][w] = m[w][h];
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