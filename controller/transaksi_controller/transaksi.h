#ifndef TRANSAKSI_H
#define TRANSAKSI_H


void input_pemasukan_view();

void daftar_pos_anggaran_view(struct PosAnggaran arr[], int n);

void getId_transaksi(char *id);

bool cekPosAnggaran(char *input);

void menu_transaksi_view();

void pencatatan_transaksi_controller(bool pemasukan);

#endif