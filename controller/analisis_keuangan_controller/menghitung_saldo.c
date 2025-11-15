#include <stdio.h>
#include "analisis.h"


long double calculate_saldo() {
  long double income = pemasukan_total();
  long double spending = pengeluaran_total();
  return income - spending;
}




