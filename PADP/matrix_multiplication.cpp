#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

#define DIM 1000

int main() {
	int *A = new int[DIM * DIM];
	int *B = new int[DIM * DIM];
	int *C = new int[DIM * DIM];
	
	double t = omp_get_wtime();
	
	#pragma omp parallel for num_threads(8)
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			for (int k = 0; k < DIM; k++)
				// C[i][k] == C[DIM*i + k]
				C[DIM*i + k] += A[DIM*i + j] * B[DIM*j + k];

	t = omp_get_wtime() - t;
	printf("TIME: %lf", t);

	delete[] A;
	delete[] B;
	delete[] C;
}
