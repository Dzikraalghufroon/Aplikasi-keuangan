#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../../header.h"
#include "analisis.h"

/*modul untuk menjumlahkan total semua pemasukan*/
long double pemasukan_total(){
    int jumlah_data;
    long double total = 0;
    struct Transaksi *Pemasukan = get_all_pemasukan(&jumlah_data);
    if (Pemasukan) {
        for (int i = 0; i < jumlah_data; i++) {
            total += Pemasukan[i].nominal;
        }
// membebaskan memori di heap
        free(Pemasukan);
    }

    return total;
}
