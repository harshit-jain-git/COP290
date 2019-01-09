#include <iostream>
using namespace std;

float** computeConv(float inputMatrix[][], float squareKernel[][]) {
	float conv[m - n + 1][m - n + 1];
	for (int i = 0; i < m - n + 1; i++) {
		for (int j = 0; j < m - n + 1; j++) {
			conv[i][j] = 0;
			for (int u = max(0, i − n); u < min(i, n); u++) {
				for (int v = max(0, j − n); v < min(j, n); v++) {
					conv[i][j] += inputMatrix[u][v] * squareKernel[i - u + 1][j - v + 1];
				}
			}
		}
	}
}

int main(){
	float inputMatrix[m][m];
	float squareKernel[n][n];
	float** convolution = computeConv(inputMatrix, squareKernel);
	float paddedInputMatrix[m + n - 1][m + n - 1] = {0}{0};
	for (int i = (n - 1)/2; i < m + (n - 1)/2; i++) {
		for (int j = (n - 1)/2; j < m + (n - 1)/2; j++) {
			paddedInputMatrix[i][j] = inputMatrix[i - (n - 1)/2][j - (n - 1)/2];
		}
	}
	float** paddedConvolution = computeConv(paddedInputMatrix, squareKernel);
}