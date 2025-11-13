#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../../header.h"
#include "transaksi.h"


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
            pencatatan_transaksi_controller(true);
            break;
        } else if (navigasi ==
                    2) { // jika user input 2 maka program akan mengirim boolean
                        // false sebagai parameter artinya pengeluaran
            pencatatan_transaksi_controller(false);
            break;
        } else {
            printf("Mohon Pilih menu hanya (0-3): ");
        }
        }
    }
}