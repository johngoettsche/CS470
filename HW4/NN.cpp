#include "NN.h"

#define SHOW_PROG 1
#define SHOW_TEST 1
#define SHOW_WEIGHT 0
#define ITERATIONS 1
#define SUBMIT 0
#define BIAS -1

float checkLimit(float val){
	if(abs(val) < 0.001) val = 0.000;
	if(val > FLT_MAX / 2.0) val = FLT_MAX / 2.0;
	if(val < FLT_MIN / 2.0) val = FLT_MIN / 2.0;
	return val;
}

char *readData(){
	char *in;
	in = (char *)calloc(128, sizeof(char));
	in = fgets(in, 128, stdin);

	return in;
}

int main(){
	srand((unsigned)time(NULL));
	const float alpha = 0.1;
	const int I = 5;
	const int J = 4;
	const int K = 3;
	
	int rnd;
	int goal;
	string line;
	float input[I];
	float t[K] = {0.0, 0.0, 0.0};
	float maxval[4];
	float minval[4];
	char *inp;
	int *number;
	number = (int *)calloc(2, sizeof(int));
	char **nums;
	nums = (char **)calloc(2, sizeof(char *));
	
	inp = readData();
	int i = 0;
	nums[i] = strtok(inp, " ");
	while (i < 2) {
		//printf("token[%d]: %s\n", i, nums[i]);
		i++;
		nums[i] = strtok(NULL, " ");
	}
	// converts raw data to a string of characters negating the spaces.
	for(int n = 0; n < 2; n++) number[n] = atoi(nums[n]);
	//printf("*\n");
	//for(int n = 0; n < 2; n++) printf("token[%d]: %d\n", n, number[n]);
	int items = number[0];
	int elems = number[1];
	
	float data[items][elems];
	float rawdata[items][elems];
	if(SUBMIT){
		//read in data set	
		for(int l = 0; l < items; l++){
			inp = readData();
			i = 0;
			nums[i] = strtok(inp, " ");
			while (i < elems) {
				//printf("token[%d]: %s\n", i, nums[i]);
				i++;
				nums[i] = strtok(NULL, " ");
			}
			for(int n = 0; n < 2; n++) rawdata[l][i] = atoi(nums[n]);
		}
	} else {
		ifstream in("irisClean.dat");
		for(int i = 0; i < items; i++) {
			in >> rawdata[i][0] >> rawdata[i][1] >> rawdata[i][2] >> rawdata[i][3] >> rawdata[i][4];
			//cout << "reading" << i << ": " << rawdata[i][0] << " " << rawdata[i][1] << " " << rawdata[i][2] << " " << rawdata[i][3] << " | " << rawdata[i][4] << endl;
		}
		in.close();
	}

//normalizeData
	for(int c = 0; c < elems - 1; c++){
		maxval[c] = -10000.0;
		minval[c] = 10000.0;
		for(int r = 0; r < items; r++){
			if(rawdata[r][c] > maxval[c]) maxval[c] = rawdata[r][c];
			if(rawdata[r][c] < minval[c]) minval[c] = rawdata[r][c];
		}
		//cout << minval[c] << " : " << maxval[c] << endl;
	}
	for(int c = 0; c < elems -1; c++){
		//cout << "data ";
		for(int r = 0; r < items; r++){
			data[r][c] = (rawdata[r][c] - minval[c]) / (maxval[c] - minval[c]);
			//cout << data[r][c] << " ";
		}
		//cout << endl;
	}
	for(int r = 0; r < items; r++) data[r][4] = rawdata[r][4];
		
//set up weights
	Matrix *v = new Matrix(J, I);
	Matrix *w = new Matrix(K, J);
	Matrix *tempMatrix;
	if(SHOW_WEIGHT){
		cout << "w" << endl;
		w->print();
		cout << "v" << endl;
		v->print();
	}
	for(int ev = 0; ev < ITERATIONS; ev++){
	
		rnd = rand() % items;
		input[0] = BIAS;
		for(int i = 0; i < elems - 1; i++){
			input[i + 1] = data[rnd][i];
		}
		goal = (int)data[rnd][elems - 1];
		for(int k = 0; k < K; k++) t[k] = 0.0;
		t[goal] = 1.0;
		Matrix *x = new Matrix(input, I);
			if(SHOW_PROG)cout << "x" << endl;
			if(SHOW_PROG)x->print();
		Matrix *g = new Matrix(x->dotProduct(v));
			if(SHOW_PROG)cout << "g" << endl;
			if(SHOW_PROG)g->print();
		Matrix *a = g->s();
		a->m[0][0] = BIAS;
			if(SHOW_PROG)cout << "a" << endl;
			if(SHOW_PROG)a->print();
		Matrix *h = new Matrix(a->dotProduct(w));
			if(SHOW_PROG)cout << "h" << endl;
			if(SHOW_PROG)h->print();
		Matrix *y = h->s();
			if(SHOW_PROG)cout << "y" << endl;
			if(SHOW_PROG)y->print();
			if(SHOW_PROG)cout << "t" << endl;
			if(SHOW_PROG)for(int k = 0; k < K; k++)cout << t[k] << endl;
			if(SHOW_PROG)cout << "\nBACK" << endl;
	//back
		//calculate deltaY
		Matrix *deltaY = new Matrix(y);
		for(int k = 0; k < K; k++) {
			//deltaY->m[0][k] = (t[k] - y->m[0][k]) * y->m[0][k] * (1.0 - y->m[0][k]);
			deltaY->m[0][k] = (t[k] - y->m[0][k]);
		}
			if(SHOW_PROG)cout << "y" << endl;
			if(SHOW_PROG)y->print();
			if(SHOW_PROG)cout << "deltaY" << endl;
			if(SHOW_PROG)deltaY->print();
				
		//calculate deltaA
		Matrix *deltaA = new Matrix(a);
		tempMatrix = deltaY->dotProduct(w->flip());
			if(SHOW_PROG)cout << "tempMatrix - deltaA" << endl;
			if(SHOW_PROG)tempMatrix->print();
		for(int j = 0; j < J; j++) {
			//deltaA->m[0][j] = (a->m[0][j] * (1 - a->m[0][j])) * tempMatrix->m[0][j]; 
			deltaA->m[0][j] = tempMatrix->m[0][j]; 
		}
			//deltaA->m[0][0] = 0.0;
			if(SHOW_PROG)cout << "deltaA" << endl;
			if(SHOW_PROG)deltaA->print();
		
		//adjust w
		tempMatrix = deltaY->flip()->dotProduct(a->flip());
			if(SHOW_PROG)cout << "tempMatrix - w" << endl;
			if(SHOW_PROG)tempMatrix->print();
		for(int k = 0; k < K; k++){
			for(int j = 0; j < J; j++){
				w->m[k][j] += alpha * tempMatrix->m[0][j];
			}
		}
		//adjust v
		deltaA->m[0][0] = 0.0;
		tempMatrix = deltaA->flip()->dotProduct(x->flip());
			if(SHOW_PROG)cout << "tempMatrix - v" << endl;
			if(SHOW_PROG)tempMatrix->print();
		for(int j = 0; j < J; j++){
			for(int i = 0; i < I; i++){
				v->m[j][i] += alpha * tempMatrix->m[j][i];
			}
		}
		delete x;
		delete g;
		delete a;
		delete h;
		delete y;
		delete deltaA;
		delete deltaY;
	}
	//testing
	int max;
	int success = 0;
	if(SUBMIT){
		inp = readData();
		i = 0;
		nums[i] = strtok(inp, " ");
		while (i < 2) {
			//printf("token[%d]: %s\n", i, nums[i]);
			i++;
			nums[i] = strtok(NULL, " ");
		}
		// converts raw data to a string of characters negating the spaces.
		for(int n = 0; n < 2; n++) number[n] = atoi(nums[n]);
		//printf("*\n");
		//for(int n = 0; n < 2; n++) printf("token[%d]: %d\n", n, number[n]);
		items = number[0];
		elems = number[1] + 1;
	}
	float tdata[items][elems];
	float testdata[items][elems];
	if(SUBMIT){
		//read in data set	
		for(int l = 0; l < items; l++){
			inp = readData();
			i = 0;
			nums[i] = strtok(inp, " ");
			while (i < elems) {
				//printf("token[%d]: %s\n", i, nums[i]);
				i++;
				nums[i] = strtok(NULL, " ");
			}
			for(int n = 0; n < 2; n++) testdata[l][i] = atoi(nums[n]);
		}
		
	} else {
		for(int r = 0; r < items; r++){
			//cout << r << "testdata{ ";
			for(int c = 0; c < elems; c++){
				testdata[r][c] = rawdata[r][c];
				//cout << testdata[r][c] << " " ;
			}
			//cout << "}" << endl;
		}
	}
	//normalizeTestData
	for(int r = 0; r < items; r++){
		for(int c = 0; c < elems - 1; c++){
			tdata[r][c] = (testdata[r][c] - minval[c]) / (maxval[c] - minval[c]);
		}
	}
	success = 0;
	int count = 0;
	for(int ds = 0; ds < items; ds++){
		goal = rawdata[ds][elems - 1];
		input[0] = BIAS;
		for(int i = 0; i < elems - 1; i++){
			input[i + 1] = tdata[ds][i];
		}
		//cout << "input " << ds << ": " << input[0] << " " << input[1] << " " << input[2] << " " << input[3] << " " << input[4] << endl; 
		Matrix *x = new Matrix(input, I);
		Matrix *g = new Matrix(x->dotProduct(v));
		Matrix *a = g->s();
		a->m[0][0] = BIAS;
		Matrix *h = new Matrix(a->dotProduct(w));
		Matrix *y = h->s();
		max = 0;
		float maxScore = 0;
		if(SHOW_TEST)cout << y->m[0][0] << " : "  << y->m[0][1] << " : " << y->m[0][2] << " || ";
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
		if(!SUBMIT){
			if(goal == max) success++;
		}
		if(SHOW_TEST)cout << max << " : " << goal << endl;
		//cout << "TEST(" << count << "): " << max << endl;
		count++;
	}
	cout << "success " << success << " out of " << count << " or " << 100 * (float)success / (float)count << "%" << endl;
	if(SHOW_WEIGHT){
		cout << "\nw" << endl;
		w->print();
		cout << "v" << endl;
		v->print();
	}
}
