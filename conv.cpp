#include <iostream>
#include <fstream>
#include <string>
#include "helper.h"
using namespace std;
int n,f,p;
float** computeConv0(float** inputMatrix, float** squareKernel) {
	//cout<<"checkpoint3"<<endl;
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
					//cout<<inputMatrix[u][v]<<" "<<squareKernel[i+f-1-u][j+f-1-v]<<endl;
					conv[i][j] += inputMatrix[u][v] * squareKernel[i+f-1-u][j+f-1-v];
					//cout<<conv[i][j]<<endl;
				}
			}
			//cout<<conv[i][j]<<endl;
		}
	}
	//cout<<"checkpoint4"<<endl;
	return conv;
}
float** computeConv1(float** inputMatrix, float** squareKernel) {
	//cout<<"checkpoint3"<<endl;
	float teoplitz[(n+2*p-f+1)*(n+2*p-f+1)][f*f];
	//cout<<"checkpoint4"<<endl;
	for(int i=0;i<(n+2*p-f+1)*(n+2*p-f+1);i++)
	{
		int r=(i)/(n+2*p-f+1);
		int c=i%(n+2*p-f+1);
		for(int j=0;j<f*f;j++)
		{
			int r1=r+j/f;
			int c1=c+j%f;
			//cout<<"checkpoint"<<endl;
			teoplitz[i][j]=inputMatrix[r1][c1];
		}
	}
	//cout<<"checkpoint5"<<endl;
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
	//cout<<"checkpoint6"<<endl;
	int d=(n+2*p-f + 1);
	float** conv;
	conv=new float*[d];
	for(int i=0;i<d;i++)
		conv[i]=new float[d];
	//cout<<"checkpoint7"<<endl;
	//float conv[n+2*p-f + 1][n+2*p-f + 1];
	for(int i=0;i<(n+2*p-f+1)*(n+2*p-f+1);i++)
	{
		int sum=0;
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
	p=atoi(argv[2]);
	n=stoi(argv[4]);
	f=stoi(argv[6]);
	char* m1=argv[3];
	char* m2=argv[5];
	int mode=stoi(argv[1]);
	int n1=n+2*p;
	//convolution_formula=0  and as matrix multiplication=1
	float **inputMatrix;
	inputMatrix = new float *[n1];
	for(int i = 0; i <n1; i++)
    inputMatrix[i] = new float[n1];
	
	float **squareKernel;
	squareKernel = new float *[f];
	for(int i = 0; i <f; i++)
    squareKernel[i] = new float[f];
	
	// float inputMatrix[n+2*p][n+2*p]={0};
	// float squareKernel[f][f];
	//cout<<"checkpoint1"<<endl;
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
	// for(int i=0;i<n1;i++)
	// {
	// 	for(int j=0;j<n1;j++)
	// 	{
	// 		cout<<inputMatrix[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	// for(int i=0;i<f;i++)
	// {
	// 	for(int j=0;j<f;j++)
	// 	{
	// 		cout<<squareKernel[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	//cout<<"checkpoint2"<<endl;
	float** convolution;
	if(mode==0)
		convolution = computeConv0(inputMatrix,squareKernel);
	else if(mode==1)
		convolution = computeConv1(inputMatrix, squareKernel);

	int d=(n+2*p-f + 1);
	for(int i=0;i<d;i++)
	{
		for(int j=0;j<d;j++)
		{
			cout<<convolution[i][j]<<" ";
		}
		cout<<endl;
	}

	// float* inputvector=new float[5];
	// for(int i=0;i<5;i++)
	// 	inputvector[i]=i;
	// float * result=softmax(inputvector,5);
	// for(int i=0;i<5;i++)
	// {
	// 	cout<<result[i]<<" ";
	// 	cout<<endl;
	// }
	// float ** result=avgpool(inputMatrix,n,f);
	// for(int i=0;i<n-f+1;i++)
	// {
	// 	for(int j=0;j<n-f+1;j++)
	// 	{
	// 		cout<<result[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
}