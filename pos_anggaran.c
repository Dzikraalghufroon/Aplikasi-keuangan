#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

void tambah_pos_anggaran(bool message) {
    struct PosAnggaran data;

    bool mengisi = true;
    char lanjut;
    bool alert = false;
    /*
    *  perulangan untuk mengisi data pos anggaran
    */
    while (mengisi) {

      clearScreen(); // membersihkan layar
      header();
      if (message) {
        printf(
            "\tmohon tambahkan pos anggaran, karena data pos anggaran belum ada "
            "\n");
      }

      /*
          User melakukan input untuk nama pos
      */
      printf("\tMasukkan Nama pos: ");
      fgets(data.pos, sizeof(data.pos), stdin);
      data.pos[strcspn(data.pos, "\n")] = '\0'; // hapus newline

      /*
      *  Periksa apakah pos sudah ada di file
      */
      bool sudah_ada = false;
      FILE *cekFile = fopen("pos_anggaran.txt", "r");
      if (cekFile != NULL) {
        char line[100];
        char pos_existing[50];
        float batas_existing;

        while (fgets(line, sizeof(line), cekFile)) {
          // format file: namaPos|batasNominal
          if (sscanf(line, "%49[^|]|%f", pos_existing, &batas_existing) == 2) {
            if (strcmp(pos_existing, data.pos) == 0) {
              sudah_ada = true;
              break;
            }
          }
        }
        fclose(cekFile);
      }

      if (sudah_ada) {
        printf("Pos '%s' sudah ada di dalam file. Silakan masukkan nama lain.\n",
              data.pos);
        printf("Tekan ENTER untuk melanjutkan...");
        getchar();
        continue;
      }
      /*
      *  User melakukan input untuk batas anggaran
      */
      printf("\tMasukkan batas anggaran: ");
      scanf(" %f", &data.batas_nominal);
      getchar();
      if (data.batas_nominal <= 0) {
        printf("Anda menetapkan batas anggaran sebesar '%f', batas anggaran "
              "harus lebih besar dari nol.\n",
              data.batas_nominal);
        printf("Tekan ENTER untuk melanjutkan...");
        getchar();
        continue;
      }

      /*
      *menyimpan data ke dalam file pos_anggaran.txt
      */
      FILE *fp = fopen("pos_anggaran.txt", "a");
      if (fp == NULL) {
        printf("Gagal membuka file untuk menulis!\n");
        return;
      }
      fprintf(fp, "%s|%.2f\n", data.pos, data.batas_nominal);
      fclose(fp);

      printf("Data berhasil ditambahkan!\n");
      message = false;

      printf("==================================================================="
            "==================================================================="
            "===========\n");
      clearScreen(); // membersihkan layar

      /*
          perulangan untuk memvalidasi jawaban
      */
      while (true) {
        /*
      menanyakan kepada user apakah masih ingin menambah data atau sudah selesai
      */
        header();
        if (alert) {
          clearScreen();
          header();
          printf("\n mohon hanya menginput (y/n)\n");
        }
        printf("\tApakah anda masih ingin menambah pos anggaran? \n");
        printf("\tmasukkan (y) untuk tetap menambah \n\tmasukkan (n) jika "
              "selesai \n=");

        scanf(" %c", &lanjut);
        getchar(); // bersihkan buffer
        if (lanjut == 'n' || lanjut == 'N') {
          mengisi = false;
          break;
        } else if (lanjut == 'y' || lanjut == 'Y') {
          break;
        } else {
          alert = true;
        }
      }
    }
}
void edit_pos_anggaran() {
    FILE *fp = fopen("pos_anggaran.txt", "r");
    FILE *EDIT = fopen("Temp_pos_anggaran.txt", "w");
    struct PosAnggaran data;
    char namaCari[50];
    bool success = false;
    struct PosAnggaran array_pos_anggaran[100];
    int panjangArray_posAnggaran = 0;
    int nomor = 1;

    if (!fp || !EDIT) {
        printf("Gagal membuka file!\n");
        return;
    }

    clearScreen();
    header();
    printf("\n=== DAFTAR POS ANGGARAN ===\n\n");
    printf("+------+--------------------------------+------------------+\n");
    printf("| No   | Pos Anggaran                   | Batas Nominal    |\n");
    printf("+------+--------------------------------+------------------+\n");

    // memanggil procedure getPos_anggaran untuk mendapatkan data dari file
    // pos_anggaran
    getPos_anggaran(array_pos_anggaran, &panjangArray_posAnggaran);

    for (int i = 0; i < panjangArray_posAnggaran; i++) {
        printf("| %-4d | %-30s | %16.2f |\n", i + 1, array_pos_anggaran[i].pos,
            array_pos_anggaran[i].batas_nominal);
    }
    printf("+------+--------------------------------+------------------+\n");

    // Kembali ke awal file untuk proses edit
    rewind(fp);

    printf("Masukkan nama pos yang ingin diubah: ");
    fgets(namaCari, sizeof(namaCari), stdin);
    namaCari[strcspn(namaCari, "\n")] = '\0';

    // melakukan proses pengeditan
    while (fscanf(fp, "%[^|]|%f\n", data.pos, &data.batas_nominal) == 2) {
        // jika ditemukan data yang cocok maka data batas nominal yang sebelumnya
        // akan di ganti dengan yang baru
        if (strcmp(data.pos, namaCari) == 0) {
            success = true;
            printf("Masukkan batas nominal baru: ");
            scanf("%f", &data.batas_nominal);
        }
        // melakukan proses menulis ke sebuah file yang akan menampung data baru
        fprintf(EDIT, "%s|%.2f\n", data.pos, data.batas_nominal);
    }

    fclose(fp);
    fclose(EDIT);

    // menghapus file lama untuk diganti oleh file baru
    remove("pos_anggaran.txt");
    rename("Temp_pos_anggaran.txt", "pos_anggaran.txt");

    if (success) {
      printf("\nData berhasil diubah!\n");
    } else {
      printf("\nData tidak ditemukan!\n");
    }

    printf("Tekan Enter untuk kembali...");
    getchar();
    getchar();
}

