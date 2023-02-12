#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SEED 3655942

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	double t;
	if(rank == 0) {
		t = MPI_Wtime();
	}

	int n = 10000;
	int count = 0, red_count;
	srand(SEED);
	for (int i = 0; i < n / size; i++) {
		double x = (double)rand() / RAND_MAX;
		double y = (double)rand() / RAND_MAX;
		double z = x*x + y*y;
		if (z <= 1.0) count++;
	}
	MPI_Reduce(&count, &red_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank == 0) {
		t = MPI_Wtime() - t;
		printf("time: %lf\n", t);

		double pi = (double)red_count / n * 4;
		printf("# of trials = %d, estimate of pi is %lf\n", n, pi);
	}	

	MPI_Finalize();
}
