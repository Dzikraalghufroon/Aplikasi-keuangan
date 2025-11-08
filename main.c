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
void edit_pos_anggaran();
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
      continue;
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
      continue;
    }

    /*
    menyimpan data ke dalam file pos_anggaran.txt
    */
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
}
void edit_pos_anggaran() {
  FILE *fp = fopen("pos_anggaran.txt", "r");
  FILE *EDIT = fopen("Temp_pos_anggaran.txt", "w");
  struct PosAnggaran data;
  char namaCari[50];
  bool success = false;

  if (!fp || !EDIT) {
    printf("Gagal membuka file!\n");
    return;
  }

  clearScreenANSI();
  header();
  printf("\n=== DAFTAR POS ANGGARAN ===\n\n");
  printf("+------+--------------------------------+------------------+\n");
  printf("| No   | Pos Anggaran                   | Batas Nominal    |\n");
  printf("+------+--------------------------------+------------------+\n");

  int nomor = 1;
  while (fscanf(fp, "%[^|]|%f\n", data.pos, &data.batas_nominal) == 2) {
    printf("| %-4d | %-30s | %16.2f |\n", nomor, data.pos, data.batas_nominal);
    nomor++;
  }
  printf("+------+--------------------------------+------------------+\n");

  // Kembali ke awal file untuk proses edit
  rewind(fp);

  printf("Masukkan nama pos yang ingin diubah: ");
  fgets(namaCari, sizeof(namaCari), stdin);
  namaCari[strcspn(namaCari, "\n")] = '\0';

  while (fscanf(fp, "%[^|]|%f\n", data.pos, &data.batas_nominal) == 2) {
    if (strcmp(data.pos, namaCari) == 0) {
      success = true;
      printf("Masukkan batas nominal baru: ");
      scanf("%f", &data.batas_nominal);
    }
    fprintf(EDIT, "%s|%.2f\n", data.pos, data.batas_nominal);
  }

  fclose(fp);
  fclose(EDIT);

  remove("pos_anggaran.txt");
  rename("Temp_pos_anggaran.txt", "pos_anggaran.txt");

  if (success) {
    printf("\nData berhasil diubah!\n");
  } else {
    printf("\nData tidak ditemukan!\n");
  }

  printf("Tekan Enter untuk kembali...");
  getchar();
  getchar();
}

void hapus_pos_anggaran() {
  FILE *fp = fopen("pos_anggaran.txt", "r");
  FILE *EDIT = fopen("Temp_pos_anggaran.txt", "w");
  struct PosAnggaran data;
  char namaCari[50];
  bool success = false;

  if (!fp || !EDIT) {
    printf("Gagal membuka file!\n");
    return;
  }

  clearScreenANSI();
  header();
  printf("\n=== DAFTAR POS ANGGARAN ===\n\n");
  printf("+------+--------------------------------+------------------+\n");
  printf("| No   | Pos Anggaran                   | Batas Nominal    |\n");
  printf("+------+--------------------------------+------------------+\n");

  int nomor = 1;
  while (fscanf(fp, "%[^|]|%f\n", data.pos, &data.batas_nominal) == 2) {
    printf("| %-4d | %-30s | %16.2f |\n", nomor, data.pos, data.batas_nominal);
    nomor++;
  }
  printf("+------+--------------------------------+------------------+\n");

  // Kembali ke awal file untuk proses edit
  rewind(fp);

  printf("Masukkan nama pos yang ingin dihapus: ");
  fgets(namaCari, sizeof(namaCari), stdin);
  namaCari[strcspn(namaCari, "\n")] = '\0';

  while (fscanf(fp, "%[^|]|%f\n", data.pos, &data.batas_nominal) == 2) {
    if (strcmp(data.pos, namaCari) != 0) {
      success = true;
      fprintf(EDIT, "%s|%.2f\n", data.pos, data.batas_nominal);
    }
  }

  fclose(fp);
  fclose(EDIT);

  remove("pos_anggaran.txt");
  rename("Temp_pos_anggaran.txt", "pos_anggaran.txt");

  if (success) {
    printf("\nData berhasil dihapus!\n");
  } else {
    printf("\nData gagal di hapus!\n");
  }

  printf("Tekan Enter untuk kembali...");
  getchar();
}

void menu_pos_anggaran() {
  bool menu = true;
  int validasi;
  while (menu) {
    clearScreenANSI();

    header();

    printf("======================= MENU POS ANGGARAN =======================");
    printf(" \n");
    printf("     1. Tambah Pos Anggaran\n");
    printf("     2. Edit Pos Anggaran\n");
    printf("     3. Hapus Pos Anggaran\n");
    printf("     0. Keluar\n");
    printf(
        "==================================================================");
    printf("\n \tPilih menu (0-3): ");
    /*
          perulangan untuk memvalidasi jawaban
      */
    while (true) {
      scanf(" %d", &validasi);
      getchar();
      if (validasi ==
          0) { // jika user input 0 maka program akan kembali ke menu utama
        menu = false;
        break;
      } else if (validasi == 1) { // jika user input 1 maka program akan masuk
                                  // ke modul tambah pos anggaran
        tambah_pos_anggaran(false);
        break;
      } else if (validasi == 2) { // jika user input 2 maka program akan masuk
                                  // ke modul edit pos anggaran
        edit_pos_anggaran();
        break;
      } else if (validasi == 3) { // jika user input 3 maka program akan masuk
                                  // ke modul hapus pos anggaran
        hapus_pos_anggaran();
        break;
      } else {
        printf("Mohon Pilih menu hanya (0-3): ");
      }
    }
  }
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
        printf("____________________");
        printf("\n|Program selesai.|\n");
        menu = false;
        break;
      } else if (validasi == 1) {
        // tambah_pos_anggaran(false);
        menu_pos_anggaran();
        break;
      } else {
        printf("Mohon Pilih menu hanya (0-4): ");
      }
    }
  }
}
