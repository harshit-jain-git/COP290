#include<iostream>
#include<fstream>
#include<time.h>
#include<math.h>
#include "cblas_multiply.h"
#include "mkl_multiply.h"
#include "pthread_multiply.h"

#define L 32768
#define samples 10

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
	file.open("performance.csv");
	for (int i = 4; i <= L; i = 2*i) {
		file << i << ":	";
		matrix = new float[i*i];
		col_matrix = new float[i];
		ans = new float[i*i];
		generateMatrix(matrix, i, i);
		generateMatrix(col_matrix, i, 1);
		double pthread_time = 0;
		double mkl_time = 0;
		double cblas_time = 0;
		for (int j = 0; j < samples; j++) {
			pthread_time += pthread_multiply(matrix, col_matrix, ans, i, i, 1);
			mkl_time += mkl_multiply(matrix, col_matrix, ans, i, i, 1);
			cblas_time += cblas_multiply(matrix, col_matrix, ans, i, i, 1);
		}
		pthread_time = pthread_time/samples;
		mkl_time = mkl_time/samples;
		cblas_time = cblas_time/samples;
		file << pthread_time << "	" << mkl_time << "	" << cblas_time << endl;
	}
	file.close();
	return 0;
}