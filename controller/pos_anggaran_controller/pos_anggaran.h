#ifndef POS_ANGGARAN
#define POS_ANGGARAN

void daftar_pos_anggaran_view(struct PosAnggaran arr[], int n);

bool cekPos_anggaran(char *data);

void tambah_pos_anggaran_model(char *nama_pos, long double nominal);

void daftar_pos_anggaran_view(struct PosAnggaran arr[], int n);

void tambah_pos_anggaran_controller(bool message);

void edit_pos_anggaran_controller();

void hapus_pos_anggaran_controller();

void menu_pos_anggaran_view();

bool hapus_pos_anggaran_model(char *namaCari);

bool edit_pos_anggaran_model(char *namaCari);


#endif