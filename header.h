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
};

bool file_kosong(const char *namaFile);

void getPos_anggaran(struct PosAnggaran *arr, int *jumlah);

void clearScreen(); 

void header();

#endif
