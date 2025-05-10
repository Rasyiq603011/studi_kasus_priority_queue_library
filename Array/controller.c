#include "controller.h"
#include <stdio.h>
#include <conio.h>

int get_menu_choice(){
    int choice;
    scanf("%d", &choice);
    fflush(stdin);
    return choice;
}

void lihat_buku_dipinjam(ListBook buku) {
    system("cls");
    printf("===== Buku yang Sedang Dipinjam =====\n");
    
    boolean ada_dipinjam = false;
    
    if (isEmptyBook(buku)) {
        printf("(Belum ada buku terdaftar)\n");
    } else {
        for (i = 0; i < buku.size; i++) {
            // Jika stok berkurang berarti ada yang dipinjam
            if (buku.Head[i]->pinjam >= 0) {
                printf("Judul: %s\n", buku.Head[i]->judul);
                printf("Status: DIPINJAM\n");
                printf("------------------------\n");
                ada_dipinjam = true;
            }
        }
        
        if (!ada_dipinjam) {
            printf("(Tidak ada buku yang sedang dipinjam)\n");
        }
    }
    
    printf("\nTekan sembarang tombol untuk melanjutkan...");
    getch();
}

void proses_pengembalian_buku(ListBook *buku) {
    system("cls");

    printf("===== Proses Pengembalian Buku =====\n");
    
    boolean ada_dipinjam = false;
    
    if (isEmptyBook(*buku)) {
        printf("(Belum ada buku terdaftar)\n");
    } else {
        printf("Buku yang sedang dipinjam:\n");
        for (i = 0; i < buku->size; i++) {
            if (buku->Head[i]->pinjam >= 0) {
                printf("%s\n", buku->Head[i]->judul);
                ada_dipinjam = true;
            }

        }
        
        if (ada_dipinjam) {
            char* judul;
            printf("\n");
            readBookName(&judul);
            
            int indeks = Findbook(*buku, judul);
            if (indeks == -1) {
                printf("Buku dengan judul '%s' tidak ditemukan.\n", judul);
                free(judul);
                printf("Tekan sembarang tombol untuk kembali...");
                getch();
                return;
            }

            Pbook temp = buku->Head[indeks];
            
            if (temp->pinjam == 0) {
                printf("Buku '%s' tidak sedang dipinjam.\n", judul);
                free(judul);
                printf("Tekan sembarang tombol untuk kembali...");
                getch();
                return;
            }
            
            // Kembalikan buku
            temp->stock++;
            temp->pinjam--;
            printf("Buku '%s' berhasil dikembalikan!\n", judul);
            printf("Memeriksa antrian peminjam untuk buku '%s'...\n", judul);
            
            // Jika ada peminjam dalam antrian, proses peminjaman untuk prioritas tertinggi
            if (isEmpty(temp->antrian)) {
                printf("- Tidak ada antrian peminjam untuk buku ini.\n");
            } else {
                // Proses berdasarkan prioritas (1=Dosen, 2=Mahasiswa, 3=Umum)
                for(i = 1; i <= 3; i++){
                    if (temp->stock <= 0) {
                        printf("- Stok buku habis, tidak dapat memproses antrian lebih lanjut.\n");
                        break;
                    }
                    
                    if(!proses_prioritas(&(temp->antrian), i, &(temp->stock), &(temp->pinjam))){
                        printf("- Stok buku habis, tidak dapat memproses antrian lebih lanjut.\n");
                        break;
                    }
                }
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
                printAllBook(*buku);
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

void tambah_buku(ListBook *buku){
    char* judul;
    int stock;
    int existing;
    
    readBookName(&judul);
    stock = read_stock();
    
    existing = Findbook(*buku, judul);
//    printf("apakah eroro difindbook");
    if (existing != -1) {
        printf("Buku dengan judul tersebut sudah ada!\n");
        free(judul);
        return;
    }
    printf("proses penambahan");
    int cek = addBook(&(*buku), judul, stock);
    
    if (cek){
	    printf("Buku berhasil ditambahkan!\n");    
	    buku->size++;
	}
	else{
		printf("gagal menambah buku");
	}
	free(judul);
	printf("\nTekan sembarang tombol untuk melanjutkan...");
    getch();

}

void hapus_buku(ListBook *buku){
    char* judul;
    int existing;
    
    readBookName(&judul);
    
    existing = Findbook(*buku, judul);
    if (existing == -1) {
        printf("Buku dengan judul tersebut tidak ditemukan!\n");
        free(judul);
        return;
    }
    int cek = deleteBook(&(*buku), judul);
    if (cek){
	    printf("Buku berhasil dihapus!\n"); 
        buku->size--;
	}
	else{
		printf("gagal menghapus buku\n");
	}
    free(judul);
	printf("\nTekan sembarang tombol untuk melanjutkan...");
    getch();
}

void display_book(ListBook buku){
    printf("===== Daftar Buku =====\n");
    if (isEmptyBook(buku)) {
        printf("(Belum ada buku)\n");
    } else {
//    	printf("masuk else");
        for (i=0; i < buku.size; i++ ){ 
            printBookByIndex(buku, i);

            if (!isEmpty(buku.Head[i]->antrian)) {
                printf("Antrean Peminjam:\n");
                address antrian = buku.Head[i]->antrian;
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
        }
    }
    printf("\nTekan sembarang tombol untuk melanjutkan...");
    getch();
}
