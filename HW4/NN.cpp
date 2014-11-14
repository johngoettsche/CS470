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
	double alpha = 0.1;
	
	float *data = (float *)calloc(5, sizeof(float));
	int goal;
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
		goal = (int)data[4];
		
	//forward
		cout << "x:" << endl;
		Matrix x(input, 5);
		x.print();

		cout << "g:" << endl;
		Matrix g(x.s(v));
		g.print();
		
		cout << "a:" << endl;
		float *data2 = (float *)calloc(4, sizeof(float));
		data2[0] = 1.0;
		for(int i = 0; i < 3; i++){
			data2[i + 1] = g.m[0][i];
		}
		Matrix a(data2, 4);
		a.print();

		cout << "result:" << endl;
		Matrix result(a.s(w));
		result.print();
		
		int ch = getChoice(result);
		cout << ch << endl;
		cout << goal << endl;
		cout << result.m[0][goal] << " - " << result.m[0][ch] << " = " << result.m[0][goal] - result.m[0][ch] << endl;
	//back

	}
	in.close();
}
