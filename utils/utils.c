#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

bool file_kosong(const char *namaFile) {
    // strcat( "storage/",namaFile);
    FILE *fp = fopen(namaFile, "r");
    if (!fp) return true;
    int c = fgetc(fp);
    fclose(fp);
    return (c == EOF);
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
