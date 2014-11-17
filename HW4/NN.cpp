#include "NN.h"

int main(){
	const float alpha = 0.1;
	const int I = 5;
	const int J = 4;
	const int K = 3;
	float data[100][5];
	int select;
	int goal;
	string line;
	float input[I];
	float t[K] = {0.0, 0.0, 0.0};
	float data2[J];
	float deltaY[K];
	float deltaA[J];
	float sum;
	
	srand(time(NULL));
		
//read in data set	
	ifstream in("irisClean.dat");
	for(int i = 0; i < 150; i++) in >> data[i][0] >> data[i][1] >> data[i][2] >> data[i][3] >> data[i][4];
	in.close();
	
//set up weights
	cout << "v:" << endl;
	Matrix *v = new Matrix(J, I);
	v->print();
	
	cout << "w:" << endl;
	Matrix *w = new Matrix(K, J);
	w->print();
	for(int ev = 0; ev < 5; ev++){
		//select a data set from training region
		select = rand() % 100;
		cout << ">" << select << "<" << endl;
		
		input[0] = -1;
		for(int i = 0; i < 4; i++){
			input[i + 1] = data[select][i];
		}
		goal = (int)data[select][4];
		cout << "<" << goal << ">" << endl;
		for(int k; k < K; k++) t[k] = 0.0;
		t[goal] = 1.0;
		
		//for(int i = 0; i < 5; i++) cout << "| " << data[select][i] << endl; 
	//forward
		//cout << "x:" << endl;
		Matrix *x = new Matrix(input, I);
		//x->print();

		//cout << "g:" << endl;
		Matrix *g = new Matrix(x->s(v));
		//g->print();
		
		//cout << "a:" << endl;
		data2[0] = 0.5;
		for(int i = 0; i < 3; i++){
			data2[i + 1] = g->m[0][i];
		}
		Matrix *a = new Matrix(data2, J);
		//a->print();

		cout << "y:" << endl;
		Matrix *y = new Matrix(a->s(w));
		y->print();
	
	//back
		//calculate deltaY
		for(int k = 0; k < K; k++) {
			cout << "(" << y->m[0][k] << " - " << t[k] << ") * (1 - " << y->m[0][k] << ") = " << (y->m[0][k] - t[k]) * y->m[0][k] * (1 - y->m[0][k]) << endl;
			deltaY[k] = (y->m[0][k] - t[k]) * y->m[0][k] * (1 - y->m[0][k]);
			if(abs(deltaY[k]) < 0.001) deltaY[k] = 0.0;
		}
		cout << "> ";
		for(int k = 0; k < K; k++) cout << deltaY[k] << endl;
		//calculate deltaA
		for(int j = 0; j < J; j++) {
			sum = 0.0;
			for(int k = 0; k < K; k++) {
				//cout << w->m[k][j] << " * " << deltaY[k] << " = " << w->m[k][j] * deltaY[k] << endl;
				sum += w->m[k][j] * deltaY[k];
			}
			deltaA[j] = a->m[0][j] * (1 - a->m[0][j]) * sum; 
			if(abs(deltaA[j]) < 0.001) deltaA[j] = 0.0;
		}
		cout << "< "; 
		for(int j = 0; j < J; j++) cout << deltaA[j] << endl;
		//adjust w
		for(int k = 0; k < K; k++){
			for(int j = 0; j < J; j++){
				cout << w->m[k][j] << " + (" << alpha << " * " << deltaY[k] << " * " << deltaA[j]  << ") = " << w->m[k][j] + (alpha * deltaY[k] * deltaA[j]) << endl;
				w->m[k][j] = w->m[k][j] + (alpha * deltaY[k] * deltaA[j]);
				if(w->m[k][j] > 2.0) w->m[k][j] = 2.0;
				if(w->m[k][j] < -2.0) w->m[k][j] = -2.0;
			}
		}
		//adjust v
		for(int j = 0; j < J; j++){
			for(int i = 0; i < I; i++){
				v->m[j][i] = v->m[j][i] + (alpha * deltaA[j] * x->m[0][i]);
				if(v->m[j][i] > 2.0) v->m[j][i] = 2.0;
				if(v->m[j][i] < -2.0) v->m[j][i] = -2.0;
			}
		}
		delete x;
		delete g;
		delete a;
		delete y;
	}
	//cout << "v:" << endl;
	//v->print();
	
	//cout << "w:" << endl;
	//w->print();
}
