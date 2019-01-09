#include <iostream>
#include <math.h>
using namespace std;

float** reluActivate(float inputMatrix[][], int m) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (inputMatrix[i][j] <= 0) inputMatrix[i][j] = 0;
		}
	}
}

float** tanhActivate(float inputMatrix[][], int m) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			float x = inputMatrix[i][j];
			inputMatrix[i][j] = (exp(2*x) - 1)/(exp(2*x) + 1);
		}
	}
}

int main() {
	float inputMatrix[m][m];
	float** reluActivatedMatrix = reluActivate(inputMatrix);
	float** tanhActivatedMatrix = tanhActivate(inputMatrix);
}