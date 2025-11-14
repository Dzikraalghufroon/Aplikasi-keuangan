#include <stdio.h>
#include <stdbool.h>

void set_transaksi(bool pemasukan, char *kode_transaksi,char * tanggal,char *pos,long double nominal,char *deskripsi){

    FILE *fwrite = fopen("data_transaksi.txt", "a");
    if (pemasukan) {
        //menyimpan dengan format (kode transaksi | tanggal | Pos Anggaran | Jenis | Nominal | Deskripsi)
        fprintf(fwrite, "%s|%s|%s|%s|%Lf|%s\n", kode_transaksi, tanggal,"Pemasukan","Pemasukan",nominal,deskripsi);
    }
    else {
        //menyimpan dengan format (kode transaksi | tanggal | Pos Anggaran | Jenis | Nominal | Deskripsi)
    fprintf(fwrite, "%s|%s|%s|%s|%Lf|%s\n", kode_transaksi, tanggal,pos,"Pengeluaran",nominal,deskripsi);
    }
    fclose(fwrite);
}