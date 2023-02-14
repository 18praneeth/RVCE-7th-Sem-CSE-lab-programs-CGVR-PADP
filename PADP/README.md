# Commands to Run Programs

OpenMP programs 

### 1st Program (Monte Carlo)
```
1a) g++ -fopenmp monte_carlo_openmp.cpp
    ./a.out
    g++ for CPP files, gcc for C files
1b) mpic++ monte_carlo_mpi.cpp
    mpirun -np 4 a.out

```

### 5th Program (MPI message Passing)
```
mpicc mpi_message.c -o prog
mpirun -np 4 prog

```
