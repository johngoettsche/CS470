#include "NN.h"

int getChoice(Matrix results){
	int choice = -1;
	float choiceScore = 0;
	for(int i = 0; i < 3; i++){
		cout << choice + 1  << "| "<< choiceScore << " : " << results.m[0][i] << endl;
		if(results.m[0][i] > choiceScore){
			choiceScore = results.m[0][i];
			choice = i;
		}
	}
	return choice;
}

int main(){
	const float alpha = 0.1;
	const int I = 5;
	const int J = 4;
	const int K = 3;
	float data[100][5];
	int select;
	int goal;
	string line;
	srand(time(NULL));
//read in data set	
	ifstream in("irisClean.dat");
	for(int i = 0; i < 150; i++) in >> data[i][0] >> data[i][1] >> data[i][2] >> data[i][3] >> data[i][4];
	in.close();
	
//set up weights
	cout << "v:" << endl;
	Matrix v(J, I);
	v.print();
	
	cout << "w:" << endl;
	Matrix w(K, J);
	w.print();
	for(int ev = 0; ev < 5; ev++){
	
		select = rand() % 100;
		cout << ">" << select << "<" << endl;
		
		float input[I];
		input[0] = -1;
		for(int i = 0; i < 4; i++){
			input[i + 1] = data[select][i];
		}
		goal = (int)data[select][4];
		cout << "<" << goal << ">" << endl;
		float t[3] = {0.0, 0.0, 0.0};
		t[goal] = 1.0;
		
		//for(int i = 0; i < 5; i++) cout << "| " << data[select][i] << endl; 
	//forward
		//cout << "x:" << endl;
		Matrix x(input, I);
		//x.print();

		//cout << "g:" << endl;
		Matrix g(x.s(v));
		//g.print();
		
		//cout << "a:" << endl;
		float data2[J];
		data2[0] = 0.5;
		for(int i = 0; i < 3; i++){
			data2[i + 1] = g.m[0][i];
		}
		Matrix a(data2, J);
		//a.print();

		cout << "y:" << endl;
		Matrix y(a.s(w));
		y.print();
	
	//back
		//float sumX = 0.0;
		//for(int i = 0; i < I; i++) sumX += x.m[0][i];
		//calculate deltaY
		float deltaY[3];
		for(int k = 0; k < K; k++) {
			cout << "(" << y.m[0][k] << " - " << t[k] << ") * (1 - " << y.m[0][k] << ") = " << (y.m[0][k] - t[k]) * y.m[0][k] * (1 - y.m[0][k]) << endl;
			deltaY[k] = (y.m[0][k] - t[k]) * y.m[0][k] * (1 - y.m[0][k]);
			if(abs(deltaY[k]) < 0.00001) deltaY[k] = 0.0;
			//if(deltaY[k] > 100) deltaY[k] = 100;
			//if(deltaY[k] < -100) deltaY[k] = -100;
		}
		cout << "> ";
		for(int k = 0; k < K; k++) cout << deltaY[k] << endl;
		//calculate deltaA
		float deltaA[J];
		//float sumDeltaA = 0.0;
		for(int j = 0; j < J; j++) {
			float sum = 0;
			for(int k = 0; k < K; k++) {
				//cout << w.m[k][j] << " * " << deltaY[k] << " = " << w.m[k][j] * deltaY[k] << endl;
				sum += w.m[k][j] * deltaY[k];
			}
			deltaA[j] = a.m[0][j] * (1 - a.m[0][j]) * sum; 
			if(abs(deltaA[j]) < 0.00001) deltaA[j] = 0.0;
			//if(deltaA[j] > 100) deltaA[j] = 100;
			//if(deltaA[j] < -100) deltaA[j] = -100;
			//sumDeltaA += deltaA[j];
		}
		cout << "< "; 
		for(int j = 0; j < J; j++) cout << deltaA[j] << endl;
		//adjust w
		for(int k = 0; k < K; k++){
			for(int j = 0; j < J; j++){
				cout << w.m[k][j] << " + (" << alpha << " * " << deltaY[k] << " * " << deltaA[j]  << ") = " << w.m[k][j] + (alpha * deltaY[k] * deltaA[j]) << endl;
				w.m[k][j] = w.m[k][j] + (alpha * deltaY[k] * deltaA[j]);
				//if(w.m[k][j] > 100) w.m[k][j] = 100;
				//if(w.m[k][j] < -100) w.m[k][j] = -100;
			}
		}
		//adjust v
		for(int j = 0; j < J; j++){
			for(int i = 0; i < I; i++){
				v.m[j][i] = v.m[j][i] + (alpha * deltaA[j] * x.m[0][i]);
				//if(v.m[j][i] > 100) v.m[j][i] = 100;
				//if(v.m[j][i] < -100) v.m[j][i] = -100;
			}
		}
	}
	//cout << "v:" << endl;
	//v.print();
	
	//cout << "w:" << endl;
	//w.print();
}
