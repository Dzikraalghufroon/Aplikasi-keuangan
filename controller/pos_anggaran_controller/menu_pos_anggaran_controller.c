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

    scanf("%d", &navigasi);
    getchar();

    switch (navigasi) {
    case 0:
        menu = false;
        break;

    case 1:
        tambah_pos_anggaran_controller(false);
        break;

    case 2:
        edit_pos_anggaran_controller();
        break;

    case 3:
        hapus_pos_anggaran_controller();
        break;

    default:
        printf("Mohon Pilih menu hanya (0-3)\n");
        getchar();
        break;
    }
}
}

