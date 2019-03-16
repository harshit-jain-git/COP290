## Image Processing Library
### Compilation:
	Change the value of MKLROOT variable in makefile to your mkl library folder. 
	Open a terminal in the repo directory and type: make all

### Assumption:
	Stride = 1
	Input Matrix size = [nxn]
	Filter size = [fxf]
	Padding = p
	Input Vector size = n

#### Implemented Functions - 
**computeConv0**: Evaluates convolution of a square matrix with a given square kernel using normal convolution method.
*Output matrix dimensions*:  [(n + 2p - f + 1)x(n + 2p - f + 1)]  
*Usage:*	`./all conv0 padding_size input_matrix_file input_matrix_size kernel_file kernel_matrix_size`

**computeConv1**: Evalutes convolution of a square matrix with a given square kernel by multiplying the Teoplitz matrix and the flipped kernel.  
*Output matrix dimensions*:  [(n + 2p - f + 1)x(n + 2p - f + 1)]  
*Usage:*	`./all conv1 padding_size input_matrix_file input_matrix_size kernel_file kernel_matrix_size`

**relu**: Activates the input matrix using Rectified Linear Unit function.  
*Output matrix dimensions*:  [nxn]  
*Usage:*
	`./all relu input_matrix_file input_matrix_size`

**tanh**: Activates the input matrix using hyperbolic tan function.  
*Output matrix dimensions*:  [nxn]  
*Usage:*
	`./all tanh input_matrix_file input_matrix_size`

**maxpool**: Evaluates the maxpool matrix for a given input matrix. We assume the filter matrix to be a square matrix of dimensions [fxf].  
*Output matrix dimensions*:  [(n + 2p - f + 1)x(n + 2p - f + 1)]  
*Usage:* 
	`./all maxpool padding_size input_matrix_file input_matrix_size filter_size`

**avgpool**: Evaluates the avgpool matrix for a given input matrix. We assume the filter matrix to be a square matrix of dimensions [fxf].  
*Output matrix dimensions*:  [(n + 2p - f + 1)x(n + 2p - f + 1)]  
*Usage:*
	`./all avgpool padding_size input_matrix_file input_matrix_size filter_size`

**sigmoid**: Activates the input vector using sigmoid function.  
*Usage:*
	`./all sigmoid input_vector_file input_vector_size`

**softmax**: Activates the input vector using softmax function.  
*Usage:*
	`./all softmax input_vector_file input_vector_size`

**Available methods for Matrix multiplication: ['MKL', 'OpenBLAS', 'pthread']**  
*Usage*:
```
./all conv0 padding_size input_matrix_file input_matrix_size kernel_file kernel_matrix_size mkl
./all conv0 padding_size input_matrix_file input_matrix_size kernel_file kernel_matrix_size openblas
./all conv0 padding_size input_matrix_file input_matrix_size kernel_file kernel_matrix_size pthread
```

*For comparing matrix multiplication performance use:*
```
	 make performance
	 gnuplot plot.plt
```

![Latency Comparison plot](time_comparison.png)

### Implemented a CNN called LeNet using our own functions
    MNIST Input image: 28x28 pixels, grayscale so number of channels 1
 
    Conv_1:
    Input dimension N 28x28 
    Input channels 1
    Output channels 20, so number of filters 20 -- each filter will produce 1 output channel
    Kernel K = 5, so each filter is a 5x5 square
    Stride 1, padding 0, so output dimension (N-K+1) = 28-5+1 = 24
    Number of parameters = 20 (number of filters) * 5 * 5 (square kernel) * 1 (input channels) + 20 (bias terms, one for each filter) = 20 * 26 = 520.
    File conv1.txt has 520 values, last 20 being the bias values. 
    
    Pool_1:
    Input dimension N = 24x24
    Input channels 20
    Pooling with kernel K = 2, stride 2, so output is 12x12
    Output channel 20
    Max pooling, so no weights 
    
    Conv_2:
    Input dimension N 12x12
    Input channels 20
    Output channels 50, so number of filters 50 -- each filter will produce 1 output channel
    Kernel K = 5, so each filter is a 5x5 square
    Stride 1, padding 0, so output dimension (N-K+1) = 12-5+1 = 8
    Number of parameters = 50 (number of filters) * 5 * 5 (square kernel) * 20 (input channels) + 50 (bias terms, one for each filter) = 50 * 501 = 25050.
    File conv2.txt has 25050 values, last 50 being the bias values. 
    
    Pool_2:
    Input dimension N = 8x8
    Input channels 50
    Pooling with kernel K = 2, stride 2, so output is 4x4
    Output channel 50
    Max pooling, so no weights 
    
    FC_1:
    Input dimension N 4x4
    Input channels 50
    Output channels 500, so number of filters 500 -- each filter will produce 1 output channel
    Kernel K = 4, so each filter is a 4x4 square
    Stride 1, padding 0, so output dimension (N-K+1) = 4-4+1 = 1
    Number of parameters = 500 (number of filters) * 4 * 4 (square kernel) * 50 (input channels) + 500 (bias terms, one for each filter) = 500 * 801 = 400500.
    File fc1.txt has 400500 values, last 500 being the bias values.
    Has a relu layer.
     
    FC_2:
    Input dimension N 1x1
    Input channels 500
    Output channels 10, so number of filters 10 -- each filter will produce 1 output channel
    Kernel K = 1, so each filter is a 1x1 square
    Stride 1, padding 0, so output size (N-K+1) = 1-1+1 = 1
    Number of parameters = 10 (number of filters) * 1 * 1 (square kernel) * 500 (input channels) + 10 (bias terms, one for each filter) = 10 * 501 = 5010.
    File fc2.txt has 5010 values, last 10 being the bias values.
    
#### Compilation:
	Open a terminal in the repo directory and type: make lenet
**Note:**
    Preprocess the Image first before feeding to CNN.
##### Preprocessing:
    python preprocess.py image.png
    It will create a data.txt file after processing image.png
#### Usage:
    ./lenet data.txt conv1.txt conv2.txt fc1.txt fc2.txt
It will output top 5 digits with highest softmax probabilities

