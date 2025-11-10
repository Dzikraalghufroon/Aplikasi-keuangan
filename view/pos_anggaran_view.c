#include <stdio.h>
#include <stdbool.h>
#include "../header.h"

void menu_pos_anggaran_view(){
    printf("======================= MENU POS ANGGARAN =======================");
    printf(" \n");
    printf("     1. Tambah Pos Anggaran\n");
    printf("     2. Edit Pos Anggaran\n");
    printf("     3. Hapus Pos Anggaran\n");
    printf("     0. Keluar\n");
    printf(
        "==================================================================");
}

void daftar_pos_anggaran_view(struct PosAnggaran arr[], int n){
    printf("+------+--------------------------------+------------------+\n");
    printf("| No   | Pos Anggaran                   | Batas Nominal    |\n");
    printf("+------+--------------------------------+------------------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %-4d | %-30s | %16.2f |\n", i + 1, arr[i].pos, arr[i].batas_nominal);
    }
    printf("+------+--------------------------------+------------------+\n");

}