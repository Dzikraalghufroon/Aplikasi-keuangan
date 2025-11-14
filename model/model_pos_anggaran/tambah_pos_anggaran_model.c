#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void tambah_pos_anggaran_model(char *nama_pos, long double nominal){
    FILE *fp = fopen("pos_anggaran.txt", "a");
      if (fp == NULL) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
      }
      fprintf(fp, "%s|%Lf\n", nama_pos, nominal);
      fclose(fp);

      printf("Data berhasil ditambahkan!\n");
}