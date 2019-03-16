#include <iostream>
#include <math.h>
#include "helper.h"
#include <string.h> 
#include "mkl_multiply.h"
using namespace std;


// Function to print a linearized matrix given rows and columns
void print(const char * name, const float* matrix, int row, int column)
{
    printf("Matrix %s has %d rows and %d columns:\n", name, row, column);
    for (int i = 0; i < row; i++){
      for (int j = 0; j < column; j++){
        printf("%.3f ", matrix[i*column+j]);
      }
      printf("\n");
    }
    printf("\n");
}

//Function to print a matrix given rows and columns
void printMatrix(float** matrix, int dim1, int dim2) {
	for (int i = 0; i < dim1; i++) {
		for (int j = 0; j < dim2; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

// Function to print vector given its dimention
void printVector(float* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		cout << vector[i] << " ";
	}
	cout << endl;
}

//Function to compute convolution of two square matrices with dimentions nxn and fxf. p is padding.
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

//Function to convert a matrix (nxn) into 1D row major teoplitz form.
float* rmteoplitz(float** inputMatrix, int n,int f)
{
	int d=(n-f+1);
	float* T=new float[d*d*f*f];
	for(int i = 0; i < d*d; i++)
	{
		int r = i/d;
		int c = i % d;
		for(int j = 0; j < f*f; j++)
		{
			int r1 = r + j/f;
			int c1 = c + j%f;
			T[i*f*f+j] = inputMatrix[r1][c1];
		}
	}
	return T;
}

//Function to flip a fxf matrix and return its row major form.
float* flippedkernel(float** squareKernel, int f)
{
	float* F;
	int d=f*f;
	F=new float[d];
	int index = 0;
	// Constructing the flipped kernel
	for(int i = f - 1; i >= 0; i--)
	{
		for(int j = f - 1; j >= 0; j--)
		{
			F[index] = squareKernel[i][j];
			index++;
		}
	}
	return F;
}

//Function to convert a 3D matrix(lxfxf) to its row major form for 3D convolution.
float* kernel3d(float*** squareKernel, int f,int l)
{
	float* F;
	int d = f*f*l;
	F = new float[d];
	int index = 0;
	// Constructing the flipped kernel
	for(int k = 0; k < l; k++)
	{
		for(int i = 0; i < f; i++)
		{
			for(int j = 0; j < f; j++)
			{
				F[index] = squareKernel[k][i][j];
				index++;
			}
		}
	}
	return F;
}

//Function to convert a 3D matrix(lxnxn) into a row major teoplitz taking filter_size=f.
float* teoplitz3d(float*** inputMatrix, int n,int l,int f)
{
	int d = (n - f + 1);
	float* T = new float[d*d*f*f*l];
	int index = 0;
	for(int i = 0; i < d; i++)
	{
		for(int j = 0; j < d; j++)
		{
			for(int k = 0; k < l; k++)
			{
				for(int p = i; p < i + f; p++)
				{
					for(int q = j; q < j + f; q++)
					{
						T[index]=inputMatrix[k][p][q];
						index++;
					}
				}
			}
		}
	}
	return T;
}

//Function to compute correlation of two 3D matrices(lxnxn and lxfxf) and adding the bias to each term of resultant 2D matrix
float**  conv3d(float*** inputMatrix, float*** squareKernel, int n, int l, int f,float b) {
	float* T=teoplitz3d(inputMatrix,n,l,f);
	float* F = kernel3d(squareKernel, f,l);
	int d=n-f+1;
	float* C=new float[d*d];
	double t=mkl_multiply(T,F,C,d*d,f*f*l,1);
	float** result=new float*[d];
	for(int i=0;i<d;i++)
		result[i]=new float[d];
	for(int i=0;i<d*d;i++)
	{
		int r=i/d,c=i%d;
		result[r][c]=C[i]+b;
	}
	return result;
}

//Function to compute convolution of a nxn matix with fxf matrix using teoplitz matrix. p is padding.
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

	float flippedkernel[f*f];
	int index = 0;
	// Constructing the flipped kernel
	for(int i = f - 1; i >= 0; i--)
	{
		for(int j = f - 1; j >= 0; j--)
		{
			flippedkernel[index] = squareKernel[i][j];
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
			sum += toeplitz[i][j]*flippedkernel[j];
		}
		int r = i/(n + 2*p - f + 1);
		int c = i%(n + 2*p - f + 1);
		conv[r][c] = sum;
	}
	return conv;
}

//Relu function on a nxn input matrix
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

//tanh function on a nxn input matrix
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

//Maxpool function on a nxn input matrix with filter_size=f and stride=1
float** maxpool(float** inputMatrix, int n, int f, int s = 1){
	int m = (n - f)/s + 1;
	float** A = new float*[m];
	int index_1 = 0, index_2 = 0;
	for(int i = 0; i < m; i++)
		A[i] = new float[m];
	for(int i = 0; i < n - f + 1; i=i+s, index_1++)
	{
		index_2 = 0;
		for(int j = 0; j < n - f + 1; j=j+s, index_2++)
		{
			float max1 = inputMatrix[i][j];
			for(int u = i; u < i + f; u++)
			{
				for(int v = j; v < j + f; v++)
				{
					if (max1 < inputMatrix[u][v])
						max1 = inputMatrix[u][v];
				}
			}
			A[index_1][index_2] = max1;
		}
	}
	return A;
}

//Average_pool function on a nxn input matrix with filter_size=f and stride=1
float** avgpool(float** inputMatrix, int n, int f, int s = 1){
	int m = (n - f)/s + 1;
	float** A = new float*[m];
	int index_1 = 0, index_2 = 0;
	for(int i = 0; i < m; i++)
		A[i] = new float[m];
	for(int i = 0; i < n - f + 1; i=i+s, index_1++)
	{
		index_2 = 0;
		for(int j = 0; j < n - f + 1; j=j+s, index_2++)
		{
			double sum = 0;
			for(int u = i; u < i + f; u++)
			{
				for(int v = j; v < j + f; v++)
				{
					sum += inputMatrix[u][v];
				}
			}
			A[index_1][index_2] = (float)(sum/(f*f));
			//A[index_1][index_2] = inputMatrix[i][j];
		}
	}
	return A;
}

//sigmoid function on a vector having n elements.
float* sigmoid(float* inputVector, int n)
{
	float* A = new float[n];
	for(int i = 0; i < n; i++)
	{
		A[i] = 1/(1.0 + exp(-inputVector[i]));
	}
	return A;
}

//softmax function on a vector having n elements.
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
