#include<iostream>
#include<fstream>
#include<time.h>
#include <math.h>
#include "cblas_multiply.h"
#include "mkl_multiply.h"
#include "pthread_multiply.h"

#define L 16384
#define samples 20

using namespace std;

void generateMatrix(float* A, int a, int b) {
	int index = 0;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			A[index++] = -1024 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2048)));
		}

	}
}

int main(int argc, char** argv) {
	float* matrix;
	float* ans;
	float* col_matrix;
	ofstream file;
	file.open("performance.dat");
	for (int i = 2; i <= L; i = 2*i) {
		if(i>4)
			file << i << " ";
		matrix = new float[i*i];
		col_matrix = new float[i];
		ans = new float[i];
		generateMatrix(matrix, i, i);
		generateMatrix(col_matrix, i, 1);
		double pthread_time[samples],mkl_time[samples],cblas_time[samples];
		double mkl_mean = 0,pthread_mean=0,cblas_mean=0,pthread_sd=0,mkl_sd=0,cblas_sd=0;
		for (int j = 0; j < samples; j++) {
			pthread_time[j]= pthread_multiply(matrix, col_matrix, ans, i, i, 1);
			pthread_mean+=pthread_time[j];
			mkl_time[j]= mkl_multiply(matrix, col_matrix, ans, i, i, 1);
			mkl_mean+=mkl_time[j];
			cblas_time[j]= cblas_multiply(matrix, col_matrix, ans, i, i, 1);
			cblas_mean+=cblas_time[j];
		}
		pthread_mean = pthread_mean/samples;
		mkl_mean = mkl_mean/samples;
		cblas_mean = cblas_mean/samples;
		for(int j = 0; j < samples; j++)
		{
			pthread_sd += pow((pthread_time[j] - pthread_mean), 2);
			mkl_sd += pow((mkl_time[j] - mkl_mean), 2);
			cblas_sd += pow((cblas_time[j] - cblas_mean), 2);
		}
		pthread_sd = pthread_sd/samples;
		pthread_sd = sqrt(pthread_sd);
		mkl_sd = mkl_sd/samples;
		mkl_sd = sqrt(mkl_sd);
		cblas_sd = cblas_sd/samples;
		cblas_sd = sqrt(cblas_sd);
		if(i > 4)
			file << pthread_mean << " " << pthread_sd << " " << mkl_mean << " " << mkl_sd << " " << cblas_mean << " " << cblas_sd << endl;
	}
	file.close();
	return 0;
}