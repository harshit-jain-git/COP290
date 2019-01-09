#include <iostream>
#include <math.h>
using namespace std;

int main() {
	float vector[m];
	float sigmoidProbab[m];
	float softmaxProbab[m];
	float constant = 0.0;
	for (int i = 0; i < m; i++) {
		sigmoidProbab[i] = 1/(1 + exp (-vector[i]));
		softmaxProbab[i] = exp (vector[i]);
		constant += exp (vector[i]);
	}
	for (int i = 0; i < m; i++) softmaxProbab[i] = softmaxProbab[i]/constant;
}