#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#define N 500

double main(void)
{
	int i, j, k;
	int* A[N];
	int* B[N];
	int* C[N];
	int thread_num;
	double t, t1, t2;

	thread_num = omp_get_max_threads();

	//Build and compute
	#pragma omp parallel shared (A,B,C,t) private(i,j,k)
	{
		//Malloc arrays
		#pragma omp for
		for (i = 0; i < N; i++)
		{
			A[i] = (int*)malloc(N * sizeof(int));
			B[i] = (int*)malloc(N * sizeof(int));
			C[i] = (int*)malloc(N * sizeof(int));
		}

		//Fill A and B
		#pragma omp for
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				A[i][j] = rand() % 100;
				B[i][j] = rand() % 100;
			}
		}

		//Compute A * B
		t1 = omp_get_wtime();
		#pragma omp for
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				C[i][j] = 0;
				for (k = 0; k < N; k++)
				{
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		int th;
		t2 = omp_get_wtime() - t;

		#pragma omp for
		for (i = 0; i < N; i++) {
			free(A[i]);
			free(B[i]);
			free(C[i]);
		}
	}
	t = t2 - t1;
	printf("%f", t);
	return 0;	//This one is in seconds
}