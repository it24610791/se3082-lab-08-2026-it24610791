#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, message = 100;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("Rank 0: Sending to rank 1\n");
        MPI_Send(&message, 1, MPI_INT, 1, 10, MPI_COMM_WORLD);
    } else if (rank == 2) {
        printf("Rank 2: Waiting for a message from rank 0\n");
        MPI_Recv(&message, 1, MPI_INT, 0, 10,
                 MPI_COMM_WORLD, &status);
        printf("Rank 2: Received %d\n", message);
    }

    MPI_Finalize();
    return 0;
}
