#include <iostream>
#include <fstream>
#include <string.h>
#include "helper.h"
using namespace std;
int n,f,p;
float** computeConv0(float** inputMatrix, float** squareKernel) {
	int d=(n+2*p-f + 1);
	float** conv;
	conv=new float*[d];
	for(int i=0;i<d;i++)
		conv[i]=new float[d];
	for (int i = 0; i < n+2*p-f + 1; i++) {
		for (int j = 0; j < n+2*p-f + 1; j++) {
			conv[i][j] = 0;
			for (int u = i; u < i+f; u++) {
				for (int v = j; v < j+f; v++) {
					conv[i][j] += inputMatrix[u][v] * squareKernel[i+f-1-u][j+f-1-v];
				}
			}
		}
	}
	return conv;
}
float** computeConv1(float** inputMatrix, float** squareKernel) {
	float teoplitz[(n+2*p-f+1)*(n+2*p-f+1)][f*f];
	for(int i=0;i<(n+2*p-f+1)*(n+2*p-f+1);i++)
	{
		int r=(i)/(n+2*p-f+1);
		int c=i%(n+2*p-f+1);
		for(int j=0;j<f*f;j++)
		{
			int r1=r+j/f;
			int c1=c+j%f;
			teoplitz[i][j]=inputMatrix[r1][c1];
		}
	}
	float flipedkernal[f*f];
	int temp=0;
	for(int i=f-1;i>=0;i--)
	{
		for(int j=f-1;j>=0;j--)
		{
			flipedkernal[temp]=squareKernel[i][j];
			temp++;
		}
	}
	int d=(n+2*p-f + 1);
	float** conv;
	conv=new float*[d];
	for(int i=0;i<d;i++)
		conv[i]=new float[d];
	for(int i=0;i<(n+2*p-f+1)*(n+2*p-f+1);i++)
	{
		float sum=0;
		for(int j=0;j<f*f;j++)
		{
			sum+=teoplitz[i][j]*flipedkernal[j];
		}
		int r=i/(n+2*p-f+1);
		int c=i%(n+2*p-f+1);
		conv[r][c]=sum;
	}
	return conv;
}

int main(int argc,char** argv){
	char* mode=argv[1];
	char* m1;
	char* m2;
	float **inputMatrix;
	float **squareKernel;
	float * inputvector;
	if(strcmp(mode,"sigmoid")==0||strcmp(mode,"softmax")==0)
	{
		m1=argv[2];
		n=stoi(argv[3]);
		inputvector = new float [n];
		ifstream file;
		file.open(m1);
		if (!file) {
	    cerr << "Unable to open file datafile.txt";
	    exit(1);
		}
		else
		{
			float x;
			for(int i=0;i<n;i++)
			{
				file >> x;
				inputvector[i]=x;
			}
			file.close();
		}
	}
	else if(strcmp(mode,"conv0")==0||strcmp(mode,"conv1")==0||strcmp(mode,"avgpool")==0||strcmp(mode,"maxpool")==0||strcmp(mode,"tanh")==0||strcmp(mode,"relu")==0)
	{
		p=atoi(argv[2]);
		m1=argv[3];
		n=stoi(argv[4]);	
		int n1=n+2*p;
		inputMatrix = new float *[n1];
		for(int i = 0; i <n1; i++)
	    inputMatrix[i] = new float[n1];
		ifstream file;
		file.open(m1);
		if (!file) {
	    cerr << "Unable to open file datafile.txt";
	    exit(1);
		}
		else
		{
			float x;
			for(int i=p;i<n+p;i++)
			{
				for(int j=p;j<n+p;j++)
				{
					file >> x;
					inputMatrix[j][i]=x;
				}
			}
			file.close();
		}
		if(strcmp(mode,"conv0")==0||strcmp(mode,"conv1")==0)
		{
			m2=argv[5];
			f=stoi(argv[6]);
			squareKernel = new float *[f];
			for(int i = 0; i <f; i++)
	    		squareKernel[i] = new float[f];
			file.open(m2);
			if (!file) {
			    cerr << "Unable to open file datafile.txt";
			    exit(1);
			}
			else
			{
				float x;
				for(int i=0;i<f;i++)
				{
					for(int j=0;j<f;j++)
					{
						file >> x;
						squareKernel[j][i]=x;
					}
				}
				file.close();
			}
		}
		else if(strcmp(mode,"maxpool")==0||strcmp(mode,"avgpool")==0)
		{
			f=stoi(argv[5]);
		}
	}

	float** result;
	float* result2;
	if(strcmp(mode,"conv0")==0)
		result = computeConv0(inputMatrix,squareKernel);
	else if(strcmp(mode,"conv1")==0)
		result = computeConv1(inputMatrix, squareKernel);
	else if(strcmp(mode,"avgpool")==0)
		result=avgpool(inputMatrix,n+2*p,f);
	else if(strcmp(mode,"maxpool")==0)
		result=maxpool(inputMatrix,n+2*p,f);
	else if(strcmp(mode,"relu")==0)
		result=relu(inputMatrix,n+2*p);
	else if(strcmp(mode,"tanh")==0)
		result=tanh(inputMatrix,n+2*p);
	else if(strcmp(mode,"sigmoid")==0)
		result2=sigmoid(inputvector,n);
	else if(strcmp(mode,"softmax")==0)
		result2=softmax(inputvector,n);
	int d;
	if(strcmp(mode,"conv0")==0||strcmp(mode,"conv1")==0||strcmp(mode,"avgpool")==0||strcmp(mode,"maxpool")==0)
	{
		d=(n+2*p-f + 1);
		for(int i=0;i<d;i++)
		{
			for(int j=0;j<d;j++)
			{
				cout<<result[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	else if(strcmp(mode,"tanh")==0||strcmp(mode,"relu")==0)
	{
		d=(n+2*p);
		for(int i=0;i<d;i++)
		{
			for(int j=0;j<d;j++)
			{
				cout<<result[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	else if(strcmp(mode,"sigmoid")==0||strcmp(mode,"softmax")==0)
	{
		d=n;
		for(int i=0;i<d;i++)
		{
			cout<<result2[i]<<" ";
		}
		cout<<endl;
	}
	// cout<<endl;
	// 	for(int i=0;i<d;i++)
	// 	{
	// 		for(int j=0;j<d;j++)
	// 		{
	// 			cout<<inputMatrix[i][j]<<" ";
	// 		}
	// 		cout<<endl;
	// 	}
	return 0;
}