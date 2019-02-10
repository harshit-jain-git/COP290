#include <iostream>
#include "helper.h"
#include <fstream>

#define N 28
#define CHANNELS_1 20
#define CHANNELS_2 20
#define CHANNELS_3 50
#define CHANNELS_4 50
#define CHANNELS_5 500
#define CHANNELS_6 10

#define M_1 5
#define M_2 2
#define M_3 4
#define M_4 1

using namespace std;

int main(int argc, char** argv) {
	ifstream file;
	file.open(argv[1]);
	float*** Input_image;
	Input_image = new float**[1];
	Input_image[0] = new float*[N];
	for (int i = 0; i < N; i++)
		Input_image[0][i] = new float[N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			float a;
			file >> a;
			a = 1.0 - a/255.0;
			Input_image[0][i][j] = a;	
		}
	}
	//printMatrix(Input_image[0], N, N);
	cout << "Entering Layer 1" << endl;

	// Layer 1
	float*** output_layer_1;
	int channels_1 = CHANNELS_1;

	float**** filter_1 = new float***[channels_1];
	float* bias_1 = new float[channels_1];
	int output_layer_1_size = N - M_1 + 1;
	int l = 1;

	ifstream filter_file;
	filter_file.open(argv[2]);
	for (int i = 0; i < channels_1; i++) {
		filter_1[i] = new float**[l];
		for (int j = 0; j < l; j++) {
			filter_1[i][j] = new float*[M_1];
			for (int k = 0; k < M_1; k++) {
				filter_1[i][j][k] = new float[M_1];
			}
		}
	}

	for (int i = 0; i < channels_1; i++) {
		for (int j = 0; j < l; j++) {
			for (int k = 0; k < M_1; k++) {
				for (int m = 0; m < M_1; m++) {
					filter_file >> filter_1[i][j][k][m];					
				}
			}
		}
	}

	// printMatrix(filter_1[19][0], M_1, M_1);
	for (int i = 0; i < channels_1; i++)
		if (filter_file.good()) filter_file >> bias_1[i];
		else {cout << "File error" << endl; break;}

	output_layer_1 = new float**[channels_1];
	for (int i = 0; i < channels_1; i++) {
		output_layer_1[i] = conv3d(Input_image, filter_1[i], N, 1, M_1, bias_1[i]);
		printMatrix(output_layer_1[i], output_layer_1_size, output_layer_1_size);
	}
	filter_file.close();

	cout << "Entering Layer 2" << endl;

	// Layer 2
	float*** output_layer_2;
	int channels_2 = CHANNELS_2;
	int output_layer_2_size = output_layer_1_size / 2;

	output_layer_2 = new float**[channels_2];
	for (int i = 0; i < channels_2; i++) {
		output_layer_2[i] = avgpool(output_layer_1[i], output_layer_1_size, M_2, 2);
		//printMatrix(output_layer_2[i], output_layer_2_size, output_layer_2_size);
	}

	cout << "Entering Layer 3" << endl;

	// Layer 3
	float*** output_layer_3;
	int channels_3 = CHANNELS_3;

	float**** filter_3 = new float***[channels_3];
	float* bias_3 = new float[channels_3];
	int output_layer_3_size = output_layer_2_size - M_1 + 1;
	l = 20;

	filter_file.open(argv[3]);
	for (int i = 0; i < channels_3; i++) {
		filter_3[i] = new float**[l];
		for (int j = 0; j < l; j++) {
			filter_3[i][j] = new float*[M_1];
			for (int k = 0; k < M_1; k++) {
				filter_3[i][j][k] = new float[M_1];
			}
		}
	}

	for (int i = 0; i < channels_3; i++) {
		for (int j = 0; j < l; j++) {
			for (int k = 0; k < M_1; k++) {
				for (int m = 0; m < M_1; m++) {
					filter_file >> filter_3[i][j][k][m];					
				}
			}
		}
	}

	for (int i = 0; i < channels_3; i++)
		if (filter_file.good()) filter_file >> bias_3[i];
		else {cout << "File error" << endl; break;}

	output_layer_3 = new float**[channels_3];
	for (int i = 0; i < channels_3; i++) {
		output_layer_3[i] = conv3d(output_layer_2, filter_3[i], output_layer_2_size, channels_2, M_1, bias_3[i]);
		//printMatrix(output_layer_3[i], output_layer_3_size, output_layer_3_size);
	}
	
	filter_file.close();

	cout << "Entering Layer 4" << endl;
	
	// Layer 4
	float*** output_layer_4;
	int channels_4 = CHANNELS_4;
	int output_layer_4_size = output_layer_3_size / 2;

	output_layer_4 = new float**[channels_4];
	for (int i = 0; i < channels_4; i++) {
		output_layer_4[i] = avgpool(output_layer_3[i], output_layer_3_size, M_2, 2);
		//printMatrix(output_layer_4[i], output_layer_4_size, output_layer_4_size);
	}

	cout << "Entering Layer 5" << endl;

	// Layer 5
	float*** output_layer_5;
	int channels_5 = CHANNELS_5;

	float**** filter_5 = new float***[channels_5];
	float* bias_5 = new float[channels_5];
	int output_layer_5_size = output_layer_4_size - M_3 + 1;
	l = 50;

	filter_file.open(argv[4]);
	for (int i = 0; i < channels_5; i++) {
		filter_5[i] = new float**[l];
		for (int j = 0; j < l; j++) {
			filter_5[i][j] = new float*[M_3];
			for (int k = 0; k < M_3; k++) {
				filter_5[i][j][k] = new float[M_3];
			}
		}
	}

	for (int i = 0; i < channels_5; i++) {
		for (int j = 0; j < l; j++) {
			for (int k = 0; k < M_3; k++) {
				for (int m = 0; m < M_3; m++) {
					filter_file >> filter_5[i][j][k][m];					
				}
			}
		}
	}

	for (int i = 0; i < channels_5; i++)
		if (filter_file.good()) filter_file >> bias_5[i];
		else {cout << "File error" << endl; break;}

	output_layer_5 = new float**[channels_5];
	for (int i = 0; i < channels_5; i++) {
		output_layer_5[i] = conv3d(output_layer_4, filter_5[i], output_layer_4_size, channels_4, M_3, bias_5[i]);
		output_layer_5[i] = relu(output_layer_5[i], output_layer_5_size);
		//printMatrix(output_layer_5[i], output_layer_5_size, output_layer_5_size);
	}

	filter_file.close();

	cout << "Entering Layer 6" << endl;

	// Layer 6
	float*** output_layer_6;
	int channels_6 = CHANNELS_6;

	float**** filter_6 = new float***[channels_6];
	float* bias_6 = new float[channels_6];
	int output_layer_6_size = output_layer_5_size - M_4 + 1;
	l = 500;

	filter_file.open(argv[5]);
	for (int i = 0; i < channels_6; i++) {
		filter_6[i] = new float**[l];
		for (int j = 0; j < l; j++) {
			filter_6[i][j] = new float*[M_4];
			for (int k = 0; k < M_4; k++) {
				filter_6[i][j][k] = new float[M_4];
			}
		}
	}

	for (int i = 0; i < channels_6; i++) {
		for (int j = 0; j < l; j++) {
			for (int k = 0; k < M_4; k++) {
				for (int m = 0; m < M_4; m++) {
					filter_file >> filter_6[i][j][k][m];					
				}
			}
		}
	}

	for (int i = 0; i < channels_6; i++)
		if (filter_file.good()) filter_file >> bias_6[i];
		else {cout << "File error" << endl; break;}

	output_layer_6 = new float**[channels_6];
	for (int i = 0; i < channels_6; i++) {
		output_layer_6[i] = conv3d(output_layer_5, filter_6[i], output_layer_6_size, channels_5, M_4, bias_6[i]);
		//printMatrix(output_layer_6[i], output_layer_6_size, output_layer_6_size);
	}

	float* output = new float[10];
	for (int i = 0; i < 10; i++)
		output[i] = output_layer_6[i][0][0];

	output = softmax(output, 10);

	filter_file.close();

	// Print the result
	for (int i = 0; i < 10; i++) {
		cout << "Probability of " << i << " : " << output[i] << endl;
	}

	free(output_layer_1);
	free(output_layer_2);
	free(output_layer_3);
	free(output_layer_4);
	free(output_layer_5);
	free(output_layer_6);

	return 0;
}