#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, message;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0 || rank == 1) {
        message = 100 + rank;
        MPI_Send(&message, 1, MPI_INT, 2, 10, MPI_COMM_WORLD);
        printf("Rank %d sent %d to rank 2\n", rank, message);
    } else if (rank == 2) {
        for (int i = 0; i < 2; i++) {
            MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, 10,
                     MPI_COMM_WORLD, &status);
            printf("Rank 2 received %d from rank %d\n",
                   message, status.MPI_SOURCE);
        }
    }

    MPI_Finalize();
    return 0;
}
