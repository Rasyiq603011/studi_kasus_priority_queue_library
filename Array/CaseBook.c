/*  
	File name	: CaseBook.c
    Made by		: Muhammad Nabil Syauqi Rasyiq
    Date		: 2 April 2025
    Description	: Implementation of linked list Casebook.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CaseBook.h"

int i; // Variabel Perulangan

/*========================================================*/
/*==================== MAIN FUNCTIONS ====================*/
/*========================================================*/

// IS : L terdefinisi
// FS : mengembalikan true jika L kosong
boolean isEmptyBook(ListBook L){
    return (L.size == 0);
}

// IS : L terdefinisi
// FS : mengembalikan true jika L penuh
boolean isFullBook(ListBook L){
    return (L.size == L.MaxSize);
}

// IS : L terdefinisi
// FS : Menyiapkan Listbook L dengan ukuran maksimum MaxSize
void createListBook(ListBook *L, int MaxSize){
    L->Head = (Pbook*)malloc(MaxSize * sizeof(Pbook));
    L->size = 0;
    L->MaxSize = MaxSize;
}

// IS : A bertipe bookData terdefinisi
// FS : Melakukan alokasi elemen baru dan mengembalikan address elemen tersebut
// Catatan: Jika alokasi gagal, maka mengembalikan Nil
Pbook allocateBook(char* judul, int stock){
	Pbook newBook = (Pbook) malloc(sizeof(BookData));
    if (newBook != NULL) {

        newBook->judul = strdup(judul);
        if (newBook->judul == NULL) {
            free(newBook);
            return NULL;
        }
        newBook->stock = stock;
        CreateAddress(&(newBook->antrian));
		newBook->pinjam = 0;
    }
    return newBook;
}

// IS : Mendealokasikan semua elemen dalam list
// FS : ListBook L terhapus
void deallocateListBook(ListBook *L) {
    int j; 
    
    for (j = 0; j < L->size; j++) {
        if (L->Head[j] != NULL) {

            if (L->Head[j]->antrian != NULL) {
                List tempList;
                tempList.type = TYPE_STRUCT;
                tempList.First = L->Head[j]->antrian;
                ClearList(&tempList);
                L->Head[j]->antrian = NULL; 
            }
            

            if (L->Head[j]->judul != NULL) {
                free(L->Head[j]->judul);
                L->Head[j]->judul = NULL;
            }
            

            free(L->Head[j]);
            L->Head[j] = NULL;
        }
    }
    

    if (L->Head != NULL) {
        free(L->Head);
        L->Head = NULL;
    }
    
    L->size = 0;
    L->MaxSize = 0;
}


// IS : L terdefinisi
// FS : Mengembalikan indeks buku yang ducari
// Catatan: Jika tidak ditemukan, maka mengembalikan -1
int Findbook(ListBook L, char* judul){
    for (i = 0; i < L.size; i++) {
        if (strcmp(L.Head[i]->judul, judul) == 0) {
            return i; // Mengembalikan indeks buku yang ditemukan
        }
    }
    return -1; // Buku tidak ditemukan
}

// IS : L terdefinisi
// FS : Mengembalikan kondisi true jika buku berhasil dihapus
// Catatan: Jika buku tidak ditemukan, maka mengembalikan false
int deleteBook(ListBook *L, char* judul){
    int index = Findbook(*L, judul);
    if (index != -1) {
        free(L->Head[index]->judul); // Mendealokasikan judul buku
        for (i = index; i < L->size; i++) {
            L->Head[i] = L->Head[i + 1]; // Menggeser elemen ke kiri
        }
        L->size--; // Mengurangi ukuran list
        return 1; // Buku berhasil dihapus
    }
    return 0; // Buku tidak ditemukan
}

// IS : L terdefinisi
// FS : Mengembalikan kondisi true jika buku berhasil ditambahkan
// Catatan: Jika buku sudah ada, maka mengembalikan false
int addBook(ListBook *L, char* judul, int stock){
    if(isFullBook(*L)){
        return 0;
    }
    Pbook newbook = allocateBook(judul, stock);
    if (newbook == NULL){
        return 0;
    }
    L->Head[L->size] = newbook;
    return 1;
}

// IS : L terdefinisi
// FS : Menampilkan semua data buku dalam list
void printAllBook(ListBook L){
	printf("masuk print\n");
    for (i=0; i < L.size; i++ ){
    	printf("iterasi ke-%d luar", i);
        printBookByIndex(L, i);
    }
    printf("Keluar print");
}

// IS : L terdefinisi
// FS : menampilkan data buku dengan indwka
void printBookByIndex(ListBook L, int index){
    printf("Judul : %s, Stock : %d \n", L.Head[index]->judul, L.size);
}

// IS : L terdefinisi
// FS : Mengembalikan jumlah buku dalam list
// Catatan: Jika list kosong, maka mengembalikan 0
int getJumlahbuku(ListBook L){
    return L.size;
}



