/*  
	File name     : CaseBook.h
    Made by       : Muhammad Nabil Syauqi Rasyiq
    Date          : 1 April 2025
    Description   : Header file for linked list Book as requirement for study case
*/
#ifndef CASEBOOK_H
#define CASEBOOK_H
#include "linked.h"

extern int i; // Variabel Perulangan

typedef struct Buku *Pbook;
typedef struct Buku{
    char* judul; // Judul buku, requirement minimum
	int stock;   // stok buku, requirement minimum
    int pinjam;
    address antrian;        
} BookData;

typedef struct {
    Pbook *Head;
    int size; // ukuran list
    int MaxSize; // ukuran maksimum list
} ListBook;

/*========================================================*/
/*==================== MAIN FUNCTIONS ====================*/
/*========================================================*/

// IS : L terdefinisi
// FS : mengembalikan true jika L kosong
boolean isEmptyBook(ListBook L);

// IS : L terdefinisi
// FS : mengembalikan true jika L penuh
boolean isFullBook(ListBook L);

// IS : L terdefinisi
// FS : Menyiapkan Listbook L dengan ukuran maksimum MaxSize
void createListBook(ListBook *L, int MaxSize);

// IS : A bertipe bookData terdefinisi
// FS : Melakukan alokasi elemen baru dan mengembalikan address elemen tersebut
// Catatan: Jika alokasi gagal, maka mengembalikan Nil
Pbook allocateBook(char* judul, int stock);

// IS : Mendealokasikan semua elemen dalam list
// FS : ListBook L terhapus
void deallocateListBook(ListBook *L);

// IS : L terdefinisi
// FS : Mengembalikan indeks buku yang ducari
// Catatan: Jika tidak ditemukan, maka mengembalikan -1
int Findbook(ListBook L, char* judul);

// IS : L terdefinisi
// FS : Mengembalikan kondisi true jika buku berhasil dihapus
// Catatan: Jika buku tidak ditemukan, maka mengembalikan false
int deleteBook(ListBook *L, char* judul);

// IS : L terdefinisi
// FS : Mengembalikan kondisi true jika buku berhasil ditambahkan
// Catatan: Jika buku sudah ada, maka mengembalikan false
int addBook(ListBook *L, char* judul, int stock);


// IS : L terdefinisi
// FS : Menampilkan semua data buku dalam list
void printAllBook(ListBook L);

// IS : L terdefinisi
// FS : menampilkan data buku dengan indwka
void printBookByIndex(ListBook L, int index);

// IS : L terdefinisi
// FS : Mengembalikan jumlah buku dalam list
// Catatan: Jika list kosong, maka mengembalikan 0
int getJumlahbuku(ListBook L);


#endif /* CASEBook_H */
