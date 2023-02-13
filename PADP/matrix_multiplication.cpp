#include <iostream>
#include <omp.h>

#define DIM 1000

using namespace std;

int main() {
	int *A = new int[DIM * DIM];
	int *B = new int[DIM * DIM];
	int *C = new int[DIM * DIM];

	double t = omp_get_wtime();

	#pragma omp parallel for // num_threads(1/2/4/8)
	for (int i = 0; i < DIM; i++)
		for (int j = 0; j < DIM; j++)
			for (int k = 0; k < DIM; k++)
				// C[i][k] -> C[DIM*i + k]
				C[DIM*i + k] += A[DIM*i + j] * B[DIM*j + k];

	t = omp_get_wtime() - t;
	cout << "Time: " << t << endl;

	delete[] A;
	delete[] B;
	delete[] C;
}
