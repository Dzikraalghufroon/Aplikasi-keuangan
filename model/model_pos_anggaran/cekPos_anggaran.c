#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool cekPos_anggaran(char *data){
    FILE *cekFile = fopen("pos_anggaran.txt", "r");
      if (cekFile != NULL) {
        char line[100];
        char pos_existing[50];
        float batas_existing;

        while (fgets(line, sizeof(line), cekFile)) {
          // format file: namaPos|batasNominal
          if (sscanf(line, "%49[^|]|%f", pos_existing, &batas_existing) == 2) {
            if (strcmp(pos_existing, data) == 0) {
              return true;
              break;
            }
          }
        }
        fclose(cekFile);
      }

    return false;
}