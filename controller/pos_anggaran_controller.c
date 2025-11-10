#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../header.h"

void daftar_pos_anggaran_view(struct PosAnggaran arr[], int n);

bool cekPos_anggaran(char *data);

bool edit_pos_anggaran_model(char *namaCari);

bool hapus_pos_anggaran_model(char *namaCari);

void menu_pos_anggaran_view();

void tambah_pos_anggaran(bool message) {
    struct PosAnggaran data;

    bool mengisi = true;
    char lanjut;
    bool alert = false;
    bool sudah_ada = false;
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
      sudah_ada = cekPos_anggaran(data.pos);
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

// procedure untuk mengedit pos anggaran
void edit_pos_anggaran() {
    struct PosAnggaran data;
    char namaCari[50];
    bool success = false;
    struct PosAnggaran array_pos_anggaran[100];
    int panjangArray_posAnggaran = 0;
    int nomor = 1;

    clearScreen();
    header();

    // memanggil procedure getPos_anggaran untuk mendapatkan data dari file
    // pos_anggaran
    getPos_anggaran(array_pos_anggaran, &panjangArray_posAnggaran);


    //memanggil procedure untuk menampilkan pos anggaran
    daftar_pos_anggaran_view(array_pos_anggaran,panjangArray_posAnggaran);

    printf("Masukkan nama pos yang nominalnya ingin diubah: ");
    fgets(namaCari, sizeof(namaCari), stdin);
    namaCari[strcspn(namaCari, "\n")] = '\0';

    success = edit_pos_anggaran_model(namaCari);
    if (success) {
      printf("\nData berhasil diubah!\n");
    } else {
      printf("\nData tidak ditemukan!\n");
    }

    printf("Tekan Enter untuk kembali...");
    getchar();
    getchar();
}

// procedure untuk menghapus pos anggaran
void hapus_pos_anggaran() {

    char namaCari[50];
    bool success = false;
    struct PosAnggaran array_pos_anggaran[100];
    int panjangArray_posAnggaran = 0;
    int nomor = 1;

    clearScreen();
    header();
    // memanggil procedure getPos_anggaran untuk mendapatkan data dari file
    // pos_anggaran
    getPos_anggaran(array_pos_anggaran, &panjangArray_posAnggaran);


    //memanggil procedure untuk menampilkan pos anggaran
    daftar_pos_anggaran_view(array_pos_anggaran,panjangArray_posAnggaran);

    printf("Masukkan nama pos yang ingin dihapus: ");
    fgets(namaCari, sizeof(namaCari), stdin);
    namaCari[strcspn(namaCari, "\n")] = '\0';

    success = hapus_pos_anggaran_model(namaCari);
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

    menu_pos_anggaran_view();
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

