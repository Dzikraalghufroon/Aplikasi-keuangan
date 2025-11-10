#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../../header.h"

bool cekPosAnggaran(char *input) {
    struct PosAnggaran array_pos_anggaran[100];
    int panjangArray_posAnggaran = 0;

    getPos_anggaran(array_pos_anggaran, &panjangArray_posAnggaran);

    for (int i = 0; i < panjangArray_posAnggaran; i++) {
        if (strcmp(array_pos_anggaran[i].pos, input) == 0) {
            return true; // input ditemukan
        }
    }
    return false; // input tidak ditemukan
}
