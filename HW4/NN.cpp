#include "NN.h"

int main(){
	srand((unsigned)time(NULL));
	const float alpha = 0.1;
	const int I = 5;
	const int J = 4;
	const int K = 3;
	float data[150][5];
	int rnd;
	int goal;
	string line;
	float input[I];
	float t[K] = {0.0, 0.0, 0.0};
	float data2[J];
	float deltaY[K];
	float deltaA[J];
	float sum;
		
//read in data set	
	ifstream in("irisClean.dat");
	for(int i = 0; i < 150; i++) in >> data[i][0] >> data[i][1] >> data[i][2] >> data[i][3] >> data[i][4];
	in.close();
	
//set up weights
	Matrix *v = new Matrix(J, I);
	cout << "v:" << endl;
	v->print();
	Matrix *w = new Matrix(K, J);
	cout << "w:" << endl;
	w->print();
	for(int ev = 0; ev < 5000; ev++){
		rnd = rand() % 100;
		input[0] = 1;
		for(int i = 0; i < 4; i++){
			input[i + 1] = data[rnd][i];
		}
		goal = (int)data[rnd][4];
		for(int k; k < K; k++) t[k] = 0.0;
		t[goal] = 1.0;
		Matrix *x = new Matrix(input, I);
		//cout << "x:" << endl;
		//x->print();
		Matrix *g = new Matrix(x->dotProduct(v));
		g = g->flip();
		g = g->s();
		//cout << "v:" << endl;
		//v->print();
		//cout << "g:" << endl;
		//g->print();
		data2[0] = 0.5;
		for(int i = 0; i < 3; i++){
			data2[i + 1] = g->m[0][i];
		}
		Matrix *a = new Matrix(data2, J);
		Matrix *y = new Matrix(a->dotProduct(w));
		y = y->flip();
		y = y->s();
		//cout << "y:" << endl;
		//y->print();
	
	//back
		//calculate deltaY
		//cout << "deltaY:" << endl;
		for(int k = 0; k < K; k++) {
			deltaY[k] = (y->m[0][k] - t[k]) * y->m[0][k] * (1.0 - y->m[0][k]);
			if(abs(deltaY[k]) < 0.0000000001) deltaY[k] = 0.0;
			//cout << y->m[0][k] - t[k] << " : "<< deltaY[k] << endl;
		}
		//calculate deltaA
		for(int j = 0; j < J; j++) {
			sum = 0.0;
			for(int k = 0; k < K; k++) {
				sum += w->m[k][j] * deltaY[k];
			}
			deltaA[j] = a->m[0][j] * (1 - a->m[0][j]) * sum; 
			if(abs(deltaA[j]) < 0.0000000001) deltaA[j] = 0.0;
		}
		//adjust w
		for(int k = 0; k < K; k++){
			for(int j = 0; j < J; j++){
				w->m[k][j] = w->m[k][j] + (alpha * deltaY[k] * deltaA[j]);
				if(w->m[k][j] > FLT_MAX / 2.0) w->m[k][j] = FLT_MAX / 2.0;
				if(w->m[k][j] < FLT_MIN / 2.0) w->m[k][j] = FLT_MIN / 2.0;
			}
		}
		//adjust v
		for(int j = 0; j < J; j++){
			for(int i = 0; i < I; i++){
				v->m[j][i] = v->m[j][i] + (alpha * deltaA[j] * x->m[0][i]);
				if(v->m[j][i] > FLT_MAX / 2.0) v->m[j][i] = FLT_MAX / 2.0;
				if(v->m[j][i] < FLT_MIN / 2.0) v->m[j][i] = FLT_MIN / 2.0;
			}
		}
		delete x;
		delete g;
		delete a;
		delete y;
	}
	//testing
	int max;
	int success = 0;
	for(int ds = 100; ds < 150; ds++){
		for(int i = 0; i < 4; i++){
			input[i + 1] = data[ds][i];
		}
		goal = (int)data[ds][4];
		Matrix *x = new Matrix(input, I);
		Matrix *g = new Matrix(x->dotProduct(v));
		g = g->flip();
		g = g->s();
		data2[0] = 0.5;
		for(int i = 0; i < 3; i++){
			data2[i + 1] = g->m[0][i];
		}
		Matrix *a = new Matrix(data2, J);
		Matrix *y = new Matrix(a->dotProduct(w));
		y = y->flip();
		y = y->s();
		max = 0;
		float maxScore = 0;
		for(int k = 0; k < K; k++){
			if(y->m[0][k] > maxScore){
				maxScore = y->m[0][k];
				max = k;
			}
		}
		delete x;
		delete g;
		delete a;
		delete y;
		cout << max << " : " << goal << endl;
		if(max == goal) success++;
	}
	cout << "v:" << endl;
	v->print();
	cout << "w:" << endl;
	w->print();
	cout << "success " << success / 50.00 << endl;
}
