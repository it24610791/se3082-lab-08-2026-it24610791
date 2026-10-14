#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    long long n = 10000000LL;
    long long local_sum = 0;
    long long total_sum = 0;
    long long start, end;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start_time = MPI_Wtime();

    long long chunk = n / size;
    start = rank * chunk + 1;
    end = (rank == size - 1) ? n : (rank + 1) * chunk;

    for (long long i = start; i <= end; i++) {
        local_sum += i;
    }

    MPI_Reduce(&local_sum, &total_sum, 1,
               MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double elapsed = MPI_Wtime() - start_time;

    if (rank == 0) {
        printf("Processes: %d\n", size);
        printf("Sum: %lld\n", total_sum);
        printf("Execution time: %.6f seconds\n", elapsed);
    }

    MPI_Finalize();
    return 0;
}
