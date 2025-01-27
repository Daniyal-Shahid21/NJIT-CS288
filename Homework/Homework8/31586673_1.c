#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VAL 999
#define BUCKET_SIZE (MAX_VAL + 1)

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int processID, numProcesses;
    MPI_Comm_rank(MPI_COMM_WORLD, &processID);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    if (argc != 2) {
        if (processID == 0) fprintf(stderr, "Usage: %s <binary file>\n", argv[0]);
        MPI_Finalize();
        return 0;
    }

    const char *filename = argv[1];
    int *values = NULL, totalNumbers = 0;

    if (processID == 0) {
        FILE *file = fopen(filename, "rb");
        fseek(file, 0, SEEK_END);
        totalNumbers = ftell(file) / sizeof(int);
        rewind(file);
        values = malloc(totalNumbers * sizeof(int));
        fread(values, sizeof(int), totalNumbers, file);
        fclose(file);
    }

    MPI_Bcast(&totalNumbers, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int chunk_size = (totalNumbers + numProcesses - 1) / numProcesses;
    int *localChunk = malloc(chunk_size * sizeof(int));
    MPI_Scatter(values, chunk_size, MPI_INT, localChunk, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    int *localCounts = calloc(BUCKET_SIZE, sizeof(int));
    for (int i = 0; i < chunk_size && (processID * chunk_size + i) < totalNumbers; i++) {
        localCounts[localChunk[i]]++;
    }

    int *globalCounts = NULL;
    if (processID == 0) globalCounts = calloc(BUCKET_SIZE, sizeof(int));
    MPI_Reduce(localCounts, globalCounts, BUCKET_SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (processID == 0) {
        int pos = 0;
        for (int i = 0; i < BUCKET_SIZE; i++) {
            for (int j = 0; j < globalCounts[i]; j++) {
                values[pos++] = i;
            }
        }
        FILE *file = fopen(filename, "wb");
        fwrite(values, sizeof(int), totalNumbers, file);
        fclose(file);
        free(globalCounts);
        free(values);
    }

    free(localChunk);
    free(localCounts);
    MPI_Finalize();
    return 1;
}
