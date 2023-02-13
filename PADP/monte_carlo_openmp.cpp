#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SEED 3655942

int main() {
	int th;
	printf("Enter the number of threads to be used to estimate pi: ");
	scanf("%d", &th);	
	omp_set_num_threads(th);

	double t = omp_get_wtime();

	int n = 10000;
	int count = 0;
	srand(SEED);
	#pragma omp parallel for reduction( +: count)
	for (int i = 0; i < n; i++) {
		double x = (double)rand() / RAND_MAX;
		double y = (double)rand() / RAND_MAX;
		double z = x*x + y*y;
		if (z <= 1.0) count++;
	}

	t = omp_get_wtime() - t;
	printf("time: %lf\n", t);

	double pi = (double)count / n * 4;	
	printf("# of trials = %d, estimate of pi is %lf, # of threads = %d \n", n, pi, th);
}
