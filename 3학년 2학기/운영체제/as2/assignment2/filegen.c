#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

#define MAX_PROCESS 30000

int main(void) {
    char num[100];
    mkdir("temp", 0777);
    DIR *dir = opendir("temp");
    for (int i=0; i<MAX_PROCESS; i++) {
        char file_name[10000] = {'t','e','m','p','/','\0'};
        sprintf(num, "%d", i);
        FILE *f_write = fopen(strcat(file_name, num), "w+");
        fprintf(f_write, "%d", 1+rand()%9);
        fclose(f_write);
    }
    closedir(dir);
}