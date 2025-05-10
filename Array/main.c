#include "controller.h"
#include "test_case.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {    

    int choice;
    boolean running = true;
    ListBook perpustakaan;
    
    // Inisialisasi array buku
    createListBook(&perpustakaan, 20);

    // Main program loop
    while (running) {
        display_mainmenu();
        choice = get_menu_choice();
        
        switch (choice) {
            case 1: // Kelola data buku
                kelola_data_buku(&perpustakaan);
                break;
                
            case 2: // Proses Peminjaman Buku
                pinjam_menu(&perpustakaan);
                break;
                
            case 3: // Proses Pengembalian Buku
                kembali_menu(&perpustakaan);
                break;
                
            case 4: // Run Test Case
                system("cls");
                run_test_case();
                printf("\nTekan sembarang tombol untuk kembali ke menu utama...");
                getch();
                break;
                
            case 5: // Exit
                running = false;
                display_exit_message();
                break;
                
            default: // Invalid choice
                display_invalid_choice_message();
                break;
        }
    }
    
    // Bersihkan memori saat keluar
    deallocateListBook(&perpustakaan);
    
    return 0;
}
