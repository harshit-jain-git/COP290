#include <iostream>
#include <math.h>
#include "helper.h"
#include<string.h> 
using namespace std;

// Function to print matrix
void printMatrix(float** matrix, int dim) {
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

// Function to print vector
void printVector(float* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		cout << vector[i] << " ";
	}
	cout << endl;
}

float** computeConv0(float** inputMatrix, float** squareKernel, int n, int p, int f) {
	int d = (n + 2*p - f + 1);
	float** conv;
	conv = new float*[d];
	for(int i = 0;i < d;i++)
	{
		conv[i] = new float[d];
	}
	// Evaluating the Convolution
	for (int i = 0; i < n + 2*p - f + 1; i++) {
		for (int j = 0; j < n + 2*p - f + 1; j++) {
			conv[i][j] = 0;
			for (int u = i; u < i + f; u++) {
				for (int v = j; v < j + f; v++) {
					conv[i][j] += inputMatrix[u][v] * squareKernel[i + f - 1 - u][j + f - 1 - v];
				}
			}
		}
	}
	return conv;
}

float** computeConv1(float** inputMatrix, float** squareKernel, int n, int p, int f) {
	float toeplitz[(n + 2*p - f + 1)*(n + 2*p - f + 1)][f*f];
	// Constructing the Toeplitz Matrix
	for(int i = 0; i < (n + 2*p - f + 1)*(n + 2*p - f + 1); i++)
	{
		int r = i/(n + 2*p - f + 1);
		int c = i % (n + 2*p - f + 1);
		for(int j = 0; j < f*f; j++)
		{
			int r1 = r + j/f;
			int c1 = c + j%f;
			toeplitz[i][j] = inputMatrix[r1][c1];
		}
	}

	float flippedkernal[f*f];
	int index = 0;
	// Constructing the flipped kernel
	for(int i = f - 1; i >= 0; i--)
	{
		for(int j = f - 1; j >= 0; j--)
		{
			flippedkernal[index] = squareKernel[i][j];
			index++;
		}
	}

	int convMatrixDim = (n + 2*p - f + 1);

	float** conv;
	conv = new float*[convMatrixDim];
	// Initializing the convolution matrix rows
	for (int i = 0; i < convMatrixDim; i++) 
	{
		conv[i] = new float[convMatrixDim];
	}
	// Evaluating the Convolution
	for (int i = 0; i < convMatrixDim*convMatrixDim; i++)
	{
		float sum = 0;
		for(int j = 0;j < f*f; j++)
		{
			sum += toeplitz[i][j]*flippedkernal[j];
		}
		int r = i/(n + 2*p - f + 1);
		int c = i%(n + 2*p - f + 1);
		conv[r][c] = sum;
	}
	return conv;
}

float** relu(float** inputMatrix, int n) {
	float** A;
	A = new float*[n];
	for(int i = 0; i < n; i++)
		A[i] = new float[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (inputMatrix[i][j] <= 0) A[i][j] = 0.0;
			else
				A[i][j] = inputMatrix[i][j];
		}
	}
	return A;
}

float** tanh(float** inputMatrix, int n) {
	float** A;
	A = new float*[n];
	for(int i = 0;i < n; i++)
	{
		A[i] = new float[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			float x = inputMatrix[i][j];
			if(x <= 10)
				A[i][j] = (exp(2*x) - 1)/(exp(2*x) + 1);
			else
				A[i][j] = (float)1;
		}
	}
	return A;
}

float** maxpool(float** inputMatrix, int n, int f){
	int m = n - f + 1;
	float** A = new float*[m];
	for(int i = 0; i < m; i++)
		A[i] = new float[m];
	for(int i = 0; i < n - f + 1; i++)
	{
		for(int j = 0; j < n - f + 1; j++)
		{
			float max1 = inputMatrix[i][j];
			for(int u = i; u < i + f; u++)
			{
				for(int v = j; v < j + f; v++)
				{
					max1 = max(max1,inputMatrix[u][v]);
				}
			}
			A[i][j] = max1;
		}
	}
	return A;
}

float** avgpool(float** inputMatrix, int n, int f){
	int m = n - f + 1;
	float** A = new float*[m];
	for(int i = 0; i < m; i++)
		A[i] = new float[m];
	for(int i = 0; i < n - f + 1; i++)
	{
		for(int j = 0; j < n - f + 1; j++)
		{
			double sum = 0;
			for(int u = i; u < i + f; u++)
			{
				for(int v = j; v < j + f; v++)
				{
					sum += inputMatrix[u][v];
				}
			}
			A[i][j] = (float)(sum/(f*f));
		}
	}
	return A;
}
float* sigmoid(float* inputVector, int n)
{
	float* A = new float[n];
	for(int i = 0; i < n; i++)
	{
		A[i] = 1/(1.0 + exp(-inputVector[i]));
	}
	return A;
}

float* softmax(float* inputVector, int n)
{
	float maxNum = inputVector[0];
	for(int i = 1; i < n; i++)
	{
		maxNum = max(maxNum, inputVector[i]);
	}
	float* A = new float[n];
	float sum = 0;
	for(int i = 0; i < n; i++)
	{
		sum += exp(inputVector[i] - maxNum);
	}
	for(int i = 0; i < n; i++)
	{
		A[i] = (float)(exp(inputVector[i] - maxNum)/sum);
	}
	return A;
}
