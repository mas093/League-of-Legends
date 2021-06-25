#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 500


int main()
{
	//Allocating the arrays on the heap to avoid stack overflows
	int i, j, k;
	int* A[N];
	int* B[N];
	int* C[N];

	for (i = 0; i < N; i++)
	{
		A[i] = (int*)malloc(N * sizeof(int));
		B[i] = (int*)malloc(N * sizeof(int));
		C[i] = (int*)malloc(N * sizeof(int));
	}

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			A[i][j] = rand() % 100;
			B[i][j] = rand() % 100;
		}
	

	//Multiply A and B, store it in C and report the time elapsed
	clock_t t;
	t = clock();
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			C[i][j] = 0;
			for (k = 0; k < N; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
	}
	t = clock() - t;

	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("%f\n", time_taken);

	for (i = 0; i < N; i++) {
		free(A[i]);
		free(B[i]);
		free(C[i]);
	}
	return 0;

}
