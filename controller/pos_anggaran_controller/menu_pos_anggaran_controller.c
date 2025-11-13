#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../../header.h"
#include "pos_anggaran.h"

void menu_pos_anggaran_controller() {
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
        tambah_pos_anggaran_controller(false);
        break;
      } else if (navigasi == 2) { // jika user input 2 maka program akan masuk
                                  // ke modul edit pos anggaran
        edit_pos_anggaran_controller();
        break;
      } else if (navigasi == 3) { // jika user input 3 maka program akan masuk
                                  // ke modul hapus pos anggaran
        hapus_pos_anggaran_controller();
        break;
      } else {
        printf("Mohon Pilih menu hanya (0-3): ");
      }
    }
  }
}

