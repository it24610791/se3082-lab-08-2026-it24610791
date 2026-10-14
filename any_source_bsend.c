#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, message;
    MPI_Status status;

    char buffer[MPI_BSEND_OVERHEAD + sizeof(int)];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0 || rank == 1) {
        message = 100 + rank;

        MPI_Buffer_attach(buffer, sizeof(buffer));

        MPI_Bsend(&message, 1, MPI_INT, 2, 10, MPI_COMM_WORLD);

        void *detached_buffer;
        int detached_size;
        MPI_Buffer_detach(&detached_buffer, &detached_size);

        printf("Rank %d buffered-sent %d to rank 2\n",
               rank, message);
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
