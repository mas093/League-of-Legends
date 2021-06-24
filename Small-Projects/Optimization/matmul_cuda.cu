#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cuda_runtime.h>
#include "kernel.h"
#include "kernel.cu"
#include "cu_array.h"
#include <math.h>

using namespace std;

int main()
{
	//Definitions
	int N = 500;
	int SIZE = N * N;

	//Allocate host memory
	vector<float> h_A;
	h_A.reserve(SIZE);
	vector<float> h_B;
	h_B.reserve(SIZE);
	vector<float> h_C;
	h_C.resize(SIZE);

	//Fill matrices
	for (int i = 0; i < N; i++) {
		for (int j = 0;j < N;j++)
		{
			h_A[i * N + j] = rand() % 100;
			h_B[i * N + j] = rand() % 100;
		}
	}

	//Allocate device memory
	cu_array<float> d_A(SIZE);
	cu_array<float> d_B(SIZE);
	cu_array<float> d_C(SIZE);

	d_A.set(&h_A[0], SIZE);
	d_B.set(&h_B[0], SIZE);



	//Measure elapsed time on the GPU (time.h is CPU)
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	cudaDeviceSynchronize();
	cudaEventRecord(start);
	
	matrixMultiplication(d_A.getData(), d_B.getData(), d_C.getData(), N);
	
	cudaDeviceSynchronize();
	cudaEventRecord(stop);
	cudaEventSynchronize(stop);

	float milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);

	//d_C.get(&h_C[0], SIZE); Copy back does not work for large N


	cout << milliseconds << "ms" << endl;
	return 0;
}