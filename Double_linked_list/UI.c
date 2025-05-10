#include "UI.h"
#include <stdio.h>
#include <stdlib.h>

void display_mainmenu(){
    system("cls");
    printf("========= MAIN MENU ==========\n");
    printf("1. Kelola Data Buku\n");
    printf("2. Peminjaman Buku\n");
    printf("3. Pengembalian Buku\n");
    printf("4. Jalankan Test Case\n");
    printf("5. Exit\n");
    printf("Masukan Pilihan: ");
}

void display_kelola_data_buku(){
    system("cls");
    printf("========= Kelola Data Buku ==========\n");
    printf("1. Tambah Data Buku\n");
    printf("2. Hapus Data Buku\n");
    printf("3. Lihat Data Buku\n");
    printf("4. Back to Menu\n");
    printf("Masukan Pilihan: ");
}

void display_pinjam_menu(){
    system("cls");
    printf("========= Menu Peminjaman ==========\n");
    printf("1. Lihat Antrian Buku\n");
    printf("2. Daftar Pinjam Buku\n");
    printf("3. Proses Antrian Buku\n");
    printf("4. Back to Menu\n");
    printf("Masukan Pilihan: ");
}

void display_kembali_menu(){
    system("cls");
    printf("========= Menu Pengembalian ==========\n");
    printf("1. Daftar Pengembalian Buku\n");
    printf("2. Proses Pengembalian Buku\n");
    printf("3. Back to Menu\n");
    printf("Masukan Pilihan: ");    
}

void display_exit_message(){
    printf("Terima Kasih telah Menggunakan Program ini\n");
}

void display_invalid_choice_message(){
    printf("Pilihan tidak valid\n");
    printf("Tekan sembarang tombol untuk melanjutkan...");
    getch();
}

void displayMemoryErrorMessage() {
    printf("Error: Gagal mengalokasikan memori.\n");
}
