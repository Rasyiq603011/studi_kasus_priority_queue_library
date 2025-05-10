#include "controller.h"
#include <stdio.h>
#include <conio.h>

int get_menu_choice(){
    int choice;
    scanf("%d", &choice);
    fflush(stdin);
    return choice;
}

void lihat_buku_dipinjam(library buku) {
    system("cls");
    printf("===== Buku yang Sedang Dipinjam =====\n");
    
    print_borrowed_book(*(buku->data));
    
    printf("\nTekan sembarang tombol untuk melanjutkan...");
    getch();
}
void proses_pengembalian_buku(library *buku) {
    if (buku == NULL || *buku == NULL) {
        printf("Error: Perpustakaan tidak valid\n");
        return;
    }
    
    system("cls");
    printf("===== Proses Pengembalian Buku =====\n");
    
    boolean ada_dipinjam = false;
    
    if ((*buku)->data == NULL || ListEmpty(*((*buku)->data))) {
        printf("(Belum ada buku terdaftar)\n");
    } else {
        lihat_buku_dipinjam(*buku);
        ada_dipinjam = ((*buku)->next != Nil);
    }
        
    if (ada_dipinjam) {
        char* judul = NULL;
        printf("\n");
        readBookName(&judul);
        
        if (judul == NULL) {
            printf("Error: Gagal membaca judul buku\n");
            return;
        }
        
        address temp = SearchByVPbook(First(*((*buku)->data)), judul);
        if (temp == Nil) {
            printf("Buku dengan judul '%s' tidak ditemukan.\n", judul);
            free(judul);
            printf("Tekan sembarang tombol untuk kembali...");
            getch();
            return;
        }
        
        if (info_buku(temp)->pinjam <= 0) {
            printf("Buku '%s' tidak sedang dipinjam.\n", judul);
            free(judul);
            printf("Tekan sembarang tombol untuk kembali...");
            getch();
            return;
        }
        
        // Kembalikan buku
        (info_buku(temp)->stock)++;
        (info_buku(temp)->pinjam)--;
        printf("Buku '%s' berhasil dikembalikan!\n", judul);
        printf("Memeriksa antrian peminjam untuk buku '%s'...\n", judul);

        List *antrian = search_queue_by_book(*buku, judul);

        if (antrian == Nil) {
            antrian = insert_queue(buku, &temp);
            if (antrian == Nil) {
                printf("Gagal membuat antrian untuk buku ini.\n");
                free(judul);
                printf("Tekan sembarang tombol untuk kembali...");
                getch();
                return;
            }
        }
        
        // Jika ada peminjam dalam antrian, proses peminjaman untuk prioritas tertinggi
        if (!ListEmpty(*antrian)) {
            // Cek prioritas 1 (Dosen) terlebih dahulu
            if (proses_prioritas(&(antrian->First), 1, &(info_buku(temp)->stock))) {
                // Jika tidak ada dosen, cek mahasiswa
                if (info_buku(temp)->stock > 0 && proses_prioritas(&(antrian->First), 2, &(info_buku(temp)->stock))) {
                    // Jika tidak ada mahasiswa, cek umum
                    if (info_buku(temp)->stock > 0) {
                        proses_prioritas(&(antrian->First), 3, &(info_buku(temp)->stock));
                    }
                }
            }
        } else {
            printf("Tidak ada peminjam dalam antrian untuk buku ini.\n");
        }
        
        free(judul);
    } else {
        printf("(Tidak ada buku yang sedang dipinjam)\n");
    }
    printf("\nTekan sembarang tombol untuk melanjutkan...");
    getch();
}
    


void kelola_data_buku(library *buku){
    int choice;
    boolean running = true;

    // Main program loop
    while (running) {
        display_kelola_data_buku();
        choice = get_menu_choice();
        
        switch (choice) {
            case 1: // Tambah buku
                tambah_buku(buku);
                break;
                
            case 2: // Hapus buku
                hapus_buku(buku);
                break;
                
            case 3: // Lihat data buku
                display_book(*buku);
                break;
                
            case 4: // Back to menu
                running = false;
                break;
                
            default: // Invalid choice
                display_invalid_choice_message();
                break;
        }
    }
}

void pinjam_menu(library *buku){
    int choice;
    boolean running = true;

    // Main program loop
    while (running) {
        display_pinjam_menu();
        choice = get_menu_choice();
        
        switch (choice) {
            case 1: // Lihat antrian buku
                printf("dalam tahap pengembangan");
                printf("\nTekan sembarang tombol untuk melanjutkan...");
                getch();
                break;
                
            case 2: // Daftar pinjam buku
                Daftar_Peminjaman(buku);
                break;
                
            case 3: // Proses antrian buku
                proses_antrian_buku(buku);
                break;
                
            case 4: // Back to menu
                running = false;
                break;
                
            default: // Invalid choice
                display_invalid_choice_message();
                break;
        }
    }
}

void kembali_menu(library *buku){
    int choice;
    boolean running = true;

    // Main program loop
    while (running) {
        display_kembali_menu();
        choice = get_menu_choice();
        
        switch (choice) {
            case 1: // Lihat buku yang dipinjam
                lihat_buku_dipinjam(*buku);
                break;
                
            case 2: // Daftar pengembalian buku
                Daftar_Pengembalian(buku);
                break;
                
            case 3: // Proses pengembalian buku
                proses_pengembalian_buku(buku);
                break;
                
            case 4: // Back to menu
                running = false;
                break;
                
            default: // Invalid choice
                display_invalid_choice_message();
                break;
        }
    }
}

void tambah_buku(library *buku){
    char* judul;
    int stock;
    Pbook newbook;
    
    system("cls");
    printf("===== Tambah Buku =====\n");
    
    readBookName(&judul);

    newbook->judul = strdup(judul);
    newbook->pinjam = 0;
    newbook->stock = read_stock();
    
    InsertLVPbook(&((*buku)->data->First), newbook);
    
    
    printf("\nTekan sembarang tombol untuk melanjutkan...");
    getch();
}

void hapus_buku(library *buku){
    char* judul;
    Pbook delbook;
    
    system("cls");
    printf("===== Hapus Buku =====\n");
    
    if (ListEmpty(*((*buku)->data))) {
        printf("Perpustakaan kosong!\n");
    } else {
        readBookName(&judul);
        
        address temp = SearchByVPbook((*buku)->data->First, judul);
        if (temp == Nil) {
            printf("Buku dengan judul tersebut tidak ditemukan!\n");
        } else {
            DeleteByVPbook((*buku)->data, judul);
            printf("Buku berhasil dihapus!\n");
        }
        
        free(judul);
    }
    
    printf("\nTekan sembarang tombol untuk melanjutkan...");
    getch();
}

void display_book(library buku){
    system("cls");
    printf("===== Daftar Buku =====\n");
    
    if (ListEmpty(*(buku->data))) {
        printf("(Belum ada buku)\n");
    } else {
        printInfoPbook(*(buku->data)); 
        printf("------------------------\n");
    }
    printf("\nTekan sembarang tombol untuk melanjutkan...");
    getch();
}
