#include <stdio.h>
#include <stdbool.h>
#include "../../header.h"


void daftar_pos_anggaran_view(struct PosAnggaran arr[], int n){
    printf("+------+--------------------------------+------------------+\n");
    printf("| No   | Pos Anggaran                   | Batas Nominal    |\n");
    printf("+------+--------------------------------+------------------+\n");
    for (int i = 0; i < n; i++) {
        printf("| %-4d | %-30s | %16.2Lf |\n", i + 1, arr[i].pos, arr[i].batas_nominal);
    }
    printf("+------+--------------------------------+------------------+\n");

}