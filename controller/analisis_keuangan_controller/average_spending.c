#include <stdbool.h>
#include <stdio.h>
#include "analisis.h"

bool selection(long double params){
    if (params > 0) {
    return true;
    }
    return false;    
}

long double average_spending(){
   long double saldo= calculate_saldo();
   if (selection(saldo)) {
    return pengeluaran_total()/get_amount_spending_data();
   } 
    return 0;
}
