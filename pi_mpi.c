#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define TOTAL_POINTS 10000000LL

int main(int argc, char *argv[]) {
    int rank, size;
    long long local_inside = 0;
    long long total_inside = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long points = TOTAL_POINTS / size;
    if (rank == size - 1) {
        points += TOTAL_POINTS % size;
    }

    unsigned int seed = 12345u + (unsigned int)rank;
    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    for (long long i = 0; i < points; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;

        if (x * x + y * y <= 1.0) {
            local_inside++;
        }
    }

    MPI_Reduce(&local_inside, &total_inside, 1,
               MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double local_time = MPI_Wtime() - start_time;
    double max_time;

    MPI_Reduce(&local_time, &max_time, 1,
               MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double pi = 4.0 * (double)total_inside / TOTAL_POINTS;
        printf("Processes: %d\n", size);
        printf("Points: %lld\n", TOTAL_POINTS);
        printf("Estimated Pi: %.10f\n", pi);
        printf("Execution time: %.6f seconds\n", max_time);
    }

    MPI_Finalize();
    return 0;
}
