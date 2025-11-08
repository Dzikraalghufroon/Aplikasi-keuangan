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
} transaksi[100];


void clearScreen(); 

void header();

#endif
