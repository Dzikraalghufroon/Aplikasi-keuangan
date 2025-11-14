#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool edit_pos_anggaran_model(char *namaCari){
    char nama_pos[50]; 
    long double nominal; 
    bool result = false;
    
    FILE *fp = fopen("pos_anggaran.txt", "r");
    FILE *EDIT = fopen("Temp_pos_anggaran.txt", "w");
    if (!fp || !EDIT) {
        printf("Gagal membuka file!\n");
        return false;
    }
    while (fscanf(fp, "%[^|]|%Lf\n", nama_pos, &nominal) == 2) {
      nama_pos[strcspn(nama_pos, "\n")] = '\0'; // hapus newline
        namaCari[strcspn(namaCari, "\n")] = '\0';
        // jika ditemukan data yang cocok maka data batas nominal yang sebelumnya
        // akan di ganti dengan yang baru
        if (strcmp(nama_pos, namaCari) == 0) {
            result = true;
            printf("Masukkan batas nominal baru: ");
            scanf("%Lf", &nominal);
            getchar();
        }
        // melakukan proses menulis ke sebuah file yang akan menampung data baru
        fprintf(EDIT, "%s|%Lf\n", nama_pos, nominal);
    }

    fclose(fp);
    fclose(EDIT);

    // menghapus file lama untuk diganti oleh file baru
    remove("pos_anggaran.txt");
    rename("Temp_pos_anggaran.txt", "pos_anggaran.txt");
    return result;
}
