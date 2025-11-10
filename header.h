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

void clearScreen(); 

void header();

// model
bool posAda(const char *nama);
bool simpanPos(const struct PosAnggaran *data);
void getPos_anggaran(struct PosAnggaran arr[], int *jumlah);

// view
void tampilHeader();
void tampilDaftarPos(struct PosAnggaran arr[], int n);

// controller
void tambah_pos_anggaran(bool message);
void menu_pos_anggaran();

#endif
