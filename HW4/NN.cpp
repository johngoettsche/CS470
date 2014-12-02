#include "NN.h"

float checkLimit(float val){
	if(abs(val) < 0.001) val = 0.000;
	if(val > FLT_MAX / 2.0) val = FLT_MAX / 2.0;
	if(val < FLT_MIN / 2.0) val = FLT_MIN / 2.0;
	return val;
}

int main(){
	srand((unsigned)time(NULL));
	const float alpha = 0.01;
	const int I = 5;
	const int J = 4;
	const int K = 3;
	float data[150][5];
	float rawdata[150][5];
	int rnd;
	int goal;
	string line;
	float input[I];
	float t[K] = {0.0, 0.0, 0.0};
	float data2[J];
	float maxval[4];
	float minval[4];
		
//read in data set	
	ifstream in("irisClean.dat");
	for(int i = 0; i < 150; i++) in >> rawdata[i][0] >> rawdata[i][1] >> rawdata[i][2] >> rawdata[i][3] >> rawdata[i][4];
	in.close();
	
//normalizeData
	for(int c = 0; c < 4; c++){
		maxval[c] = -10000.0;
		minval[c] = 10000.0;
		for(int r = 0; r < 100; r++){
			if(rawdata[r][c] > maxval[c]) maxval[c] = rawdata[r][c];
			if(rawdata[r][c] < minval[c]) minval[c] = rawdata[r][c];
		}
	}
	for(int c = 0; c < 4; c++){
		for(int r = 0; r < 100; r++){
			data[r][c] = (rawdata[r][c] - minval[c]) / (maxval[c] - minval[c]);
			//cout << data[r][c] << endl;
		}
	}
	for(int r = 0; r < 100; r++) data[r][4] = rawdata[r][4];
		
//set up weights
	Matrix *v = new Matrix(J, I);
	Matrix *w = new Matrix(K, J);
	for(int ev = 0; ev < 10000; ev++){
		rnd = rand() % 100;
		input[0] = -1;
		for(int i = 0; i < 4; i++){
			input[i + 1] = data[rnd][i];
		}
		goal = (int)data[rnd][4];
		for(int k = 0; k < K; k++) t[k] = 0.0;
		t[goal] = 1.0;
		Matrix *x = new Matrix(input, I);
		Matrix *g = new Matrix(x->dotProduct(v));
		Matrix *gp = g->flip();
		gp = gp->s();
		data2[0] = -1;
		for(int i = 0; i < 3; i++){
			data2[i + 1] = gp->m[0][i];
		}
		Matrix *a = new Matrix(data2, J);
		Matrix *h = new Matrix(a->dotProduct(w));
		Matrix *y = h->flip();
		y = y->s();
	
	//back
		//calculate deltaY
		Matrix *deltaY = new Matrix(a);
		deltaY->m[0][0] = 0.0;
		for(int k = 0; k < K; k++) {
			deltaY->m[0][k + 1] = (t[k] - y->m[0][k]); // * y->m[0][k] * (1.0 - y->m[0][k]);
		}
		//cout << "y" << endl;
		//y->print();
		//cout << "deltaY" << endl;
		//deltaY->print();
		
		//calculate deltaA
		Matrix *deltaA = new Matrix(x);
		deltaA->m[0][0] = 0.0;
		float temp = deltaY->dotProduct(w)->m[0][0];
		for(int j = 0; j < J; j++) {
			deltaA->m[0][j + 1] = (a->m[0][j] * (1 - a->m[0][j])) * temp; 
		}
		//adjust w
		//cout << "dotProduct" << endl;
		//a->dotProduct(deltaY)->print();
		temp = a->dotProduct(deltaY)->m[0][0];
		//cout << temp << endl;
		for(int k = 0; k < K; k++){
			for(int j = 0; j < J; j++){
				w->m[k][j] += alpha * temp;
			}
		}
		//adjust v
		temp = x->dotProduct(deltaA)->m[0][0];
		for(int j = 0; j < J; j++){
			for(int i = 0; i < I; i++){
				v->m[j][i] += alpha * temp;
			}
		}
		delete x;
		delete g;
		delete gp;
		delete a;
		delete h;
		delete y;
		delete deltaA;
		delete deltaY;
	}
	//testing
	int max;
	int success = 0;
	for(int c = 0; c < 4; c++){
		for(int r = 100; r < 150; r++){
			data[r][c] = (rawdata[r][c] - minval[c]) / (maxval[c] - minval[c]);
			//cout << data[r][c] << endl;
		}
	}
	for(int r = 100; r < 150; r++) data[r][4] = rawdata[r][4];
	int count = 0;
	for(int ds = 0; ds < 100; ds++){
		count++;
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
		//cout << y->m[0][0] << " : "  << y->m[0][1] << " : " << y->m[0][2] << " || ";
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
		//cout << max << " : " << goal << endl;
		cout << count << " " << max << endl;
		if(max == goal) success++;
	}
	//cout << "success " << success << " out of " << count << " or " << 100 * (float)success / (float)count << "%" << endl;
	//w->print();
	//v->print();
}
