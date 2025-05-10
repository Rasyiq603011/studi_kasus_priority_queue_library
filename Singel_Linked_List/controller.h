#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "case.h"
#include "UI.h"
#include "boolean.h"

// Mendapatkan pilihan menu dari pengguna
int get_menu_choice();

// Menu untuk mengelola data buku (tambah, hapus, lihat)
void kelola_data_buku(library *buku);

// Menu untuk peminjaman buku
void pinjam_menu(library *buku);

// Menu untuk pengembalian buku
void kembali_menu(library *buku);

// Menambahkan buku baru ke perpustakaan
void tambah_buku(library *buku);

// Menghapus buku dari perpustakaan
void hapus_buku(library *buku);

// Menampilkan semua buku dalam perpustakaan
void display_book(library buku);

// Melihat buku yang sedang dipinjam
void lihat_buku_dipinjam(library buku);

// Memproses pengembalian buku
void proses_pengembalian_buku(library *buku);

#endif // CONTROLLER_H
