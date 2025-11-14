#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../../header.h"
#include "transaksi.h"

/*
modul yang berisi sebuah menu untuk fitur transaksi untuk memeriksa apakah
user akan menginput pemasukan atau pengeluaran
*/

void menu_transaksi() {

  // memanggil fungsi file_kosong untuk memeriksa apakah file tidak ada
  if (file_kosong("data_transaksi.txt")) {
    FILE *BuatFile = fopen("data_transaksi.txt", "a");
    fclose(BuatFile);
  }
  bool menu = true;
  int navigasi;
  while (menu) {
    clearScreen();

    header();
    /*
        perulangan untuk navigasi
    */
    menu_transaksi_view();
    scanf(" %d", &navigasi);
    getchar();
    switch (navigasi) {
      // jika user input 0 maka program akan kembali ke menu utama
    case 0:
      menu = false;
      break;

      /* jika user input 1 maka program akan mengirim boolean*/
      /* true sebagai parameter artinya pemasukan*/
    case 1:
      pencatatan_transaksi_controller(true);
      break;

      /* jika user input 2 maka program akan mengirim boolean*/
      /* false sebagai parameter artinya pengeluaran*/
    case 2:
      pencatatan_transaksi_controller(false);
      break;

      /*Jika user menginput selain 0 - 2*/
    default:
      printf("Mohon Pilih menu hanya (0-2): ");
      break;
    }
  }
}