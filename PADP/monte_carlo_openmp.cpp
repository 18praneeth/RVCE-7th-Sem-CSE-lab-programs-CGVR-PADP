#include <iostream>
#include <cstdlib>
#include <omp.h>

#define SEED 3655942

using namespace std;

int main() {
	int th;
	cout << "Enter the number of threads: ";
	cin >> th;
	omp_set_num_threads(th);

	double t = omp_get_wtime();

	int n = 10000;
	int count = 0;
	srand(SEED);
	#pragma omp parallel for reduction(+:count)
	for (int i = 0; i < n; i++) {
		double x = (double)rand() / RAND_MAX;
		double y = (double)rand() / RAND_MAX;
		double z = x*x + y*y;
		if (z <= 1.0) count++;
	}

	t = omp_get_wtime() - t;
	cout << "Time: " << t << endl;

	double pi = (double)count / n * 4;	
	cout << "no. of threads: " << th << endl;
	cout << "no. of trials: " << n << endl;
	cout << "est. of pi: " << pi << endl;
}
