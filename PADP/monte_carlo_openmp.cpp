#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SEED 3655942

int main() {
	int th;
	printf("Enter the number of threads to be used to estimate pi: ");
	scanf("%d", &th);	
	omp_set_num_threads(th);

	int n;
	printf("Enter the number of iterations to be used to estimate pi: ");
	scanf("%d", &n);

	double t = omp_get_wtime();

	srand(SEED);
	int count = 0;
	double x, y, z;
	#pragma omp parallel for private(x,y,z) reduction( +: count)
	for (int i = 0; i < n; i++) {
		x = (double)rand() / RAND_MAX;
		y = (double)rand() / RAND_MAX;
		z = x*x + y*y;
		if (z <= 1.0) count++;
	}

	t = omp_get_wtime() - t;
	printf("time: %lf\n", t);

	double pi = (double)count / n * 4;	
	printf("# of trials = %d, estimate of pi is %lf, # of threads = %d \n", n, pi, th);
}