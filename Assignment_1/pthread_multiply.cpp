#include <iostream>
#include <string.h>
#include <pthread.h>
#include <time.h>

using namespace std;

const int MAX_THREAD = 4;
int row = 0;
float* input_matrix_1;
float* input_matrix_2;
float* answer;
int rows1,rows2,col2,cnt;
void* multiply(void* arg) {
	while (cnt<rows1) {
		cnt++;
		for(int i=0;i<col2;i++)
		{
			answer[(cnt-1)*col2+i] = 0;
			for (int j = 0; j < rows2; j++) {
					answer[(cnt-1)*col2+i] += input_matrix_1[(cnt-1)*rows2+j]*input_matrix_2[j*(col2)+i];
			}
		}
	}
}

double pthread_multiply(float* A,float* B,float* C,int m,int l,int n)
{
	input_matrix_1 = A;
	input_matrix_2 = B;
	answer = C;
	rows1 = m;
	rows2 = l;
	col2 = n;
	cnt = 0;
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
	time = time*1000000;
	//cout << "Time taken in microseconds: " << time << endl;
	return time;
}
