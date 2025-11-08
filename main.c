#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

void tambah_pos_anggaran(bool message);
void edit_pos_anggaran();
void menu_utama();
void menu_pos_anggaran();
int main() {
  menu_utama();
  return 0;
}

void clearScreen() { printf("\033[2J\033[H"); }
void header() {
  printf("╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════╗\n");
  printf("║                                 APLIKASI KEUANGAN MAHASISWA        "
         "                              ║\n");
  printf("╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════╝\n");
}

void menu_utama() {
  FILE *fp = fopen("pos_anggaran.txt", "r");

  int validasi;

  bool menu = true;
  if (fp == NULL) {
    tambah_pos_anggaran(true);
  }

  int c = fgetc(fp);

  if (c == EOF) {
    fclose(fp);
    tambah_pos_anggaran(true);
  }

  fclose(fp);

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
    printf("\n \tPilih menu (0-4): ");
    /*
          perulangan untuk memvalidasi jawaban
      */
    while (true) {
      scanf(" %d", &validasi);
      getchar();
      if (validasi == 0) {
        printf("____________________");
        printf("\n|Program selesai.|\n");
        menu = false;
        break;
      } else if (validasi == 1) {
        menu_pos_anggaran();
        break;
      } else {
        printf("Mohon Pilih menu hanya (0-4): ");
      }
    }
  }
}
