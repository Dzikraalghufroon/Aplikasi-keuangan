#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

void getId_transaksi(char *id) {
  FILE *fp = fopen("transaksi.txt", "r");
    char line[100];
    char id_terakhir[10] = "T000"; // default jika file kosong

    // Jika file tidak ditemukan 
    if (fp == NULL) {
        sprintf(id, "T001");
        return;
    }

    // Untuk membaca semua file sampai akhir
    while (fgets(line, sizeof(line), fp)) {
        // Ambil bagian id sebelum '|' untuk menghasilkan id baru
        sscanf(line, "%[^|]", id_terakhir);
    }
    fclose(fp);

    // Ambil angka di belakang huruf T
    int nomor;
    sscanf(id_terakhir + 1, "%d", &nomor);
    // artinya kita mengambil array 1 sampai seterusnya dan mengabaikan indeks ke 0
    nomor++; 

    // Bentuk ulang ID baru dengan format T001, T002, dst.
    sprintf(id, "T%03d", nomor);
}

void pencatatan_transaksi(bool pemasukan) {
  char kode_transaksi[10];
  clearScreen();
  header();
  getId_transaksi(kode_transaksi);
  printf(" %s", kode_transaksi);
  getchar();
}

void menu_transaksi() {
  if (file_kosong("data_transaksi.txt")) {
    FILE *BuatFile = fopen("data_transaksi.txt", "a");
    fclose(BuatFile);
  }
  bool menu = true;
  int navigasi;
  while (menu) {
    clearScreen();

    header();

    printf(
        "========================= MENU TRANSAKSI =========================");
    printf(" \n Pilih jenis Transaksi!");
    printf("     1. Pemasukan\n");
    printf("     2. Pengeluaran\n");
    printf("     0. Keluar\n");
    printf(
        "==================================================================");
    printf("\n \tPilih menu (0-2): ");
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
      } else if (navigasi ==
                 1) { // jika user input 1 maka program akan mengirim boolean
                      // true sebagai parameter artinya pemasukan
        pencatatan_transaksi(true);
        break;
      } else if (navigasi ==
                 2) { // jika user input 2 maka program akan mengirim boolean
                      // false sebagai parameter artinya pengeluaran
        pencatatan_transaksi(false);
        break;
      } else {
        printf("Mohon Pilih menu hanya (0-3): ");
      }
    }
  }
}