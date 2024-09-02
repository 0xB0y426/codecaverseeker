#include <stdio.h>
#include <stdlib.h>

#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"

#define CAVE_SIZE 1024

int main(int argc, char *argv[]) {
    printf("CODE CAVE SEEKER \nWrited by R4idB0y\n \n");

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *arq = fopen(argv[1], "rb");
    if (!arq) {
        perror("Failed to open file");
        return 1;
    }

    unsigned char byte;
    long start = -1, length = 0;
    long pos = ftell(arq);

    while (fread(&byte, 1, 1, arq) == 1) {
        if (byte == 0x00) {
            if (start == -1) start = ftell(arq) - 1;  
            length++;
        } else {
            if (length >= CAVE_SIZE) 
                printf(BLUE"[+] Code Cave: 0x%ld-0x%ld\n"RESET, start, ftell(arq) - 2);  
            start = -1;
            length = 0;
        }
    }

    if (length >= CAVE_SIZE) 
        printf(BLUE"[+] Code Cave: 0x%ld-0x%ld\n"RESET, start, ftell(arq) - 1); 

    fclose(arq);  
    return 0;
}
