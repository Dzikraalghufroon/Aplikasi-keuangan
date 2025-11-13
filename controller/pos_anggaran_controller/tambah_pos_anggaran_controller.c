#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../../header.h"
#include "pos_anggaran.h"


void tambah_pos_anggaran_controller(bool message) {
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

      tambah_pos_anggaran_model(data.pos, data.batas_nominal);
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
