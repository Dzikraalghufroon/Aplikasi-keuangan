#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../../header.h"
#include "transaksi.h"


void pencatatan_transaksi_controller(bool pemasukan) {
    struct PosAnggaran array_pos_anggaran[100];
    
    int panjangArray_posAnggaran = 0;
    char tanggal[11];
    char pos[20];
    time_t t = time(NULL);
    strftime(tanggal, sizeof(tanggal), "%d/%m/%Y", localtime(&t));
    float nominal;
    char deskripsi[50];

    char kode_transaksi[10];
    clearScreen();
    header();
    // memanggil procedure getPos_anggaran untuk mendapatkan data dari file
    // pos_anggaran
    getPos_anggaran(array_pos_anggaran, &panjangArray_posAnggaran);

    //jika user ingin menginput Pengeluaran maka akan menampilkan tabel daftar pos anggaran
    if (!pemasukan) {
        daftar_pos_anggaran_view(array_pos_anggaran,panjangArray_posAnggaran);
    }
    else {// tampilan jika User ingin menginput Pemasukan
        input_pemasukan_view();
    }
    //inputan dari user untuk disimpan ke file
    
    if (!pemasukan) {
        while (true) {
            printf("Masukkan Pos Anggaran : ");
            fgets(pos, sizeof(pos), stdin);
            pos[strcspn(pos, "\n")] = '\0';

            if (cekPosAnggaran(pos)) { // valid
                break;
            } else {
                printf("\nPos Anggaran harus berasal dari data pos anggaran yang diinputkan\n");
            }
        }
    }

    while (true) {
        printf("\nMasukkan nominal : ");
        if (scanf(" %f", &nominal) == 1 && nominal > 0) {
            while (getchar() != '\n'); // buang sisa input
            break;
        } else {
            printf("Nominal harus bilangan positif (>0).\n");
            while (getchar() != '\n'); // buang input salah
        }
    }


    printf("Masukkan deskripsi : ");
    fgets(deskripsi, sizeof(deskripsi), stdin);
    deskripsi[strcspn(deskripsi, "\n")] = '\0'; 


    getId_transaksi(kode_transaksi);

    //menyimpan inputan transaksi dari user ke dalam file

    set_transaksi(pemasukan, kode_transaksi, tanggal,pos,nominal,deskripsi);

}

