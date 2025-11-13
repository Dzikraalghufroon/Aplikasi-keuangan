#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../../header.h"
#include "pos_anggaran.h"

void edit_pos_anggaran_controller() {
    char namaCari[50];
    bool success = false;
    struct PosAnggaran array_pos_anggaran[100];
    int panjangArray_posAnggaran = 0;

    clearScreen();
    header();

    // memanggil procedure getPos_anggaran untuk mendapatkan data dari file
    // pos_anggaran
    getPos_anggaran(array_pos_anggaran, &panjangArray_posAnggaran);


    //memanggil procedure untuk menampilkan pos anggaran
    daftar_pos_anggaran_view(array_pos_anggaran,panjangArray_posAnggaran);

    printf("Masukkan nama pos yang nominalnya ingin diubah: ");
    fgets(namaCari, sizeof(namaCari), stdin);
    namaCari[strcspn(namaCari, "\n")] = '\0';

    success = edit_pos_anggaran_model(namaCari);
    if (success) {
      printf("\nData berhasil diubah!\n");
    } else {
      printf("\nData tidak ditemukan!\n");
    }

    printf("Tekan Enter untuk kembali...");
    getchar();
    getchar();
}
