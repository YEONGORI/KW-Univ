#define MAX_PROCESSES 64

#include <stdio.h>

int main(void) {
    FILE *f_write = fopen("temp.txt", "r+");

    for (int i=0; i<MAX_PROCESSES*2; i++) {
        fprintf(f_write, "%d", i+1);
        fprintf(f_write, "\n");
    };

    fclose(f_write);
}