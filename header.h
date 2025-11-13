#ifndef HEADER_H
#define HEADER_H

struct PosAnggaran {
  char pos[50];
  float batas_nominal;
};
struct Transaksi {
    char kode[10];
    char jenis[20];
    char pos[50];
    float nominal;
    char tanggal[20];
    char keterangan[50];
};

bool file_kosong(const char *namaFile);

void getPos_anggaran(struct PosAnggaran *arr, int *jumlah);

void clearScreen(); 

void header();

void tambah_pos_anggaran_controller(bool message);

void menu_pos_anggaran_controller();

void menu_transaksi();

void menu_utama();

#endif
