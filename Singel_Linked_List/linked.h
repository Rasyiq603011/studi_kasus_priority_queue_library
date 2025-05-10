/* 
	File name    : linked.h
 	Made by      : Muhammad Nabil Syauqi Rasyiq
   	Date         : 30 March 2025
   	Description  : Header file for linked list implementation supporting both int and char* types
*/

#ifndef LINKED_H
#define LINKED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"

typedef enum {
    TYPE_INTEGER,
    TYPE_STRING,
    TYPE_STRUCT,
    TYPE_BOOK,
} DataType;

typedef struct {
    char *username; 
    int type; // 1 untuk umum, 2 untuk mahasiswa, 3 untuk dosen
} User;

typedef struct buku *Pbook;
typedef struct buku{
    char* judul;      // Judul buku, requirement minimum
    int stock;        // stok buku, requirement minimum
    int pinjam;
} BookData;

typedef User *Struct;
typedef char* string;

typedef union {
    int integer;   
    string str;
    Struct strct;
    Pbook book;
}infotype;

typedef struct tElmtList *address;
typedef struct tElmtList {
    infotype info;
    DataType type;
    address next;      
} ElmtList;

typedef struct {
    address First;
} List;

typedef struct data *library;
typedef struct data{
    List *data;
    library next;
}elmtlib;

#define Nil NULL
#define First(L) ((L).First)
#define Type(P) ((P)->type)
#define next(P) ((P)->next)
#define info(P) ((P)->info)
#define info_integer(P) ((P)->info.integer)
#define info_string(P) ((P)->info.str)
#define info_struct(P) ((P)->info.strct)
#define info_buku(P) ((P)->info.book)

#define INT_INFO(x) ((infotype){.integer = (x)})
#define STR_INFO(x) ((infotype){.str = (x)})
#define STRUCT_INFO(x) ((infotype){.strct = (x)})
#define BOOK_INFO(x) ((infotype){.book = (x)})

/*========================================================*/
/*==================== MAIN FUNCTIONS ====================*/
/*========================================================*/

// I.S : program tidak tahu apakah node kosong atau tidak
// F.S : mereturn true jika node kosong
// Alur : return hasil cek P == Nil?
boolean isEmpty(address P);

// I.S : program tidak tahu apakah List kosong atau tidak
// F.S : mereturn true jika List kosong 
// Alur : return hasil cek L.First == Nil?
boolean ListEmpty(List L);

// I.S : variabel bertipe Address baru di deklarasikan sebagai kamus data
// F.S : Address dipastikan siap dipakai dengan membuat address menunjuk ke Nil
void CreateAddress(address *P);

// I.S : variabel bertipe list baru di deklarasikan sebagai kamus data
// F.S : menentukan tipe list dan memastikan list siap dipakai dengan membuat List.first menunjuk ke Nil
void CreateList(List *L);

// Function untuk alokasi node dengan berbagai tipe data
address alokasi(infotype info, DataType type);

// Function untuk dealokasi node
void dealokasi(address P);

/*=======================================================*/
/*================= INSERTION FUNCTIONS =================*/
/*=======================================================*/

// I.S : address *P Sudah di Create
// F.S : address newNode sudah dimasukan kedalam List dengan posisi First
void InsertFirst(address *P, address newNode);

// I.S : address *P Sudah di Create
// F.S : address newNode sudah dimasukan kedalam List dengan posisi Last
void InsertLast(address *P, address newNode);

// I.S : address *P Sudah di Create
// F.S : address newNode sudah dimasukan kedalam List dengan setelah *pBef
void InsertAfter(address *pBef, address PNew);

// I.S : address *P Sudah di Create
// F.S : address newNode sudah dimasukan kedalam List dengan sebelum *pAft
void InsertBefore(address *pAft, address *p, address PNew);

// Function untuk menyisipkan nilai di posisi first
void insert_value_first(address *P, infotype info, DataType type);

// Function untuk menyisipkan nilai di posisi last
void insert_value_last(address *P, infotype info, DataType type);

// Function untuk menyisipkan nilai setelah nilai tertentu
void insert_value_after(address *P, infotype before, infotype info, DataType type_before, DataType type_insert);

// Function untuk menyisipkan nilai sebelum nilai tertentu
void insert_value_before(address *P, infotype after, infotype info, DataType type_after, DataType type_insert);

/*========================================================*/
/*================== DELETION FUNCTIONS ==================*/
/*========================================================*/

// Function untuk menghapus node pertama
void delete_first(address *P, infotype *info);

