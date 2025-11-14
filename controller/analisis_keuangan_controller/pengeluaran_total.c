#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../../header.h"
#include "analisis.h"

/*modul untuk menjumlahkan total semua pengeluaran*/

long double pengeluaran_total(){
    int jumlah_data;
    long double total = 0;
    struct Transaksi *Pengeluaran = get_all_pengeluaran(&jumlah_data);
    if (Pengeluaran) {
        for (int i = 0; i < jumlah_data; i++) {
            total += Pengeluaran[i].nominal;
        }
// membebaskan memori di heap
        free(Pengeluaran);
    }

    return total;
}
