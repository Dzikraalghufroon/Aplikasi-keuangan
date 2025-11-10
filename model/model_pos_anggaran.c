#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../header.h"

void getPos_anggaran(struct PosAnggaran arr[], int *jumlah) {
  FILE *readFile = fopen("pos_anggaran.txt", "r");
  if (!readFile) {
    printf("File pos_anggaran.txt tidak ditemukan!\n");
    *jumlah = 0;
    return;
  }
  *jumlah = 0;
  while (fscanf(readFile, "%49[^|]|%f\n", arr[*jumlah].pos,
                &arr[*jumlah].batas_nominal) == 2) {
    (*jumlah)++;
  }

  fclose(readFile);
}
bool cekPos_anggaran(char *data){
    FILE *cekFile = fopen("pos_anggaran.txt", "r");
      if (cekFile != NULL) {
        char line[100];
        char pos_existing[50];
        float batas_existing;

        while (fgets(line, sizeof(line), cekFile)) {
          // format file: namaPos|batasNominal
          if (sscanf(line, "%49[^|]|%f", pos_existing, &batas_existing) == 2) {
            if (strcmp(pos_existing, data) == 0) {
              return true;
              break;
            }
          }
        }
        fclose(cekFile);
      }

    return false;
}

bool edit_pos_anggaran_model(char *namaCari){
    char nama_pos[50]; 
    float nominal; 
    bool result = false;
    
    FILE *fp = fopen("pos_anggaran.txt", "r");
    FILE *EDIT = fopen("Temp_pos_anggaran.txt", "w");
    if (!fp || !EDIT) {
        printf("Gagal membuka file!\n");
        return false;
    }
    while (fscanf(fp, "%[^|]|%f\n", nama_pos, &nominal) == 2) {
      nama_pos[strcspn(nama_pos, "\n")] = '\0'; // hapus newline
        namaCari[strcspn(namaCari, "\n")] = '\0';
        // jika ditemukan data yang cocok maka data batas nominal yang sebelumnya
        // akan di ganti dengan yang baru
        if (strcmp(nama_pos, namaCari) == 0) {
            result = true;
            printf("Masukkan batas nominal baru: ");
            scanf("%f", &nominal);
            getchar();
        }
        // melakukan proses menulis ke sebuah file yang akan menampung data baru
        fprintf(EDIT, "%s|%f\n", nama_pos, nominal);
    }

    fclose(fp);
    fclose(EDIT);

    // menghapus file lama untuk diganti oleh file baru
    remove("pos_anggaran.txt");
    rename("Temp_pos_anggaran.txt", "pos_anggaran.txt");
    return result;
}

bool hapus_pos_anggaran_model(char *namaCari){
    char nama_pos[50]; 
    float nominal; 
    bool result = false;
    
    FILE *fp = fopen("pos_anggaran.txt", "r");
    FILE *DELETE = fopen("Temp_pos_anggaran.txt", "w");
    if (!fp || !DELETE) {
        printf("Gagal membuka file!\n");
        return false;
    }
    while (fscanf(fp, "%[^|]|%f\n", nama_pos, &nominal) == 2) {
        if (strcmp(nama_pos, namaCari) != 0) {
          result = true;
          fprintf(DELETE, "%s|%.2f\n", nama_pos, nominal);
        }
    }

    fclose(fp);
    fclose(DELETE);

    remove("pos_anggaran.txt");
    rename("Temp_pos_anggaran.txt", "pos_anggaran.txt");

    return result;
}