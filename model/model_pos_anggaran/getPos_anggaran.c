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