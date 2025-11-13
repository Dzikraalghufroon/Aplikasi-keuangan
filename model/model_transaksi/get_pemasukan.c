#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../../header.h"

struct Transaksi get_pemasukan() {
    struct Transaksi dataTransaksi;
    char line[200];

    FILE *readFile = fopen("data_transaksi.txt", "r");
    if (!readFile) {
        printf("File data_transaksi.txt tidak ditemukan!\n");
        return dataTransaksi; 
    }

    while (fgets(line, sizeof(line), readFile)) {
        // Format file: T001|08/11/2025|Makan|Pengeluaran|10000.000000|Makan siang
        if (sscanf(line, "%49[^|]|%49[^|]|%49[^|]|%49[^|]|%f|%49[^\n]",
                   dataTransaksi.kode,
                   dataTransaksi.tanggal,
                   dataTransaksi.pos,
                   dataTransaksi.jenis,
                   &dataTransaksi.nominal,
                   dataTransaksi.keterangan) == 6) {

            if (strcmp(dataTransaksi.jenis, "Pemasukan") == 0) {
                fclose(readFile);
                return dataTransaksi;
            }
        }
    }

    fclose(readFile);
    return dataTransaksi; 
}
