#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../../header.h"
#include "analisis.h"

void rekap_pengeluaran(struct RekapPengeluaran *result,struct Transaksi *data, int *jumlah){
    bool found = false;
    int muncul = 0;
    long double nominal = 0;
    for (int i = 0; i< *jumlah; i++) {
        strcpy(result[i].pos , data[i].pos);
        result[i].nominal = get_nominal_pos(result[i].pos);
        result[i].realisasi = data[i].nominal;
        result[i].sisa = 0;
        result[i].jumlah_transaksi = 0;
    }
}
