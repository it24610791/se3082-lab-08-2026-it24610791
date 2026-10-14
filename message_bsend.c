#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, message = 100;
    int received;
    int buffer_size = MPI_BSEND_OVERHEAD + sizeof(int);
    char buffer[MPI_BSEND_OVERHEAD + sizeof(int)];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        MPI_Buffer_attach(buffer, buffer_size);

        printf("Rank 0: Buffered sending message %d\n", message);
        MPI_Bsend(&message, 1, MPI_INT, 1, 10, MPI_COMM_WORLD);

        void *detached_buffer;
        int detached_size;
        MPI_Buffer_detach(&detached_buffer, &detached_size);
    } else if (rank == 1) {
        MPI_Recv(&received, 1, MPI_INT, 0, 10,
                 MPI_COMM_WORLD, &status);
        printf("Rank 1: Received message %d\n", received);
    }

    MPI_Finalize();
    return 0;
}
