#include <stdio.h>

void analisis_kondisi_keuangan(char *kondisi, int saldo){
    if (saldo < 0) {
        kondisi = "Defisit";
    }
    else if (saldo == 0) {
        kondisi = "Seimbang";
    }
    else {
        kondisi = "surplus";
    }
}
