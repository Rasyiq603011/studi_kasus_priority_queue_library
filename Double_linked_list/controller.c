#include "controller.h"
#include <stdio.h>
#include <conio.h>

int get_menu_choice(){
    int choice;
    scanf("%d", &choice);
    fflush(stdin);
    return choice;
}

void proses_pengembalian_buku(ListBook *buku) {
    system("cls");

    printf("===== Proses Pengembalian Buku =====\n");
    
    Pbook temp = Head(*buku);
    boolean ada_dipinjam = false;
    
    if (temp == NULL) {
        printf("(Belum ada buku terdaftar)\n");
    } else {
        printf("Buku yang sedang dipinjam:\n");
        while (temp != NULL) {
            // Jika stok 0 berarti buku sedang dipinjam
            if (Stock(temp) == 0) {
                printf("%s\n", Judul(temp));
                ada_dipinjam = true;
            }
            temp = next(temp);
        }
        
        if (ada_dipinjam) {
            char* judul;
            printf("\n");
            readBookName(&judul);
            
            Pbook book = Findbook(*buku, judul);
            if (book == NULL) {
                printf("Buku dengan judul '%s' tidak ditemukan.\n", judul);
                free(judul);
                printf("Tekan sembarang tombol untuk kembali...");
                getch();
                return;
            }
            
            if (Stock(book) > 0) {
                printf("Buku '%s' tidak sedang dipinjam.\n", judul);
                free(judul);
                printf("Tekan sembarang tombol untuk kembali...");
                getch();
                return;
            }
            
            // Kembalikan buku
            Stock(book)++;
            printf("Buku '%s' berhasil dikembalikan!\n", judul);
            printf("Memeriksa antrian peminjam untuk buku '%s'...\n", judul);
            
            // Jika ada peminjam dalam antrian, proses peminjaman untuk prioritas tertinggi
            if (!isEmpty(Antrian(book))) {
                // Cek prioritas 1 (Dosen) terlebih dahulu
                if (proses_prioritas(&(Antrian(book)), 1, &(Stock(book)))) {
                    // Jika tidak ada dosen, cek mahasiswa
                    if (Stock(book) > 0 && proses_prioritas(&(Antrian(book)), 2, &(Stock(book)))) {
                        // Jika tidak ada mahasiswa, cek umum
                        if (Stock(book) > 0) {
                            proses_prioritas(&(Antrian(book)), 3, &(Stock(book)));
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
    }
    
    printf("\nTekan sembarang tombol untuk melanjutkan...");
    getch();
}

void kelola_data_buku(ListBook *buku){
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

void pinjam_menu(ListBook *buku){
    int choice;
    boolean running = true;

    // Main program loop
    while (running) {
        display_pinjam_menu();
        choice = get_menu_choice();
        
        switch (choice) {
            case 1: // Lihat antrian buku
                PrintAllBookData(*buku);
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

void kembali_menu(ListBook *buku){
    int choice;
    boolean running = true;

    // Main program loop
    while (running) {
        display_kembali_menu();
        choice = get_menu_choice();
        
        switch (choice) {
            case 1: // Daftar pengembalian buku
                Daftar_Pengembalian(buku);
                break;
                
            case 2: // Proses pengembalian buku
                proses_pengembalian_buku(buku);
                break;
                
            case 3: // Back to menu
                running = false;
                break;
                
            default: // Invalid choice
                display_invalid_choice_message();
                break;
        }
    }
}

void tambah_buku(ListBook *buku){
    char* judul;
    int stock;
    Pbook existing;
    
    readBookName(&judul);
    stock = read_stock();
    
    existing = Findbook(*buku, judul);
    if (existing != NULL) {
        printf("Buku dengan judul tersebut sudah ada!\n");
        free(judul);
        return;
    }
    
    InsertAkhirV(&Head(*buku), judul, stock);
    printf("Buku berhasil ditambahkan!\n");
    
    // Tidak perlu free judul di sini karena InsertAkhirV membuat kopian
}

void hapus_buku(ListBook *buku){
    char* judul;
    Pbook existing;
    
    readBookName(&judul);
    
    existing = Findbook(*buku, judul);
    if (existing == NULL) {
        printf("Buku dengan judul tersebut tidak ditemukan!\n");
        free(judul);
        return;
    }
    
    DeleteByName(buku, judul);
    printf("Buku berhasil dihapus!\n");
    free(judul);
}

void display_book(ListBook buku){
    Pbook temp = Head(buku);
    printf("===== Daftar Buku =====\n");
    if (temp == NULL) {
        printf("(Belum ada buku)\n");
    } else {
        while (temp != NULL) {
            printf("Judul: %s\n", Judul(temp));
            printf("Stok: %d\n", Stock(temp));
            
            if (!isEmpty(Antrian(temp))) {
                printf("Antrean Peminjam:\n");
                address antrian = Antrian(temp);
                while (antrian != NULL) {
                    printf("  - %s (Prioritas: %d)\n", 
                           info(antrian)->username, 
                           info(antrian)->type);
                    antrian = next(antrian);
                }
            } else {
                printf("Belum ada peminjam untuk buku ini.\n");
            }
            
            printf("------------------------\n");
            temp = next(temp);
        }
    }
    printf("\nTekan sembarang tombol untuk melanjutkan...");
    getch();
}
