/*  
	File name     : CaseBook.h
    Made by       : Muhammad Nabil Syauqi Rasyiq
    Date          : 1 April 2025
    Description   : Header file for linked list Book as requirement for study case
*/
#ifndef CASEBOOK_H
#define CASEBOOK_H
#include "linked.h"
#include "boolean.h"
#define Head(L) ((L).Head)
#define Judul(P) ((P)->judul) 
#define Stock(P) ((P)->stock)
#define Antrian(P) ((P)->antrian) 
#define next(P) ((P)->next) 

extern int i; // Variabel Perulangan

typedef struct Buku *Pbook;
typedef struct Buku{
    char* judul; // Judul buku, requirement minimum
	int stock;   // stok buku, requirement minimum
    address antrian;        
	Pbook next;
} BookData;

typedef struct {
    Pbook Head;
} ListBook;

/*========================================================*/
/*==================== MAIN FUNCTIONS ====================*/
/*========================================================*/

// IS : program tidak tahu apakah ListBook kosong atau tidak
// FS : mereturn true jika List kosong 
boolean ListBookEmpty(ListBook C);

// IS : variabel bertipe Pbook baru di deklarasikan sebagai kamus data
// FS : Pbook dipastikan siap dipakai dengan membuat Pbook menunjuk ke Nil
void CreatePbook(Pbook *A);

// IS : variabel bertipe ListBook baru di deklarasikan sebagai kamus data
// FS : memastikan ListBook siap dipakai dengan membuat ListBook.first menunjuk ke Nil
void CreateBookList(ListBook *C);

// IS : Program membutuhkan sebuah alamat node Pbook yang sudah memiliki nilai sesuai dengan kebutuhan 
// FS : mereturn alamat node Pbook yang sudah di malloc dan diatur nilainya sesuai dengan parameter
// Catatan: Function ini melakukan deep copy dari string menggunakan strdup, jadi parameter string bisa dibebaskan
Pbook Constructor(char* bookName, int stock);

// IS : alamat Node untuk sudah tidak terpakai dan belum di dealloc
// FS : alamat Node dan memori string di dalamnya berhasil di dealloc
void Destructor(Pbook A);

/*=======================================================*/
/*================= INSERTION FUNCTIONS =================*/
/*=======================================================*/

// IS : Pbook *P Sudah di Create
// FS : Pbook newNode sudah dimasukan kedalam ListBook dengan posisi First
void InsertAwal(Pbook *A, Pbook newNode);

// IS : Pbook *P Sudah di Create
// FS : Pbook newNode sudah dimasukan kedalam ListBook dengan posisi Last
void InsertAkhir(Pbook *A, Pbook newNode);

// IS : Pbook *P Sudah di Create
// FS : Pbook newNode sudah dimasukan kedalam ListBook dengan setelah *pBef
void InsertSetelah(Pbook *pBef, Pbook PNew);

// IS : Pbook *P Sudah di Create
// FS : Pbook newNode sudah dimasukan kedalam ListBook dengan sebelum *pAft
void InsertSebelum(Pbook *pAft, Pbook *p, Pbook PNew);

// IS : P mungkin Kosong
// FS : melakukan alokasi sebuah elemen dan menambahkan elemen di posisi First dengan nilai info bertipe int jika alokasi berhasil
void InsertAwalV(Pbook *P, char *judul, int stock);

// IS : P mungkin Kosong
// FS : melakukan alokasi sebuah elemen dan menambahkan elemen di posisi First dengan nilai info bertipe int jika alokasi berhasil
void InsertAkhirV(Pbook *P, char *judul, int stock);

/*========================================================*/
/*================== DELETION FUNCTIONS ==================*/
/*========================================================*/

// IS : A mungkin kosong dan nama kota bisa jadi tidak ditemukan
// FS : Data nama pada kota sudah terhapus semua, lalu node data kota didelete
void DeleteAwal(ListBook *C);

// IS : A mungkin kosong dan nama kota bisa jadi tidak ditemukan
// FS : Data nama pada kota sudah terhapus semua, lalu node data kota didelete
void DeleteAkhir(ListBook *C);
	
// IS : C tidak kosong
// FS : mencari node dengan nilai info dan mendealokasikannya jika ada
void DeleteByName(ListBook *C, char* bookName);

// IS : C tidak kosong
// FS : mendealokasi/menghapus seluruh isi list 
// Catatan: Jika list berisi string, seluruh memori untuk string tersebut juga akan dibebaskan
void ClearListBook(ListBook *C);

/*================================================================*/
/*===================== ADDITIONAL FUNCTIONS =====================*/
/*================================================================*/

// IS : A munkin kosong
// FS : Mereturn Pbook jika bookName ditemukan
Pbook Findbook(ListBook C, char* judul);

// IS : A mungkin kosong
// FS : Menampilkan data nama dari seluruh kota yang ada dalam list
void PrintAllBookData(ListBook C);

// IS : A mungkin kosong
// FS : Menampilkan data nama suatu kota
void PrintBookData(Pbook bookNode);

// IS:
// FS:
int countBook(ListBook C);

// IS : A Mungkin kosong
// FS : Mereturn Jumlah Nama Yang ada di Namakota
int countNameInBook(Pbook bookNode);

// IS : A bisa kosong
// FS : Mereturn Jumlah Nama Yang ada diseluruh kota
int CountTotalNames(Pbook A);

// IS : C mungkin kosong
// FS : isi dari C1 akan dicopy ke C2
void CopyListBook(ListBook C1, ListBook *C2);

#endif /* CASEBook_H */





