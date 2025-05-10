#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "case.h"
#include "UI.h"

// Mendapatkan pilihan menu dari pengguna
int get_menu_choice();

void lihat_buku_dipinjam(ListBook buku);

// Menu untuk mengelola data buku (tambah, hapus, lihat)
void kelola_data_buku(ListBook *buku);

// Menu untuk peminjaman buku
void pinjam_menu(ListBook *buku);

// Menu untuk pengembalian buku
void kembali_menu(ListBook *buku);

// Menambahkan buku baru ke perpustakaan
void tambah_buku(ListBook *buku);

// Menghapus buku dari perpustakaan
void hapus_buku(ListBook *buku);

// Menampilkan semua buku dalam perpustakaan
void display_book(ListBook buku);

// Melihat buku yang sedang dipinjam
void lihat_buku_dipinjam(ListBook buku);

// Memproses pengembalian buku
void proses_pengembalian_buku(ListBook *buku);

#endif // CONTROLLER_H
