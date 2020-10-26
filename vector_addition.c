// Given two vectors of N dimension output the vector sum.

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MASTER 0
#define MAX 1000010


void add(int *a, int *b, int len, int *sum) {
    int i;
    for (i = 0; i < len; i++) {
        sum[i] = a[i] + b[i];
    }
}

int a[MAX], b[MAX], sum[MAX], res[MAX];
int ac[MAX], bc[MAX];

int main(int argc, char *argv[]) 
{

    int T, N;
    int partial_length;
    int i;

    int rank, total_processes;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processes); // counting the total number of processes running
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // the rank of current process

    if (rank == MASTER) 
        scanf("%d", &T);
    MPI_Bcast(&T, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
    while (T-- > 0) 
    {
        if (rank == MASTER) 
        {
            scanf("%d", &N);
            partial_length = N / total_processes;
            if (N % total_processes > 0) 
                partial_length=partial_length+1;
            for (i = 0; i < N; i++)
                scanf("%d", &a[i]);
            for (i = 0; i < N; i++)
                scanf("%d", &b[i]);
        }
        MPI_Bcast(&N, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
        MPI_Bcast(&partial_length, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
        MPI_Scatter(a, partial_length, MPI_INT, ac, partial_length, MPI_INT, MASTER, MPI_COMM_WORLD);
        MPI_Scatter(b, partial_length, MPI_INT, bc, partial_length, MPI_INT, MASTER, MPI_COMM_WORLD);
        add(ac, bc, partial_length, sum);
        MPI_Gather(sum, partial_length, MPI_INT, res, partial_length, MPI_INT, MASTER, MPI_COMM_WORLD);
        if (rank == MASTER) 
        {
            for (i = 0; i < N; i++)
                printf("%d ", res[i]);
            printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}
