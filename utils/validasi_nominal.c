#include <stdbool.h>
#include <stdio.h>

bool validasi_nominal(long double nominal){
    if (nominal <= 0) {
    return false;
    }
    return true;
}

