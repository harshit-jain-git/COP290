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

int main(int argc, char* argv) {
	ifstream file;
	file.open(argv[1]);
	int*** Input_image;
	Input_image = new int**[1];
	Input_image[0] = new int*[N];
	for (int i = 0; i < N; i++)
		Input_image[0][i] = new int[N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			file >> Input_image[0][j][i];	
		}
	}

	// Layer 1
	int*** output_layer_1;
	int channels_1 = CHANNELS_1;
	int*** filter_1 = new int*[channels_1];
	int* bias_1 = new int[channels_1];
	int output_layer_1_size = N - M_1 + 1;

	ifstream filter_file;
	filter_file.open(argv[2]);
	for (int i = 0; i < M_1; i++) {
		filter_1[i] = new int*[M_1];
		for (int j = 0; j < M_1; j++) {
			filter_1[i][j] = new int[M_1];
		}
	}

	output_layer_1 = new int**[channels_1];
	for (int i = 0; i < channels_1; i++) {
		for (int j = 0; j < M_1; j++) {
			for (int k = 0; k < M_1; k++) {
				filter_file >> filter_1[i][j][k];
			}
		}
	}

	for (int i = 0; i < channels_1; i++)
		filter_file >> bias_1[i];

	output_layer_1 = new int**[channels_1];
	for (int i = 0; i < channels_1; i++) {
		output_layer_1[i] = conv3d(Input_image, filter_1[i], N, 1, M_1, bias_1[i]);
	}
	filter_file.close();

	// Layer 2
	int*** output_layer_2;
	int channels_2 = CHANNELS_2;
	int output_layer_2_size = output_layer_1_size / 2;

	output_layer_2 = new int**[channels_2];
	for (int i = 0; i < channels_2; i++) {
		output_layer_2[i] = avgpool(output_layer_1[i], output_layer_1_size, M_2, 2);
	}

	// Layer 3
	int*** output_layer_3;
	int channels_3 = CHANNELS_3;

	int*** filter_3 = new int*[channels_3];
	int* bias_3 = new int[channels_3];
	int output_layer_3_size = output_layer_2_size - M_1 + 1;

	filter_file.open(argv[3]);
	for (int i = 0; i < M_1; i++) {
		filter_3[i] = new int*[M_1];
		for (int j = 0; j < M_1; j++) {
			filter_2[i][j] = new int[M_1];
		}
	}

	output_layer_3 = new int**[channels_3];
	for (int i = 0; i < channels_3; i++) {
		for (int j = 0; j < M_1; j++) {
			for (int k = 0; k < M_1; k++) {
				filter_file >> filter_3[i][j][k];
			}
		}
	}

	for (int i = 0; i < channels_3; i++)
		filter_file >> bias_3[i];

	output_layer_3 = new int**[channels_3];
	for (int i = 0; i < channels_1; i++) {
		output_layer_3[i] = conv3d(output_layer_2, filter_2[i], output_layer_3_size, channels_2, M_1, bias_3[i]);
	}
	
	filter_file.close();

	// Layer 4
	int*** output_layer_4;
	int channels_4 = CHANNELS_4;
	int output_layer_4_size = output_layer_3_size / 2;

	output_layer_4 = new int**[channels_4];
	for (int i = 0; i < channels_4; i++) {
		output_layer_4[i] = avgpool(output_layer_3[i], output_layer_3_size, M_2, 2);
	}

	// Layer 5
	int*** output_layer_5;
	int channels_5 = CHANNELS_5;

	int*** filter_5 = new int**[channels_5];
	int* bias_5 = new int[channels_5];
	int output_layer_5_size = output_layer_4_size - M_3 + 1;

	filter_file.open(argv[4]);
	for (int i = 0; i < M_3; i++) {
		filter_5[i] = new int*[M_3];
		for (int j = 0; j < M_3; j++) {
			filter_5[i][j] = new int[M_3];
		}
	}

	output_layer_5 = new int**[channels_5];
	for (int i = 0; i < channels_5; i++) {
		for (int j = 0; j < M_3; j++) {
			for (int k = 0; k < M_3; k++) {
				filter_file >> filter_5[i][j][k];
			}
		}
	}

	for (int i = 0; i < channels_5; i++)
		filter_file >> bias_5[i];

	output_layer_5 = new int**[channels_5];
	for (int i = 0; i < channels_5; i++) {
		output_layer_5[i] = relu(conv3d(output_layer_4, filter_5[i], output_layer_5_size, channels_4, M_3, bias_5[i]), output_layer_5_size);
	}

	filter_file.close();

	// Layer 6
	int*** output_layer_6;
	int channels_6 = CHANNELS_6;

	int*** filter_6 = new int**[channels_6];
	int* bias_6 = new int[channels_6];
	int output_layer_6_size = output_layer_5_size - M_4 + 1;

	filter_file.open(argv[5]);
	for (int i = 0; i < M_4; i++) {
		filter_5[i] = new int*[M_4];
		for (int j = 0; j < M_4; j++) {
			filter_5[i][j] = new int[M_3];
		}
	}

	output_layer_6 = new int**[channels_6];
	for (int i = 0; i < channels_6; i++) {
		for (int j = 0; j < M_4; j++) {
			for (int k = 0; k < M_4; k++) {
				filter_file >> filter_6[i][j][k];
			}
		}
	}

	for (int i = 0; i < channels_6; i++)
		filter_file >> bias_6[i];

	output_layer_6 = new int**[channels_6];
	for (int i = 0; i < channels_6; i++) {
		output_layer_6[i] = conv3d(output_layer_5, filter_6[i], output_layer_6_size, channels_5, M_4, bias_6[i]);
	}

	filter_file.close();

	// Print the result
	for (int i = 0; i < channels_6; i++) {
		cout >> "Probability of 0: " >> output_layer_6[i][0][0] >> endl;
	}
	
	free(output_layer_1);
	free(output_layer_2);
	free(output_layer_3);
	free(output_layer_4);
	free(output_layer_5);
	free(output_layer_6);

	return 0;
}