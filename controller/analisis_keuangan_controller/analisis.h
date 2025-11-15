#ifndef ANALISIS_H
#define ANALISIS_H


struct Transaksi* get_all_pemasukan(int *jumlah);

struct Transaksi* get_all_pengeluaran(int *jumlah);

long double pemasukan_total();

long double pengeluaran_total();

long double calculate_saldo();

int get_amount_spending_data();

long double get_nominal_pos(const char *pos);
#endif