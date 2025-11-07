#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct PosAnggaran {
  char pos[50];
  float batas_nominal;
};

void clearScreenANSI() { printf("\033[2J\033[H"); }
void header();
void tambah_pos_anggaran(bool message);
void menu_utama();
int main() {
  menu_utama();
  return 0;
}

void header() {
  printf("╔════════════════════════════════════════════════════════════════════"
         "══════════════════════════════╗\n");
  printf("║                                 APLIKASI KEUANGAN MAHASISWA        "
         "                              ║\n");
  printf("╚════════════════════════════════════════════════════════════════════"
         "══════════════════════════════╝\n");
}

void tambah_pos_anggaran(bool message) {
  struct PosAnggaran data;

  bool mengisi = true;
  char lanjut;
  bool alert = false;
  /*
      perulangan untuk mengisi data pos anggaran
  */
  while (mengisi) {

    clearScreenANSI(); // membersihkan layar
    header();
    if (message) {
      printf(
          "\tmohon tambahkan pos anggaran, karena data pos anggaran belum ada "
          "\n");
    }

    /*
        User melakukan input untuk nama pos
    */
    printf("\tMasukkan Nama pos: ");
    fgets(data.pos, sizeof(data.pos), stdin);
    data.pos[strcspn(data.pos, "\n")] = '\0'; // hapus newline

    /*
        Periksa apakah pos sudah ada di file
    */
    bool sudah_ada = false;
    FILE *cekFile = fopen("pos_anggaran.txt", "r");
    if (cekFile != NULL) {
      char line[100];
      char pos_existing[50];
      float batas_existing;

      while (fgets(line, sizeof(line), cekFile)) {
        // format file: namaPos|batasNominal
        if (sscanf(line, "%49[^|]|%f", pos_existing, &batas_existing) == 2) {
          if (strcmp(pos_existing, data.pos) == 0) {
            sudah_ada = true;
            break;
          }
        }
      }
      fclose(cekFile);
    }

    if (sudah_ada) {
      printf("Pos '%s' sudah ada di dalam file. Silakan masukkan nama lain.\n",
             data.pos);
      printf("Tekan ENTER untuk melanjutkan...");
      getchar();
      continue; // kembali ke awal loop tanpa menulis
    }
    /*
        User melakukan input untuk batas anggaran
    */
    printf("\tMasukkan batas anggaran: ");
    scanf(" %f", &data.batas_nominal);
    getchar();
    if (data.batas_nominal <= 0) {
      printf("Anda menetapkan batas anggaran sebesar '%f', batas anggaran "
             "harus lebih besar dari nol.\n",
             data.batas_nominal);
      printf("Tekan ENTER untuk melanjutkan...");
      getchar();
      continue; // kembali ke awal loop tanpa menulis
    }

    /*
    menyimpan data ke dalam file pos_anggaran.txt
    */
    // simpan ke file
    FILE *fp = fopen("pos_anggaran.txt", "a");
    if (fp == NULL) {
      printf("Gagal membuka file untuk menulis!\n");
      return;
    }
    fprintf(fp, "%s|%.2f\n", data.pos, data.batas_nominal);
    fclose(fp);

    printf("Data berhasil ditambahkan!\n");
    message = false;

    printf("==================================================================="
           "==================================================================="
           "===========\n");
    clearScreenANSI(); // membersihkan layar

    /*
        perulangan untuk memvalidasi jawaban
    */
    while (true) {
      /*
    menanyakan kepada user apakah masih ingin menambah data atau sudah selesai
    */
      header();
      if (alert) {
        clearScreenANSI();
        header();
        printf("\n mohon hanya menginput (y/n)\n");
      }
      printf("\tApakah anda masih ingin menambah pos anggaran? \n");
      printf("\tmasukkan (y) untuk tetap menambah \n\tmasukkan (n) jika "
             "selesai \n=");

      scanf(" %c", &lanjut);
      getchar(); // bersihkan buffer
      if (lanjut == 'n' || lanjut == 'N') {
        mengisi = false;
        break;
      } else if (lanjut == 'y' || lanjut == 'Y') {
        break;
      } else {
        alert = true;
      }
    }
  }
  // fclose(fp);
}

void menu_utama() {
  FILE *fp = fopen("pos_anggaran.txt", "r");

  int validasi;

  bool menu = true;
  if (fp == NULL) {
    tambah_pos_anggaran(true);
  }

  int c = fgetc(fp);

  if (c == EOF) {
    fclose(fp);
    tambah_pos_anggaran(true);
  }

  fclose(fp);

  while (menu) {
    clearScreenANSI();

    header();

    printf(
        "=========================== MENU UTAMA ===========================");
    printf(" \n");
    printf("     1. Pencatatan Pos Anggaran\n");
    printf("     2. Pencatatan Transaksi\n");
    printf("     3. Perhitungan & Analisis Keuangan\n");
    printf("     4. Kesimpulan Kondisi Mahasiswa\n");
    printf("     5. Tampilkan laporan keuangan\n");
    printf("     0. Keluar\n");
    printf(
        "==================================================================");
    printf("\n \tPilih menu (0-4): ");
    /*
          perulangan untuk memvalidasi jawaban
      */
    while (true) {
      scanf(" %d", &validasi);
      getchar();
      if (validasi == 0) {
        printf("_______________________________________");
        printf("\n|Tidak ada perubahan. Program selesai.|\n");
        menu = false;
        break;
      } else if (validasi == 1) {
        tambah_pos_anggaran(false);
        break;
      } else {
        printf("Mohon Pilih menu hanya (0-4): ");
      }
    }
  }
}
