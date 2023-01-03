#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define BUFSIZE 32 

char *m[]={ "Hello", "RVCE", "CSE" };

int main(int argc, char **argv) {
	char msg[BUFSIZE];
	int root = 0, tag = 0;

	int rank, numProcs;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

	if(rank == 0) {
		for(int i = 1; i < numProcs; i++) {
			strcpy(msg, m[i-1]);
			MPI_Send(&msg, BUFSIZE, MPI_CHAR, i, tag, MPI_COMM_WORLD);
		}	
	} else {
		MPI_Status status;
		MPI_Recv(&msg, BUFSIZE, MPI_CHAR, root, tag, MPI_COMM_WORLD, &status);
		printf("Received %s in process of rank %d from process of rank %d\n", msg, root, rank);
	}
	MPI_Finalize();
}