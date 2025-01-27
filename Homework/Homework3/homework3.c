#include <stdio.h>
#include <stdlib.h>
#define MAX 1000


int main(int argc, char* argv[]){
    if (argc != 3){
        exit(0);
    }

    FILE *file1 = fopen(argv[1], "rb");
    FILE *file2 = fopen(argv[2], "rb");
    FILE *resultbin = fopen("result.bin", "wb");
    int n1, n2;

    fread(&n1, sizeof(int), 1, file1);
    fread(&n2, sizeof(int), 1, file2);
    if ((n1 != n2) || n1 > MAX || n2 > MAX){
        exit(1);
    }
    
    int matrix1[n1][n1][n1], matrix2[n2][n2][n2], result[n1][n1][n1];

    fread(matrix1, sizeof(int), n1*n1*n1, file1);
    fread(matrix2, sizeof(int), n2*n2*n2, file1);

    for(int i = 0; i < n1; i++){
        for(int j = 0; j < n1; j++){
            for(int k = 0; k < n1; k++){
                result[i][j][k] = matrix1[i][j][k] * matrix2[i][j][k];
                printf("%d\n", result[i][j][k]);
            }
        }
    }

    fwrite(result, sizeof(int), n1*n1*n1, resultbin);

    fclose(file1);
    fclose(file2);
    fclose(resultbin);

    return 0;
}