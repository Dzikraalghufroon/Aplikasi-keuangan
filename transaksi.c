#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"



void pencatatan_transaksi(bool pemasukan){

}

void menu_transaksi(){
    bool menu = true;
  int navigasi;
  while (menu) {
    clearScreen();

    header();

    printf("========================= MENU TRANSAKSI =========================");
    printf(" \n Pilih jenis Transaksi!");
    printf("     1. Pemasukan\n");
    printf("     2. Pengeluaran\n");
    printf("     0. Keluar\n");
    printf("==================================================================");
    printf("\n \tPilih menu (0-2): ");
    /*
          perulangan untuk navigasi 
      */
    while (true) {
      scanf(" %d", &navigasi);
      getchar();
      if (navigasi == 0) { // jika user input 0 maka program akan kembali ke menu utama
        menu = false;
        break;
      } else if (navigasi == 1) { // jika user input 1 maka program akan mengirim boolean true
                                  // sebagai parameter artinya pemasukan 
        pencatatan_transaksi(true);
        break;
      } else if (navigasi == 2) { // jika user input 2 maka program akan mengirim boolean false
                                  // sebagai parameter artinya pengeluaran
        pencatatan_transaksi(false);
        break;
      } else {
        printf("Mohon Pilih menu hanya (0-3): ");
      }
    }
  }
}