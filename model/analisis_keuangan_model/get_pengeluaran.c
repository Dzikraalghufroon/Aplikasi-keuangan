#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../header.h"

struct Transaksi* get_all_pengeluaran(int *jumlah) {
    char line[200];
    int kapasitas = 10; 
    *jumlah = 0;

    // Alokasi awal
    struct Transaksi *hasil = malloc(kapasitas * sizeof(struct Transaksi));
    if (!hasil) {
        printf("Gagal mengalokasikan memori!\n");
        return NULL;
    }

    FILE *readFile = fopen("data_transaksi.txt", "r");
    if (!readFile) {
        printf("File data_transaksi.txt tidak ditemukan!\n");
        free(hasil);
        return NULL;
    }

    while (fgets(line, sizeof(line), readFile)) {
        struct Transaksi dataTransaksi;

        if (sscanf(line, "%49[^|]|%49[^|]|%49[^|]|%49[^|]|%Lf|%49[^\n]",
                   dataTransaksi.kode,
                   dataTransaksi.tanggal,
                   dataTransaksi.pos,
                   dataTransaksi.jenis,
                   &dataTransaksi.nominal,
                   dataTransaksi.keterangan) == 6) {

            if (strcmp(dataTransaksi.jenis, "Pengeluaran") == 0) {
                // mengatur ulang jumlah array jika kapasitas habis
                if (*jumlah >= kapasitas) {
                    kapasitas *= 2;
                    struct Transaksi *tmp = realloc(hasil, kapasitas * sizeof(struct Transaksi));
                    if (!tmp) {
                        printf("Gagal memperbesar memori!\n");
                        free(hasil);
                        fclose(readFile);
                        return NULL;
                    }
                    hasil = tmp;
                }
                hasil[(*jumlah)++] = dataTransaksi;
            }
        }
    }

    fclose(readFile);
    return hasil;
}
