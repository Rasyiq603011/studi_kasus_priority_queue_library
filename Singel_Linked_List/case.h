#ifndef CASE_H
#define CASE_H

#include "linked.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Membaca input jumlah stok buku
int read_stock();

// Membaca input nama buku
void readBookName(char** bookName);

// Membaca input nama peminjam
void readPersonName(char** personName);

// Mendapatkan role/prioritas peminjam (1=Dosen, 2=Mahasiswa, 3=Umum)
int get_role();

// Mendaftarkan peminjaman buku
void Daftar_Peminjaman(library *perpus);

// Memproses peminjaman berdasarkan prioritas
int proses_prioritas(address *Antrian, int prioritas, int *Stock);

// Memproses semua antrian peminjaman buku
void proses_antrian_buku(library *perpus);

// Mendaftarkan pengembalian buku
void Daftar_Pengembalian(library *perpus);

#endif // CASE_H
