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
	for(h = 0; h < height; h++){
		for(w = 0; w < width; w++){
			m[w][h] = (2 * rand()/float(RAND_MAX)) - 1;
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

Matrix *Matrix::mult(Matrix *input){
	Matrix *output = new Matrix(width, height);
	for(int h = 0; h < height; h++){
		for(int w = 0; w < width; w++){
			output->m[w][h] = m[w][h] * input->m[w][h];
		}
	}
	return output;
}

Matrix *Matrix::dotProduct(Matrix *input){
	if(height == input->height){
	//cout << "------------------" << endl;
	//print();
	//cout << "==================" << endl;
	//input->print();
	//cout << "------------------" << endl;
		int newWidth = input->width;
		int newHeight = width;
		Matrix *output = new Matrix(newWidth, newHeight);
		float sum;
		for(int h = 0; h < newHeight; h++){
			for(int w = 0; w < newWidth; w++){
				sum = 0;
				for(int y = 0; y < height; y++){
					//cout << m[h][y] << " * " << input->m[w][y] << " = " << m[h][y] * input->m[w][y] << " == ";
					sum += m[h][y] * input->m[w][y];
					//cout << sum << endl;
				}
				//if(abs(sum) < 0.0000000001) sum = 0.0;
				output->m[w][h] = sum;
				//if(output->m[w][h] > FLT_MAX / 2.0) output->m[w][h] = FLT_MAX / 2.0;
				//if(output->m[w][h] < FLT_MIN / 2.0) output->m[w][h] = FLT_MIN / 2.0;
			}
		}
		output = output->flip();
		return output;
	} else {
		cout << "Matrixies are not of the same height" << endl;
		exit(1);
	}
}

Matrix *Matrix::s(){
	Matrix *output = new Matrix(width, height);
	for(int h = 0; h < height; h++){
		for(int w = 0; w < width; w++){
			if (abs(1 + exp(-4 * m[w][h])) > 0.0000000001)
				output->m[w][h] = 1 / (1 + exp(-4 * m[w][h]));
			else output->m[w][h] = 1.0;
			if(abs(output->m[w][h]) < 0.0000000001) output->m[w][h] = 0.0;
			if(output->m[w][h] > FLT_MAX / 2.0) output->m[w][h] = FLT_MAX / 2.0;
			if(output->m[w][h] < FLT_MIN / 2.0) output->m[w][h] = FLT_MIN / 2.0;
		}
	}
	return output;
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