#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int opt;
    int c_flag = 0, d_flag = 0, u_flag = 0;
    char *f_arg = NULL;
    char *s_arg = NULL;

    while ((opt = getopt(argc, argv, "cduf:s:")) != -1){
        switch (opt){
            case 'c':
                c_flag = 1;
                printf("Option -c is set\n");
                break;
            case 'd':
                d_flag = 1;
                printf("Option -d is set\n");
                break;
            case 'u':
                u_flag = 1;
                printf("Option -u is set\n");
                break;
            case 'f':
                f_arg = optarg;
                printf("Option -f is set with argument: %s\n", f_arg);
                break;
            case 's':
                s_arg = optarg;
                printf("Option -s is set with argument: %s\n", s_arg);
                break;
            case '?':
                if (optopt == 'f' || optopt == 's'){
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                }
		else {
                    fprintf(stderr, "Unknown option: -%c\n", optopt);
                }
                return 1;
            default:
                fprintf(stderr, "Usage: %s [-c] [-d] [-u] [-f fields] [-s char] input_file output_file\n", argv[0]);
                return 1;
        }
    }
    if (optind < argc){
        printf("Remaining arguments:\n");
        for (int i = optind; i < argc; i++){
            printf("Argument: %s\n", argv[i]);
        }
    }
    return 0;
}
