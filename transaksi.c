#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"

void menu_transaksi(){
    bool menu = true;
  int navigasi;
  while (menu) {
    clearScreen();

    header();

    printf("========================= MENU TRANSAKSI =========================");
    printf(" \n Tambahkan Transaksi!");
    printf("     1. Tambah Pos Anggaran\n");
    printf("     2. Edit Pos Anggaran\n");
    printf("     0. Keluar\n");
    printf("==================================================================");
    printf("\n \tPilih menu (0-3): ");
    /*
          perulangan untuk navigasi 
      */
    while (true) {
      scanf(" %d", &navigasi);
      getchar();
      if (navigasi == 0) { // jika user input 0 maka program akan kembali ke menu utama
        menu = false;
        break;
      } else if (navigasi == 1) { // jika user input 1 maka program akan masuk
                                  // ke modul tambah pos anggaran
        break;
      } else if (navigasi == 2) { // jika user input 2 maka program akan masuk
                                  // ke modul edit pos anggaran
        break;
      } else {
        printf("Mohon Pilih menu hanya (0-3): ");
      }
    }
  }
}