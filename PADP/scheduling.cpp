#include <iostream>
#include <cstdlib>
#include <gd.h>
#include <omp.h>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <file.png>" << endl;
		exit(1);
	}

	FILE *file = fopen(argv[1], "wb");

	double t = omp_get_wtime();

	int w = 1000;
	int h = 1000;
	gdImagePtr img = gdImageCreateTrueColor(w, h);

	#pragma omp parallel for num_threads(4) // schedule(static/dynamic/guided)
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			int color = 0xFF << omp_get_thread_num() * 8;
			#pragma omp critical
			gdImageSetPixel(img, x, y, color);
		}
	}

	gdImagePng(img, file);
	gdImageDestroy(img);

	fclose(file);

	t = omp_get_wtime() - t;
	cout << "Time: " << t << endl;
}
