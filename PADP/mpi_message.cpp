#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define BUFSIZE 32 
#define TAG 0

char *m[]={ "Hello", "RVCE", "CSE" };

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank != 0) {
		char msg[BUFSIZE];
		strcpy(msg, m[rank-1]);
		MPI_Send(&msg, BUFSIZE, MPI_CHAR, rank, TAG, MPI_COMM_WORLD);
	} else {
		for(int i = 1; i < size; i++) {
			char msg[BUFSIZE];
			MPI_Recv(&msg, BUFSIZE, MPI_CHAR, i, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Received %s in process %d from process %d\n", msg, rank, i);
		}
	}

	MPI_Finalize();
}
