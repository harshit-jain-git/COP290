#include <iostream>
#include <math.h>
#include "helper.h"
using namespace std;

float** relu(float* inputMatrix[], int m) {
	float A[m][m];
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (inputMatrix[i][j] <= 0) A[i][j] = 0.0;
			else
				A[i][j]=inputMatrix[i][j];
		}
	}
	return A;
}

float** tanh(float* inputMatrix[], int m) {
	float A[m][m];
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			float x = inputMatrix[i][j];
			A[i][j] = (exp(2*x) - 1)/(exp(2*x) + 1);
		}
	}
	return A;
}
//maxpool with stride=1
float** maxpool(float* inputMatrix[], int n,int f){
	float A[n-f+1][n-f+1];
	for(int i=0;i<n-f+1;i++)
	{
		for(int j=0;j<n-f+1;j++)
		{
			int max=0;
			for(int u=i;u<i+f;u++)
			{
				for(int v=j;v<j+f;v++)
				{
					max=max(max,inputMatrix[u][v]);
				}
			}
			A[i][j]=max;
		}
	}
	return A;
}

float** avgpool(float* inputMatrix[], int n,int f){
	float A[n-f+1][n-f+1];
	for(int i=0;i<n-f+1;i++)
	{
		for(int j=0;j<n-f+1;j++)
		{
			int sum=0;
			for(int u=i;u<i+f;u++)
			{
				for(int v=j;v<j+f;v++)
				{
					sum+=inputMatrix[u][v];
				}
			}
			A[i][j]=sum/(f*f);
		}
	}
	return A;
}
float* sigmoid(float inputVector[],int n)
{
	int A[n];
	for(int i=0;i<n;i++)
	{
		A[i]=1/(1.0+exp(0-inputVector[i]));
	}
	return A;
}

float* softmax(float inputVector[],int n)
{
	int A[n];
	int sum=0;
	for(int i=0;i<n;i++)
	{
		sum+=exp(inputVector[i]);
	}
	for(int i=0;i<n;i++)
	{
		A[i]=exp(inputVector[i])/sum;
	}
	return A;
}
