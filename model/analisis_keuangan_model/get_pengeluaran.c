#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../header.h"

struct Transaksi* get_all_pengeluaran(int *jumlah) {
    char line[200];
    int kapasitas = 10; 
    *jumlah = 0;
    struct Transaksi *hasil = malloc(kapasitas * sizeof(struct Transaksi));
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

int get_amount_spending_data() {
    FILE *readFile = fopen("data_transaksi.txt", "r");
    if (!readFile) {
        printf("File data_transaksi.txt tidak ditemukan!\n");
        return 0;
    }
    char line[200];
    int jumlah = 0;
    while (fgets(line, sizeof(line), readFile)) {
        char jenis[50];
        if (sscanf(line, "%*49[^|]|%*49[^|]|%*49[^|]|%49[^|]|%*Lf|%*49[^\n]",jenis) == 1){
            if (strcmp(jenis, "Pengeluaran") == 0) {
                jumlah++;
            }
        }
    }
    fclose(readFile);
    return jumlah;
}

void get_data_pengeluaran(int *jumlah, struct Transaksi data_transaksi_pengeluaran[]) {
     FILE *readFile = fopen("data_transaksi.txt", "r");
    if (!readFile) {
        printf("File data_transaksi.txt tidak ditemukan!\n");
        return;
    }
    char line[200];
    *jumlah = 0;
    while (fgets(line, sizeof(line), readFile)) {
        char id[50], tanggal[50], pos[50], jenis[50], deskripsi[70];
        long double nominal;
        if (sscanf(line, "%49[^|]|%49[^|]|%49[^|]|%49[^|]|%Lf|%49[^\n]",id,tanggal,pos,jenis,&nominal,deskripsi) == 6){
            if (strcmp(jenis, "Pengeluaran") == 0) {
                strcpy(data_transaksi_pengeluaran[*jumlah].kode, id);
                strcpy(data_transaksi_pengeluaran[*jumlah].tanggal, tanggal);
                strcpy(data_transaksi_pengeluaran[*jumlah].pos, pos);
                strcpy(data_transaksi_pengeluaran[*jumlah].jenis, jenis);
                strcpy(data_transaksi_pengeluaran[*jumlah].keterangan, deskripsi);
                jumlah++;
            }
        }
    }
    fclose(readFile);
}

