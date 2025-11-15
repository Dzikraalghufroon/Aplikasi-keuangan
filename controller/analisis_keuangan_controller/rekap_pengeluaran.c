#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../../header.h"
#include "analisis.h"

void rekap_pengeluaran(struct RekapPengeluaran *result,struct Transaksi *data,int jumlah){
    struct RekapPengeluaran temp[jumlah];
    // LANGKAH 1: Copy data ke temp
    for (int i = 0; i < jumlah; i++) {
        strcpy(temp[i].pos, data[i].pos);
        temp[i].nominal = get_nominal_pos(data[i].pos);  
        temp[i].realisasi = data[i].nominal;
        temp[i].jumlah_transaksi = 1;
        temp[i].sisa = 0;
    }
// Gabungkan POS yang sama result
    int count = 0; // jumlah POS unik
    for (int i = 0; i < jumlah; i++) {
        bool found = false;
        for (int j = 0; j < count; j++) {
            if (strcmp(result[j].pos, temp[i].pos) == 0) {
                // jika POS sama gabungkan
                result[j].realisasi += temp[i].realisasi;
                result[j].jumlah_transaksi += 1;
                found = true;
                break;
            }
        }
        if (!found) {// jika POS belum ada tambahkan ke result
            strcpy(result[count].pos, temp[i].pos);
            result[count].nominal = temp[i].nominal;
            result[count].realisasi = temp[i].realisasi;
            result[count].jumlah_transaksi = 1;
            count++;
        }
    }
    for (int i = 0; i < count; i++) {//menghitung sisa anggaran
        result[i].sisa = result[i].nominal - result[i].realisasi;
    }
}

