#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