// Function untuk menghapus node terakhir
void delete_last(address *P, infotype *info);

// Function untuk menghapus node berdasarkan nilai
void delete_by_value(address *P, infotype info, DataType type);

// IS : l tidak kosong
// FS : mendealokasi/menghapus seluruh isi list 
// Catatan: Jika list berisi string, seluruh memori untuk string tersebut juga akan dibebaskan
void clear_list(address *P);

/*=======================================================*/
/*================== DISPLAY FUNCTIONS ==================*/
/*=======================================================*/

// Function untuk mencetak informasi suatu node
void print_info(address P);

// IS : l bisa jadi kosong dan L harus sudah memiliki nilai type
// FS : Menampilkan isi list bertipe Integer dengan format angka1, angka2, ....., angkaTerakhir jika l tidak kosong jika kosong maka "List Kosong"
void print_list(List L);

/*================================================================*/
/*================== COUNT AND SEARCH FUNCTIONS ==================*/
/*================================================================*/

// IS : L mungkin kosong
// FS : menghitung jumlah elemen dari sebuah list
int count_list(List L);

// IS : L mungkin kosong, program ingin mengetahui address node sebelum address node dengan nilai info
// FS : function akan mencari tahu apakah ada node dengan nilai info?, jika ada maka function akan mereturn address node sebelumnya, jika tidak ada return Nil
address search_prec(List L, infotype info);

// IS : L mungkin kosong, program ingin mengetahui address node dengan nilai info
// FS : jika ada maka akan return address node tersebut, jika tidak ada maka akan return Nil
address search_by_value(address P, infotype info);

/*================================================================*/
/*===================== ADDITIONAL FUNCTIONS =====================*/
/*================================================================*/

// IS : L mungkin kosong
// FS : jika L tidak kosong maka function akan mengalokasikan address untuk menampung hasil dari mereverse List, lalu mereturnnya
address get_reverse_list(List L);

// IS : L mungkin kosong
// FS : jika L tidak kosong maka function akan membalik isi dari List 
void reverse_list(List *L);

// IS : L mungkin kosong
// FS : isi dari L1 akan dicopy ke L2
// Catatan: Untuk list string, semua string akan di-deep copy
void copy_list(List L1, List *L2);

// Function untuk mendapatkan nilai di posisi depan
infotype get_front_value(List L);

// Function untuk mendapatkan nilai di posisi belakang
infotype get_tail_value(List L);

/*=================================================================*/
/*================== IMPLEMENTATION STRUCT MODUL ==================*/
/*=================================================================*/

// Function untuk alokasi node struct
address alokasi_struct(Struct data);

// Function untuk dealokasi node struct
void dealokasi_struct(address P);

// Function untuk mencetak struct
void print_struct(Struct data);

// Function untuk membandingkan struct
int compare_struct(Struct data1, Struct data2);

/*================================================================*/
/*======================= KHUSUS BOOK DATA =======================*/
/*================================================================*/

address AlokasiPbook(Pbook data);

void DeAlokasiPbook(address P);

void InsertFVPbook(address *P, Pbook info);

void InsertLVPbook(address *P, Pbook info);

void DeleteFirstPbook(List *L, Pbook *info);

void DeleteLastPbook(List *L, Pbook *info);

void DeleteByVPbook(List *L, char *judul);

address SearchByVPbook(address P, char *judul);

void printInfoPbook(List L);

Pbook GetFrontValuePbook(List L);

Pbook GetTailValuePbook(List L);

void print_borrowed_book(List L);

/*=================================================================*/
/*=================== KHUSUS Library MANAGEMENT ===================*/
/*=================================================================*/

// IS : Library baru terdeskripsi
// FS : Library baru sudah teralokasi dan siap digunakan, diinisialiasi node untuk data buku, dengan type list: BOOK
void create_library(library *Perpustakaan);

// IS:
// FS:
boolean is_queue_exits(library Perpustakaan);

// IS:
// FS:
List *insert_queue(library *Perpustakaan, address *buku);

// IS:
// FS:
void delete_queue_by_book(library *Perpustakaan, char *judul);

// Function untuk mendapatkan judul buku dari antrian
string get_judul_antrian(address P);

// IS:
// FS:
void delete_all_queue(library *Perpustakaan);

// IS:
// FS:
List *search_queue_by_book(library Perpustakaan, char *judul);

// IS:
// FS:
void deallocated_library(library *Perpustakaan);

#endif /* LINKED_H */
