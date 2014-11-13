#include "NN.h"

int main(){
	double alpha = 0.1;
	
	float *data = (float *)calloc(5, sizeof(float));
	float goal;
	string line;
	
	ifstream in("irisClean.dat");
	
//set up weights
	cout << "v:" << endl;
	Matrix v(3, 5);
	v.print();
	
	cout << "w:" << endl;
	Matrix w(3, 4);
	w.print();
	
	for(int ev = 0; ev < 1; ev++){
		in >> data[0] >> data[1] >> data[2] >> data[3] >> data[4];
		float *input = (float *)calloc(5, sizeof(float));
		//input[0] = rand()/float(RAND_MAX);
		input[0] = 1.0;
		for(int i = 0; i < 4; i++){
			input[i + 1] = data[i];
		}
		goal = data[4];
		
	//forward
		cout << "x:" << endl;
		Matrix x(input, 5);
		x.print();
/*		
		cout << "v:" << endl;
		Matrix v(3, 5);
		v.print();
*/	
		cout << "g:" << endl;
		Matrix g(x.s(v));
		g.print();
		
		cout << "a:" << endl;
		float *data2 = (float *)calloc(4, sizeof(float));
		data2[0] = 0.5;
		for(int i = 0; i < 3; i++){
			data2[i + 1] = g.m[0][i];
		}
		Matrix a(data2, 4);
		a.print();
/*
		cout << "w:" << endl;
		Matrix w(3, 4);
		w.print();
*/
		cout << "result:" << endl;
		Matrix result(a.s(w));
		result.print();
	//back
		
		
	}
	in.close();
	
	
}
