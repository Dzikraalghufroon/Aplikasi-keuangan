#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../../header.h"

void getPos_anggaran(struct PosAnggaran arr[], int *jumlah) {
  FILE *readFile = fopen("pos_anggaran.txt", "r");
  if (!readFile) {
    printf("File pos_anggaran.txt tidak ditemukan!\n");
    *jumlah = 0;
    return;
  }
  *jumlah = 0;
  while (fscanf(readFile, "%49[^|]|%Lf\n", arr[*jumlah].pos,
                &arr[*jumlah].batas_nominal) == 2) {
    (*jumlah)++;
  }

  fclose(readFile);
}

long double get_nominal_pos(const char *pos) {
    long double jumlah = 0;
    char nama[50];
    long double nominal;

    FILE *readFile = fopen("pos_anggaran.txt", "r");
    if (!readFile) {
        printf("File pos_anggaran.txt tidak ditemukan!\n");
        return 0;
    }

    while (fscanf(readFile, "%49[^|]|%Lf\n", nama, &nominal) == 2) {
        if (strcmp(nama, pos) == 0) {
            fclose(readFile);
            return nominal;  
        }
    }

    fclose(readFile);
    return 0;
}
