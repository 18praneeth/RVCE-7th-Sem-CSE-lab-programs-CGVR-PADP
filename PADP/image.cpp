#include <stdio.h>
#include <gd.h>
#include <omp.h>

int main(int argc, char *argv[]) {
	if(argc != 3) {
		printf("Usage: %s input.png output.png\n", argv[0]);
		exit(0);
	}

	FILE *ifp = fopen(argv[1], "rb");
	if(ifp == NULL) {
		printf("Error - fopen(): %s", argv[1]);
		exit(0);
	}

	FILE *ofp = fopen(argv[2], "wb");
	if(ofp == NULL) {
		printf("Error - fopen(): %s", argv[2]);
		exit(0);
	}

	double t = omp_get_wtime();

	gdImagePtr img = gdImageCreateFromPng(ifp);
	int w = gdImageSX(img);
	int h = gdImageSY(img);

	#pragma omp parallel for
	for(int x = 0; x < w; x++) {
		for(int y = 0; y < h; y++) {
			int color = gdImageGetPixel(img, x, y);
			int avgColor = (gdImageRed(img, color) + gdImageGreen(img, color) + gdImageBlue(img, color)) / 3;
			color = gdImageColorAllocate(img, avgColor, avgColor, avgColor);
			#pragma omp critical
			gdImageSetPixel(img, x, y, color);
		}
	}

	gdImagePng(img, ofp);
	gdImageDestroy(img);

	fclose(ifp);
	fclose(ofp);

	t = omp_get_wtime() - t;
	printf("Time taken = %g\n",t);
}
