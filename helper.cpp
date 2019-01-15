#include <iostream>
#include <math.h>
#include "helper.h"
using namespace std;

float** relu(float** inputMatrix, int m) {
	float** A;
	A=new float*[m];
	for(int i=0;i<m;i++)
		A[i]=new float[m];
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (inputMatrix[i][j] <= 0) A[i][j] = 0.0;
			else
				A[i][j]=inputMatrix[i][j];
		}
	}
	return A;
}

float** tanh(float** inputMatrix, int m) {
	float** A;
	A=new float*[m];
	for(int i=0;i<m;i++)
		A[i]=new float[m];
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			float x = inputMatrix[i][j];
			//cout<<x<<endl;
			if(x<=10)
				A[i][j] = (exp(2*x) - 1)/(exp(2*x) + 1);
			else
				A[i][j]=(float)1;
		}
	}
	return A;
}
//maxpool with stride=1
float** maxpool(float** inputMatrix, int n,int f){
	int m=n-f+1;
	float** A;
	A=new float*[m];
	for(int i=0;i<m;i++)
		A[i]=new float[m];
	for(int i=0;i<n-f+1;i++)
	{
		for(int j=0;j<n-f+1;j++)
		{
			float max1=0;
			for(int u=i;u<i+f;u++)
			{
				for(int v=j;v<j+f;v++)
				{
					max1=max(max1,inputMatrix[u][v]);
				}
			}
			A[i][j]=max1;
		}
	}
	return A;
}

float** avgpool(float** inputMatrix, int n,int f){
	int m=n-f+1;
	float** A;
	A=new float*[m];
	for(int i=0;i<m;i++)
		A[i]=new float[m];
	for(int i=0;i<n-f+1;i++)
	{
		for(int j=0;j<n-f+1;j++)
		{
			double sum=0;
			for(int u=i;u<i+f;u++)
			{
				for(int v=j;v<j+f;v++)
				{
					sum+=inputMatrix[u][v];
				}
			}
			A[i][j]=(float)(sum/(f*f));
		}
	}
	return A;
}
float* sigmoid(float* inputVector,int n)
{
	float* A;
	A=new float[n];
	for(int i=0;i<n;i++)
	{
		A[i]=1/(1.0+exp(0-inputVector[i]));
	}
	return A;
}

float* softmax(float* inputVector,int n)
{
	float max1=inputVector[0];
	for(int i=1;i<n;i++)
	{
		max1=max(max1,inputVector[i]);
	}
	float* A;
	A=new float[n];
	double sum=0;
	for(int i=0;i<n;i++)
	{
		sum+=exp(inputVector[i]-max1);
	}
	for(int i=0;i<n;i++)
	{
		A[i]=(float)(exp(inputVector[i]-max1)/sum);
	}
	return A;
}
