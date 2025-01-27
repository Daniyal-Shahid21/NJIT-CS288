#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void countLinesInFile(const char *filePath, int *totalLines) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char buffer[1024];
    int lines = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        lines++;
    }

    fclose(file);
    *totalLines += lines;
}

void traverseDirectory(const char *dirPath, int *totalLines) {
    struct dirent *entry;
    struct stat entryStat;
    DIR *directory = opendir(dirPath);

    if (directory == NULL) {
        perror("Error opening directory");
        return;
    }

    while ((entry = readdir(directory)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        char fullPath[1000];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", dirPath, entry->d_name);

        if (stat(fullPath, &entryStat) == -1) {
            perror("Error getting file status");
            continue;
        }

        if (S_ISDIR(entryStat.st_mode)) {
            traverseDirectory(fullPath, totalLines);
        } 
        else if (S_ISREG(entryStat.st_mode) && strstr(entry->d_name, ".txt") != NULL) {
            countLinesInFile(fullPath, totalLines);
        }
    }
    closedir(directory);
}

int main() {
    char dirPath[1000];
    int totalLines = 0;

    printf("Enter the directory path: ");
    scanf("%999s", dirPath);

    traverseDirectory(dirPath, &totalLines);
    printf("Total number of lines in .txt files: %d\n", totalLines);

    return 0;
}