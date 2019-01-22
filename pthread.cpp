#include <iostream>
#include <fstream>
#include <string.h>
#include <pthread.h>
#include "mkl.h"
#include <time.h>

using namespace std;

const int MAX_THREAD = 8;
int row = 0;
float** input_matrix_1;
float** input_matrix_2;
float** answer;
int l, m, n;


void printMatrix(float** matrix, int dim1, int dim2) {
	for (int i = 0; i < dim1; i++) {
		for (int j = 0; j < dim2; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void* multiply(void* arg) {
	while (true) {
		int i = row++;
		if (i < l) {
			for (int j = 0; j < n; j++) {
				answer[i][j] = 0;
				for (int k = 0; k < m; k++) {
					answer[i][j] += input_matrix_1[i][k]*input_matrix_2[k][j];
				}
			}
		} else {
			break;
		}	
	}
	
}

void pthread_multiply() {
	/*l = a;	m = b;	n = c;
	input_matrix_1 = A;
	input_matrix_2 = B;*/
	answer = new float*[l];
	for (int i = 0; i < l; i++) {
		answer[i] = new float[n];
	}
	clock_t t;
    t = clock();
	pthread_t threads[MAX_THREAD];
	for (int i = 0; i < MAX_THREAD; i++) {
		int* p;
		pthread_create(&threads[i], NULL, multiply, (void*)p);
	}

	for (int i = 0; i < MAX_THREAD; i++) {
		pthread_join(threads[i], NULL);
	}
	t = clock() - t;
	double time = (double)t/CLOCKS_PER_SEC;
	cout << "Time taken: " << time << endl;
	printMatrix(answer, l, n);
}

void mkl_multiply() {
	float *A, *B, *C;
	float alpha = 1, beta = 0;
	A = (float *)mkl_malloc( l*m*sizeof( float ), 64 );
    B = (float *)mkl_malloc( m*n*sizeof( float ), 64 );
    C = (float *)mkl_malloc( l*n*sizeof( float ), 64 );
    if (A == NULL || B == NULL || C == NULL) {
      printf( "\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
      mkl_free(A);
      mkl_free(B);
      mkl_free(C);
      return;
    }

    int index = 0;
    //printf ("Intializing matrix data \n");
    for (int i = 0; i < l; i++) {
    	for (int j = 0; j < m; j++) {
    		A[index++] = input_matrix_1[i][j];
    	}
    }
    index = 0;
    for (int i = 0; i < m; i++) {
    	for (int j = 0; j < n; j++) {
    		B[index++] = input_matrix_2[i][j];
    	}
    }

    for (int i = 0; i < (l*n); i++) {
        C[i] = 0.0;
    }

    printf ("\nComputing matrix product using Intel(R) MKL dgemm function via CBLAS interface \n");
    clock_t t;
    t = clock();
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                l, n, m, alpha, A, m, B, n, beta, C, n);



    t = clock() - t;
	double time = (double)t/CLOCKS_PER_SEC;
	cout << "Time taken: " << time << endl;

    answer = new float*[l];
	for (int i = 0; i < l; i++) {
		answer[i] = new float[n];
	}
    
    // for (int i = 0; i < l*n; i++) {
    // 	cout << C[i] << "\n";
    // }
    for (int i = 0; i < l*n; i++) {
    	int r = i/n;
    	int s = i%n;
    	answer[r][s] = C[i];
    }
    printMatrix(answer, l, n);
}

void cbas_multiply() {

}

int main(int argc, char** argv) {
	char* input_file_1 = argv[1];
	char* input_file_2 = argv[2];
	l = atoi(argv[3]);
	m = atoi(argv[4]);
	n = atoi(argv[5]);
	ifstream file_1, file_2;
	file_1.open(input_file_1);
	file_2.open(input_file_2);
	if (!file_1 || !file_2) {
		cerr << "Unable to open input matrix file" << endl;
		exit(1);
	} else {
		input_matrix_1 = new float*[l];
		input_matrix_2 = new float*[m];
		for (int i = 0; i < l; i++) {
			input_matrix_1[i] = new float[m];
		}

		for (int i = 0; i < m; i++) {
			input_matrix_2[i] = new float[n];
		}		

		float x;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < l; j++) {
				file_1 >> x;
				input_matrix_1[j][i] = x;
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				file_2 >> x;
				input_matrix_2[j][i] = x;
			}
		}
		file_1.close();
		file_2.close();
		printMatrix(input_matrix_1, l, m);
		cout << endl;
		printMatrix(input_matrix_2, m, n);
		cout << endl;

		pthread_multiply();
		
		mkl_multiply();
		
	}
}