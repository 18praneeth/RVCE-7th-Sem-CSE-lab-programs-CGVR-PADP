#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define SIZE 4
#define BUFSIZE 32

#define ROOT 0
#define TAG 0

char* m[SIZE] = { "", "Hello", "RVCE", "CSE" };
char msg[BUFSIZE];

int main(int argc, char *argv[]) {
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (size != SIZE) {
		printf("Provide argument: -np %d\n", SIZE);
		exit(1);
	}

	if (rank != ROOT) {
		strcpy(msg, m[rank]);
		MPI_Send(&msg, BUFSIZE, MPI_CHAR, ROOT, TAG, MPI_COMM_WORLD);
	} else {
		for(int i = 0; i < size; i++) {
			if (i == ROOT) continue;
			MPI_Recv(&msg, BUFSIZE, MPI_CHAR, i, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Received %s in process %d from process %d\n", msg, rank, i);
		}
	}

	MPI_Finalize();
}
