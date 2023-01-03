#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SEED 3655942

int main(int argc, char **argv) {
	int rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double t;
	if(rank == 0) {
		t = MPI_Wtime();
	}

	int n = 10000, red_n;
	int count = 0, red_count;
	if(rank > 0) {
		srand(SEED);
		double x, y, z;
		for (int i = 0; i < n; i++) {
			x = (double)rand() / RAND_MAX;
			y = (double)rand() / RAND_MAX;
			z = x*x + y*y;
			if (z <= 1.0) count++;
		}
	}	
	MPI_Reduce(&count, &red_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&n, &red_n, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	red_n = red_n - n;

	if(rank == 0) {
		t = MPI_Wtime() - t;
		printf("time: %lf\n", t);

		double pi = (double)red_count / red_n * 4;
		printf("# of trials = %d, estimate of pi is %lf\n", red_n, pi);
	}	

	MPI_Finalize();
}