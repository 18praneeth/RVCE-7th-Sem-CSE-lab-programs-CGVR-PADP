#include<iostream>
#include<cmath>
#include<omp.h>

using namespace std;

inline int strike(bool comp[], int start, int step, int stop) {
	int i;
	for(i = start; i <= stop; i += step)
		comp[i] = true;
	return i;
}

int unfriendlySieve(int n) {
	int m = sqrt(n);
	bool* comp = new bool[n+1];
	for(int i = 0; i < n+1; i++)
		comp[i] = false;
	
	int count = 0;
	double t = omp_get_wtime();
	for(int i = 2; i <= m; i++) {
		if(!comp[i]) {
			count++;
			strike(comp, 2*i, i, n);
		}
	}
	for(int i = m+1; i <= n; i++) {
		if(!comp[i]) {
			count++;
		}
	}
	t = omp_get_wtime() - t;
	cout << "Time: " << t << endl;

	delete[] comp;
	return count;
}

int friendlySieve(int n) {
	int m = sqrt(n);
	bool* comp = new bool[n+1];
	for(int i = 2; i < n+1; i++)
		comp[i] = false;

	int *striker = new int[m];
	int *factor = new int[m];
	int fac_cnt = 0;
	
	int count = 0;
	double t = omp_get_wtime();
	for(int i = 2; i <= m; i++) {
		if(!comp[i]) {
			count++;
			factor[fac_cnt] = i;
			striker[fac_cnt] = strike(comp, 2*i, i, n);
			fac_cnt++;
		}
	}
	for(int left = m+1; left <= n; left += m) {
		int right = min(left+m-1, n);
		for(int k = 0; k < fac_cnt; k++) {
			striker[k] = strike(comp, striker[k], factor[k], right);
		}
		for(int i = left; i <= right; i++) {
			if(!comp[i]) {
				count++;
			}
		}
	}
	t = omp_get_wtime() - t;
	cout << "Time: " << t << endl;
	
	delete[] striker;
	delete[] factor;
	delete[] comp;
	return count;
}

int main() {
	cout << "Unfriendly " << unfriendlySieve(1000000) << endl;
	cout << "Friendly " << friendlySieve(1000000) << endl;
}