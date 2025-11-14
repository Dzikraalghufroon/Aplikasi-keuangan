#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool hapus_pos_anggaran_model(char *namaCari){
    char nama_pos[50]; 
    long double nominal; 
    bool result = false;
    
    FILE *fp = fopen("pos_anggaran.txt", "r");
    FILE *DELETE = fopen("Temp_pos_anggaran.txt", "w");
    if (!fp || !DELETE) {
        printf("Gagal membuka file!\n");
        return false;
    }
    while (fscanf(fp, "%[^|]|%Lf\n", nama_pos, &nominal) == 2) {
        if (strcmp(nama_pos, namaCari) != 0) {
          result = true;
          fprintf(DELETE, "%s|%Lf\n", nama_pos, nominal);
        }
    }

    fclose(fp);
    fclose(DELETE);

    remove("pos_anggaran.txt");
    rename("Temp_pos_anggaran.txt", "pos_anggaran.txt");

    return result;
}