void hapus_pos_anggaran() {
    FILE *fp = fopen("pos_anggaran.txt", "r");
    FILE *EDIT = fopen("Temp_pos_anggaran.txt", "w");
    struct PosAnggaran data;
    char namaCari[50];
    bool success = false;
    struct PosAnggaran array_pos_anggaran[100];
    int panjangArray_posAnggaran = 0;
    int nomor = 1;

    if (!fp || !EDIT) {
      printf("Gagal membuka file!\n");
      return;
    }

    clearScreen();
    header();
    printf("\n=== DAFTAR POS ANGGARAN ===\n\n");
    printf("+------+--------------------------------+------------------+\n");
    printf("| No   | Pos Anggaran                   | Batas Nominal    |\n");
    printf("+------+--------------------------------+------------------+\n");

    // memanggil procedure getPos_anggaran untuk mendapatkan data dari file
    // pos_anggaran
    getPos_anggaran(array_pos_anggaran, &panjangArray_posAnggaran);

    for (int i = 0; i < panjangArray_posAnggaran; i++) {
      printf("| %-4d | %-30s | %16.2f |\n", i + 1, array_pos_anggaran[i].pos,
            array_pos_anggaran[i].batas_nominal);
    }

    printf("+------+--------------------------------+------------------+\n");

    // Kembali ke awal file untuk proses edit
    rewind(fp);

    printf("Masukkan nama pos yang ingin dihapus: ");
    fgets(namaCari, sizeof(namaCari), stdin);
    namaCari[strcspn(namaCari, "\n")] = '\0';

    while (fscanf(fp, "%[^|]|%f\n", data.pos, &data.batas_nominal) == 2) {
        if (strcmp(data.pos, namaCari) != 0) {
          success = true;
          fprintf(EDIT, "%s|%.2f\n", data.pos, data.batas_nominal);
        }
    }

    fclose(fp);
    fclose(EDIT);

    remove("pos_anggaran.txt");
    rename("Temp_pos_anggaran.txt", "pos_anggaran.txt");

    if (success) {
        printf("\nData berhasil dihapus!\n");
    } else {
        printf("\nData gagal di hapus!\n");
    }

    printf("Tekan Enter untuk kembali...");
    getchar();
}

void menu_pos_anggaran() {
  bool menu = true;
  int navigasi;
  while (menu) {
    clearScreen();

    header();

    printf("======================= MENU POS ANGGARAN =======================");
    printf(" \n");
    printf("     1. Tambah Pos Anggaran\n");
    printf("     2. Edit Pos Anggaran\n");
    printf("     3. Hapus Pos Anggaran\n");
    printf("     0. Keluar\n");
    printf(
        "==================================================================");
    printf("\n \tPilih menu (0-3): ");
    /*
          perulangan untuk navigasi
      */
    while (true) {
      scanf(" %d", &navigasi);
      getchar();
      if (navigasi ==
          0) { // jika user input 0 maka program akan kembali ke menu utama
        menu = false;
        break;
      } else if (navigasi == 1) { // jika user input 1 maka program akan masuk
                                  // ke modul tambah pos anggaran
        tambah_pos_anggaran(false);
        break;
      } else if (navigasi == 2) { // jika user input 2 maka program akan masuk
                                  // ke modul edit pos anggaran
        edit_pos_anggaran();
        break;
      } else if (navigasi == 3) { // jika user input 3 maka program akan masuk
                                  // ke modul hapus pos anggaran
        hapus_pos_anggaran();
        break;
      } else {
        printf("Mohon Pilih menu hanya (0-3): ");
      }
    }
  }
}

/*
 * Menyimpan data yang ada di file pos anggaran ke dalam array
 */
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
