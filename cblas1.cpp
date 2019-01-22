#include <bits/stdc++.h>
#include <cblas.h>
#include <time.h>

//A=d*d rows and f*f columns
//B=f*f rows and 1 column
double openblas_conv(float* A,float* B,float* C,int m,int l,int n)
{
	clock_t t;
    t = clock();
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, l, 1.0, A, l, B, n, 0.0, C, n);
    t = clock() - t;
	double time = (double)t/CLOCKS_PER_SEC;
	time=time*(1000000);
	return time;
	//cout << "Time taken in microseconds: " << time << endl;
}