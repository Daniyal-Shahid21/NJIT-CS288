#include <stdio.h>
#include <stdlib.h>

void testResultFile(int dim1) {
    FILE *outputFile = fopen("result.bin", "rb");
    if (!outputFile) {
        perror("Error opening result bin");
        exit(EXIT_FAILURE);
    }

    fread(&dim1, sizeof(int), 1, outputFile);
    long readResult[dim1][dim1][dim1];
    fread(readResult, sizeof(readResult), 1, outputFile);
    printf("Dimension is %d\n", dim1);

    for (int x = 0; x < dim1; x++) {
        for (int y = 0; y < dim1; y++) {
            for (int z = 0; z < dim1; z++) {
                printf("%ld\n", readResult[x][y][z]);
            }
        }
    }
    fclose(outputFile);
}

int main() {
    int dim1;
    int dim2;
    FILE *fileA;
    FILE *fileB;
    FILE *outputFile;

    fileA = fopen("matrix1.bin", "rb");
    fileB = fopen("matrix2.bin", "rb");

    if (!fileA || !fileB) {
        perror("Error opening binary files");
        exit(EXIT_FAILURE);
    }

    fread(&dim1, sizeof(int), 1, fileA);
    fread(&dim2, sizeof(int), 1, fileB);

    if (dim1 > 100) {
        fprintf(stderr, "Dimension cannot exceed 100\n");
        exit(EXIT_FAILURE);
    }
    else if (dim1 != dim2) {
        fprintf(stderr, "Matrices do not have equal dimensions\n");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Proceed\n");
    }

    int AMatrix[dim1][dim1][dim1];
    int BMatrix[dim1][dim1][dim1];
    long outputMatrix[dim1][dim1][dim1];

    fread(AMatrix, sizeof(AMatrix), 1, fileA);
    fread(BMatrix, sizeof(BMatrix), 1, fileB);

    fclose(fileA);
    fclose(fileB);

    outputFile = fopen("result.bin", "wb");
    if (!outputFile) {
        perror("Error opening result file");
        exit(EXIT_FAILURE);
    }

    fwrite(&dim1, sizeof(int), 1, outputFile);
    for (int x = 0; x < dim1; x++) {
        for (int y = 0; y < dim1; y++) {
            for (int z = 0; z < dim1; z++) {
                outputMatrix[x][y][z] = (long)AMatrix[x][y][z] * BMatrix[x][y][z];

                fwrite(&outputMatrix[x][y][z], sizeof(long), 1, outputFile);
                printf("%d * %d = %ld\n", AMatrix[x][y][z], BMatrix[x][y][z], outputMatrix[x][y][z]);
            }
        }
    }
    fclose(outputFile);

    // TESTING PURPOSES
    testResultFile(dim1);

    return 0;
}
