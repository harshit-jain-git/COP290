#include <iostream>
#include <fstream>
#include <string.h>
#include "helper.h"
#include "cblas_multiply.h"
#include "mkl_multiply.h"
#include "pthread_multiply.h"

using namespace std;


int main(int argc,char** argv) {
	if (argc < 2) {
		cerr << "Invalid usage!" << endl;
		cerr << "Refer to README file for correct usage." << endl;
		exit(1);
	}

	char* mode=argv[1];
	if (strcmp(mode, "conv0") == 0 || strcmp(mode, "conv1") == 0) {

		int padding_size;
		int input_matrix_size;
		int kernel_size;
		float** input_matrix;
		float** squareKernel;
		float** A;
		if (argc < 7) {
			cerr << "Input format error!" << endl;
			cerr << "Usage: ./all " << mode << " padding_size input_matrix_file input_matrix_size kernel_file kernel_matrix_size" << endl;
			exit(1);
		}
		padding_size = stoi(argv[2]);
		char* input_file = argv[3];
		input_matrix_size = stoi(argv[4]);
		char* kernel_file = argv[5];
		kernel_size = stoi(argv[6]);

		ifstream file;
		file.open(input_file);
		if (!file) {
			cerr << "Unable to open input matrix file" << endl;
			exit(1);
		} else {
			int n = input_matrix_size + 2*padding_size;
			input_matrix = new float*[n];
			for (int i = 0; i < n; i++) {
				input_matrix[i] = new float[n];
			}

			float x;
			for (int i = padding_size; i < input_matrix_size + padding_size; i++) {
				for (int j = padding_size; j < input_matrix_size + padding_size; j++) {
					file >> x;
					input_matrix[j][i] = x;
				}
			}
			file.close();
			printMatrix(input_matrix, n, n);
			cout << endl;
		}

		file.open(kernel_file);
		if (!file) {
			cerr << "Unable to open kernel matrix file" << endl;
			exit(1);
		} else {
			int n = kernel_size;
			squareKernel = new float*[n];
			for (int i = 0; i < n; i++) {
				squareKernel[i] = new float[n];
			}

			float x;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					file >> x;
					squareKernel[j][i] = x;
				}
			}
			file.close();
			printMatrix(squareKernel, n, n);
			cout << endl;
		}
		if(argc==8)
		{
			//row major teoplitz T
			int d=(input_matrix_size + 2*padding_size - kernel_size + 1);
			int f=kernel_size;

			float* T=rmteoplitz(input_matrix,input_matrix_size+2*padding_size,kernel_size);
			//flipped linearized kernel F
			float* F = flippedkernel(squareKernel, f);

			char* mode2=argv[7];
			//rm
			float* C=new float[d*d];
			if(strcmp(mode2,"mkl") == 0)
			{
				double t=mkl_multiply(T,F,C,d*d,f*f,1);
				print("C with mkl operation",C,d,d);
				cout<<"time taken in microseconds: "<< t << endl;
				return 0;
			}
			else if(strcmp(mode2,"openblas") == 0)
			{
				double t=cblas_multiply(T,F,C,d*d,f*f,1);
				print("C with openblas operation",C,d,d);
				cout<<"time taken in microseconds: "<< t << endl;
				return 0;
			}
			else if(strcmp(mode2,"pthread") == 0)
			{
				double t=pthread_multiply(T,F,C,d*d,f*f,1);
				print("C with pthreads operation",C,d,d);
				cout<<"time taken in microseconds: "<< t << endl;
				return 0;
			}
			else
			{
				cout<<"last argument has to be one of these: {'mkl','openblas','pthread'}"<<endl;
				return 0;
			}

		}
		else if (strcmp(mode, "conv0") == 0) {
			A = computeConv0(input_matrix, squareKernel, input_matrix_size, padding_size, kernel_size);
		} else {
			A = computeConv1(input_matrix, squareKernel, input_matrix_size, padding_size, kernel_size);
		}
		int dim = input_matrix_size + 2*padding_size - kernel_size + 1;
		printMatrix(A, dim, dim);

	} else if (strcmp(mode, "avgpool") == 0 || strcmp(mode, "maxpool") == 0) {
		int padding_size;
		int input_matrix_size;
		float** input_matrix;
		int filter_size;
		float** A;
		if (argc != 6) {
			cerr << "Input format error!" << endl;
			cerr << "Usage: ./all " << mode << " padding_size input_matrix_file input_matrix_size filter_size" << endl;
			exit(1);
		}
		padding_size = stoi(argv[2]);
		char* input_file = argv[3];
		input_matrix_size = stoi(argv[4]);
		filter_size = stoi(argv[5]);

		ifstream file;
		file.open(input_file);

		if (!file) {
			cerr << "Unable to open input matrix file" << endl;
			exit(1);
		} else {
			int n = input_matrix_size + 2*padding_size;
			input_matrix = new float*[n];
			for (int i = 0; i < n; i++) {
				input_matrix[i] = new float[n];
			}

			float x;
			for (int i = padding_size; i < input_matrix_size + padding_size; i++) {
				for (int j = padding_size; j < input_matrix_size + padding_size; j++) {
					file >> x;
					input_matrix[j][i] = x;
				}
			}
			file.close();
			if (strcmp(mode, "avgpool") == 0) {
				A = avgpool(input_matrix, n, filter_size,1);
			} else {
				A = maxpool(input_matrix, n, filter_size,1);
			}

			int dim = input_matrix_size + 2*padding_size - filter_size + 1;
			printMatrix(A, dim, dim);
		}
	} else if (strcmp(mode, "relu") == 0 || strcmp(mode, "tanh") == 0) {
		int input_matrix_size;
		float** input_matrix;
		float** A;
		if (argc != 4) {
			cerr << "Input format error!" << endl;
			cerr << "Usage: ./all " << mode << " input_matrix_file input_matrix_size" << endl;
			exit(1);
		}
		char* input_file = argv[2];
		input_matrix_size = stoi(argv[3]);

		ifstream file;
		file.open(input_file);

		if (!file) {
			cerr << "Unable to open input matrix file" << endl;
			exit(1);
		} else {
			int n = input_matrix_size;
			input_matrix = new float*[n];
			for (int i = 0; i < n; i++) {
				input_matrix[i] = new float[n];
			}

			float x;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					file >> x;
					input_matrix[j][i] = x;
				}
			}
			file.close();
			if (strcmp(mode, "relu") == 0) {
				A = relu(input_matrix, n);
			} else {
				A = tanh(input_matrix, n);
			}

			printMatrix(A, n, n);
		}
	} else if (strcmp(mode, "sigmoid") == 0 || strcmp(mode, "softmax") == 0) {
		float* input_vector;
		int input_vector_size;
		float* A;
		if (argc != 4) {
			cerr << "Input format error!" << endl;
			cerr << "Usage: ./all " << mode << " input_vector_file input_vector_size" << endl;
			exit(1);
		}

		char* input_file = argv[2];
		input_vector_size = stoi(argv[3]);

		ifstream file;
		file.open(input_file);

		if (!file) {
			cerr << "Unable to open input vector file" << endl;
			exit(1);
		} else {
			int n = input_vector_size;
			input_vector = new float[n];
			
			float x;
			for (int i = 0; i < n; i++) {
				file >> x;
				input_vector[i] = x;
			}

			file.close();
			if (strcmp(mode, "sigmoid") == 0) {
				A = sigmoid(input_vector, n);
			} else {
				A = softmax(input_vector, n);
			}
			printVector(A, n);
		}
	} else {
		cerr << "Invalid operation" << endl;
		cerr << "Use one of the following operations: conv0, conv1, avgpool, maxpool, relu, tanh, sigmoid, softmax" << endl;
		exit(1);
	}

	return 0;
}