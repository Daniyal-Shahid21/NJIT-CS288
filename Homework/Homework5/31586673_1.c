#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    unsigned char *p = (unsigned char *)&argv;
    printf("argv    | ");
    for (int i = 7; i >= 0; i--){
        printf("%02hhx ", *(p + i));
    }
    printf("| %p\n\n", (void *)&argv);

    for (int i = 0; i < argc; i++){
        p = (unsigned char *)&argv[i];
        printf("argv[%d] | ", i);
        for (int j = 7; j >= 0; j--) {
            printf("%02hhx ", *(p + j));
        }
        printf("| %p\n", (void *)&argv[i]);
    }
    printf("\n");

    unsigned char *start = (unsigned char *)argv[0];
    while ((unsigned long)start % 8 != 0) {
        start--;
    }

    unsigned char *end = (unsigned char *)argv[argc - 1];
    while (*end != '\0') {
        end++;
    }

    while ((unsigned long)(end + 1) % 8 != 0) {
        end++;
    }

    for (unsigned char *ptr = start; ptr <= end; ptr += 8){
        printf("| ");
        for (int i = 7; i >= 0; i--){
            if (ptr + i <= end) {
                unsigned char c = *(ptr + i);
                printf("%02hhx ", c);
                if (isprint(c)){
                    printf("(%c)", c);
                }
		else if (c == '\0') {
                    printf("(\\0)");
                }
		else {
                    printf("(.)");
                }
                printf(" ");
            }
	    else {
                printf("      ");
            }
        }
        printf("| %p\n", (void *)ptr);
    }
    return 0;
}
