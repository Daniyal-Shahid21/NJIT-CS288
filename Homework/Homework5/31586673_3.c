#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_env(char *envp[]){
    for (int i = 0; envp[i] != NULL; i++){
        printf("%s\n", envp[i]);
    }
}

int main(int argc, char *argv[], char *envp[]) {
    int i, j;
    char *nameA, *nameB;

    int count = 0;
    while (envp[count] != NULL){
        count++;
    }

    for (i = 0; i < count - 1; i++){
        for (j = 0; j < count - i - 1; j++){
            char *envA = strdup(envp[j]);
            char *envB = strdup(envp[j + 1]);

            nameA = strtok(envA, "=");
            nameB = strtok(envB, "=");

            if (strcmp(nameA, nameB) > 0) {
                char *temp = envp[j];
                envp[j] = envp[j + 1];
                envp[j + 1] = temp;
            }
            free(envA);
            free(envB);
        }
    }

    printf("Sorted Environment Variables:\n");
    print_env(envp);

    return 0;
}
