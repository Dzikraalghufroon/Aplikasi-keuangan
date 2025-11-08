#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "header.h"

void getId_transaksi(char *id) {
    FILE *fp = fopen("data_transaksi.txt", "r");
    char line[100];
    char id_terakhir[10] = "T000"; // default jika file kosong

    // Jika file tidak ditemukan
    if (fp == NULL) {
        sprintf(id, "T001");
        return;
    }

    // Untuk membaca semua file sampai akhir agar bisa mendapatkan id terakhir
    while (fgets(line, sizeof(line), fp)) {
        // Ambil bagian id sebelum '|' untuk menghasilkan id baru
        line[strcspn(line, "\n")] = '\0'; // hapus newline
        sscanf(line, "%[^|]", id_terakhir); // ambil ID sebelum |
    }
    fclose(fp);

    // Ambil angka di belakang huruf T
    int nomor;
    sscanf(id_terakhir + 1, "%d", &nomor);
    // artinya kita mengambil array 1 sampai seterusnya dan mengabaikan indeks ke
    // 0
    nomor++;

    // Bentuk ulang ID baru dengan format T001, T002, dst.
    sprintf(id, "T%03d", nomor);
}

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


void pencatatan_transaksi(bool pemasukan) {
    FILE *fwrite = fopen("data_transaksi.txt", "a");

    struct PosAnggaran array_pos_anggaran[100];
    
    int panjangArray_posAnggaran = 0;
    char tanggal[11];
    char pos[20];
    time_t t = time(NULL);
    strftime(tanggal, sizeof(tanggal), "%d/%m/%Y", localtime(&t));
    float nominal;
    char deskripsi[50];

    //memanggil procedure getPos_anggaran untuk mendapatkan data dari file pos_anggaran
    getPos_anggaran(array_pos_anggaran, &panjangArray_posAnggaran);
    char kode_transaksi[10];
    clearScreen();
    header();
    printf("\n================= DAFTAR POS ANGGARAN ===================\n\n");
    printf("+------+--------------------------------+------------------+\n");
    printf("| No   | Pos Anggaran                   | Batas Nominal    |\n");
    printf("+------+--------------------------------+------------------+\n");

    //menampilkan seluruh data yang telah diambil dari procedure getPos_anggaran
    for (int i = 0; i < panjangArray_posAnggaran; i++) {
        printf("| %-4d | %-30s | %16.2f |\n", i + 1, array_pos_anggaran[i].pos,
            array_pos_anggaran[i].batas_nominal);
    }

    printf("+------+--------------------------------+------------------+\n");

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
    if (pemasukan) {
        //menyimpan dengan format (kode transaksi | tanggal | Pos Anggaran | Jenis | Nominal | Deskripsi)
        fprintf(fwrite, "%s|%s|%s|%s|%f|%s\n", kode_transaksi, tanggal,"Pemasukan","Pemasukan",nominal,deskripsi);
    }
    else {
        //menyimpan dengan format (kode transaksi | tanggal | Pos Anggaran | Jenis | Nominal | Deskripsi)
    fprintf(fwrite, "%s|%s|%s|%s|%f|%s\n", kode_transaksi, tanggal,pos,"Pengeluaran",nominal,deskripsi);
    }
    fclose(fwrite);
}

void menu_transaksi() {
    if (file_kosong("data_transaksi.txt")) {
        FILE *BuatFile = fopen("data_transaksi.txt", "a");
        fclose(BuatFile);
    }
    bool menu = true;
    int navigasi;
    while (menu) {
        clearScreen();

        header();

        printf(
            "========================= MENU TRANSAKSI =========================");
        printf(" \n Pilih jenis Transaksi!\n");
        printf("     1. Pemasukan\n");
        printf("     2. Pengeluaran\n");
        printf("     0. Keluar\n");
        printf(
            "==================================================================");
        printf("\n \tPilih menu (0-2): ");
        /*
            perulangan untuk navigasi
        */
        while (true) {
        scanf(" %d", &navigasi);
        getchar();
        if (navigasi ==
            0) { // jika user input 0 maka program akan kembali ke menu utama
            menu = false;
            break;
        } else if (navigasi ==
                    1) { // jika user input 1 maka program akan mengirim boolean
                        // true sebagai parameter artinya pemasukan
            pencatatan_transaksi(true);
            break;
        } else if (navigasi ==
                    2) { // jika user input 2 maka program akan mengirim boolean
                        // false sebagai parameter artinya pengeluaran
            pencatatan_transaksi(false);
            break;
        } else {
            printf("Mohon Pilih menu hanya (0-3): ");
        }
        }
    }
}