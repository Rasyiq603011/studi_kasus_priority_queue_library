#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Menampilkan menu utama
void display_mainmenu();

// Menampilkan menu kelola data buku
void display_kelola_data_buku();

// Menampilkan menu peminjaman
void display_pinjam_menu();

// Menampilkan menu pengembalian
void display_kembali_menu();

// Menampilkan pesan exit
void display_exit_message();

// Menampilkan pesan pilihan tidak valid
void display_invalid_choice_message();

// Menampilkan pesan error memori
void displayMemoryErrorMessage();

#endif // UI_H
