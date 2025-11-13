#include <stdio.h>
#include <stdbool.h>
#include "../utils/utils.h"
#include "../header.h"
#include "pos_anggaran_controller/pos_anggaran.h"

void menu_utama() {
  int navigasi;

  bool menu = true;

  //jika file yang menyimpan pos anggaran belum ada atau masih kosong
  if (file_kosong("pos_anggaran.txt")) {
    tambah_pos_anggaran_controller(true);
}

  while (menu) {
    clearScreen();

    header();

    printf(
        "=========================== MENU UTAMA ===========================");
    printf(" \n");
    printf("     1. Pencatatan Pos Anggaran\n");
    printf("     2. Pencatatan Transaksi\n");
    printf("     3. Perhitungan & Analisis Keuangan\n");
    printf("     4. Kesimpulan Kondisi Mahasiswa\n");
    printf("     5. Tampilkan laporan keuangan\n");
    printf("     0. Keluar\n");
    printf(
        "==================================================================");
    printf("\n \tPilih menu (0-5): ");
    /*
          perulangan untuk navigasi 
      */
    while (true) {
      scanf(" %d", &navigasi);
      getchar();
      if (navigasi == 0) {
        printf("____________________");
        printf("\n|Program selesai.|\n");
        menu = false;
        break;
      } else if (navigasi == 1) {
        menu_pos_anggaran_controller();
        break;
      }else if (navigasi == 2) {
        menu_transaksi();
        break;
      } else {
        printf("Mohon Pilih menu hanya (0-5): ");
      }
    }
  }
}
