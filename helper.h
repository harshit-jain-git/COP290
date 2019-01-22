void printMatrix(float** matrix, int dim1, int dim2);
void printVector(float* vector, int dim);
float** computeConv0(float** inputMatrix, float** squareKernel, int n, int p, int f);
float** computeConv1(float** inputMatrix, float** squareKernel, int n, int p, int f);
float** relu(float** inputMatrix, int n);
float** tanh(float** inputMatrix, int n);
float** avgpool(float** inputMatrix, int n,int f);
float** maxpool(float** inputMatrix, int n,int f);
float* sigmoid(float* inputVector,int n);
float* softmax(float* inputVector,int n);