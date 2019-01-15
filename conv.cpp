#include <iostream>
#include <fstream>
#include <string>
#include "helper.h"
using namespace std;
int n,f,p;
float** computeConv0(float inputMatrix[][n], float squareKernel[][f]) {
	int d=(n+2*p-f + 1);
	float conv[d][d];
	for (int i = 0; i < n+2*p-f + 1; i++) {
		for (int j = 0; j < n+2*p-f + 1; j++) {
			conv[i][j] = 0;
			for (int u = i; u < i+f; u++) {
				for (int v = j; v < j+f; v++) {
					conv[i][j] += inputMatrix[u][v] * squareKernel[i+f - u][j+f-v];
				}
			}
		}
	}
	cout<<"checkpoint3"<<endl;
	return (float**)conv;
}
float** computeConv1(float inputMatrix[][n+2*p], float* squareKernel[][f]) {
	float teoplitz[(n+2*p-f+1)*(n+2*p-f+1)][f*f];
	for(int i=0;i<(n+2*p-f+1);i++)
	{
		int r=(i)/(n+2*p-f+1);
		r=r*f;
		int c=i%(n+2*p-f+1);
		c=c*f;
		for(int j=0;j<f*f;j++)
		{
			r+=j/f;
			c+=j%f;
			teoplitz[i][j]=inputMatrix[r][c];
		}
	}
	float flipedkernal[f*f];
	for(int i=f-1;i>=0;i--)
	{
		for(int j=f-1;j>=0;j--)
		{
			int temp=f*(f-i-1)+(f-j-1);
			flipedkernal[temp]=squareKernel[j][i];
		}
	}
	float conv[n+2*p-f + 1][n+2*p-f + 1];
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
	return (float**)conv;
}

int main(int argc,char** argv){
	p=atoi(argv[2]);
	n=stoi(argv[4]);
	f=stoi(argv[6]);
	char* m1=argv[3];
	char* m2=argv[5];
	int mode=stoi(argv[1]);
	//convolution_formula=0  and as matrix multiplication=1
	float inputMatrix[n+2*p][n+2*p]={0};
	float squareKernel[f][f];
	cout<<"checkpoint1"<<endl;
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
	cout<<"checkpoint2"<<endl;
	float** convolution;
	if(mode==0)
		convolution = computeConv0((float**)inputMatrix,(float**)squareKernel);
	else if(mode==1)
		convolution = computeConv1((float**)inputMatrix, (float**)squareKernel);

	int d=(n+2*p-f + 1);
	for(int i=0;i<d;i++)
	{
		for(int j=0;j<d;j++)
		{
			cout<<convolution[i][j]<<" ";
		}
		cout<<endl;
	}

}