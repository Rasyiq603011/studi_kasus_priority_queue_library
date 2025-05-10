#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CaseBook.h"

// Fungsi untuk menjalankan skenario test case dari studi kasus
void run_test_case() {
     ListBook perpustakaan;
     Struct anggota1, dosen1, umum1, umum1_2; 
     int buku1, buku2;
     address antri, antri2;
    
    createListBook(&perpustakaan, 20);
    
    // a) 2 X insert elemen "Buku1" dan "Buku2" di list Buku dimana stok buku masing masing 1
    printf("a) Menambahkan Buku1 dan Buku2 dengan stok masing-masing 1\n");
    
    char *judul1 = strdup("Buku1");
    char *judul2 = strdup("Buku2");
    
    addBook(&perpustakaan, judul1, 1);
    perpustakaan.size++;
    addBook(&perpustakaan, judul2, 1);
    perpustakaan.size++;
    
    printf("   Status: ");
    buku1 = Findbook(perpustakaan, "Buku1");
    buku2 = Findbook(perpustakaan, "Buku2");
    
    if (buku1 != -1 && buku2 != -1) {
        printf("BERHASIL\n");
    } else {
        printf("GAGAL\n");
    }
    
    // Tampilkan daftar buku
    
    // b) 1 X insert elemen "Anggota1" sebagai mahasiswa di list peminjaman "Buku1"
    printf("b) Menambahkan Anggota1 sebagai mahasiswa di list peminjaman Buku1\n");
    
    anggota1 = (Struct)malloc(sizeof(User));
    anggota1->username = strdup("Anggota1");
    anggota1->type = 2; // Mahasiswa (2)
    
    InsertLastV(&(perpustakaan.Head[buku1]->antrian), anggota1);
    
    printf("   Status: ");
    if (!isEmpty(antri)) {
        printf("BERHASIL\n");
    } else {
        printf("GAGAL\n");
    }
    
    // c) 1 X insert elemen "Dosen1" sebagai dosen di list peminjaman "Buku1"
    printf("c) Menambahkan Dosen1 sebagai dosen di list peminjaman Buku1\n");
    
    dosen1 = (Struct)malloc(sizeof(User));
    dosen1->username = strdup("Dosen1");
    dosen1->type = 1; // Dosen (1)

    InsertLastV(&(perpustakaan.Head[buku1]->antrian), dosen1);
    
    printf("   Status: BERHASIL\n");
    
    // d) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku1"
    printf("d) Menambahkan Umum1 sebagai masyarakat umum di list peminjaman Buku1\n");
    
    umum1 = (Struct)malloc(sizeof(User));
    umum1->username = strdup("Umum1");
    umum1->type = 3; // Umum (3)

    InsertLastV(&(perpustakaan.Head[buku1]->antrian), umum1);
    
    printf("   Status: BERHASIL\n");
    
    // e) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku2"
    printf("e) Menambahkan Umum1 sebagai masyarakat umum di list peminjaman Buku2\n");
    
	umum1_2 = (Struct)malloc(sizeof(User));
    umum1_2->username = strdup("Umum1");
    umum1_2->type = 3;
    InsertLastV(&(perpustakaan.Head[buku2]->antrian), umum1_2);
    
    printf("   Status: BERHASIL\n");
    
    // Tampilkan status antrean
    printf("\n   Status Antrean Buku1:\n");
    antri = perpustakaan.Head[buku1]->antrian;
    while (antri != NULL) {
        printf("   - %s (Prioritas: %d)\n", info(antri)->username, info(antri)->type);
        antri = next(antri);
    }
    antri2 = perpustakaan.Head[buku2]->antrian;
    printf("\n   Status Antrean Buku2:\n");
    while (antri2 != NULL) {
        printf("   - %s (Prioritas: %d)\n", info(antri2)->username, info(antri2)->type);
        antri2 = next(antri2);
    }
    printf("\n");
    
    // f) Proses peminjaman "Buku1". Pastikan "Dosen1" yang mendapatkan proses peminjaman
    printf("f) Memproses peminjaman Buku1\n");
    
    printf("   Memproses berdasarkan prioritas...\n");
    
    proses_antrian_buku(&perpustakaan);
    
    printf("   Stok Buku1 setelah peminjaman: %d\n\n", perpustakaan.Head[buku1]->stock);
    
    printf("   Status Antrean Buku1 setelah peminjaman:\n");
	
	antri = perpustakaan.Head[buku1]->antrian;
    if (antri== NULL) {
        printf("   (Antrean kosong)\n");
    } else {
        while (antri != NULL) {
            printf("   - %s (Prioritas: %d)\n", info(antri)->username, info(antri)->type);
            antri = next(antri);
        }
    }
    printf("\n");
    
    // g) Proses pengembalian "Buku1" oleh "Dosen1". Pastikan potensi selanjutnya 
    // yang akan mendapatkan fasilitas peminjaman adalah "Anggota1" di list peminjaman "Buku1"
   

    printf("===== Proses Pengembalian Buku =====\n");
    
    boolean ada_dipinjam = false;
    
    if (isEmptyBook(perpustakaan)) {
        printf("(Belum ada buku terdaftar)\n");
    } else {
        printf("Buku yang sedang dipinjam:\n");
        for (i = 0; i < perpustakaan.size; i++) {
            if (perpustakaan.Head[i]->pinjam >= 0) {
                printf("%s\n", perpustakaan.Head[i]->judul);
                ada_dipinjam = true;
            }

        }
        
        if (ada_dipinjam) {
            int indeks = Findbook(perpustakaan, "Buku1");
            if (indeks == -1) {
                printf("Buku dengan judul buku1 tidak ditemukan.\n");
                printf("Tekan sembarang tombol untuk kembali...");
                getch();
                return;
            }

            Pbook temp = perpustakaan.Head[indeks];
            
            if (temp->pinjam == 0) {
                printf("Buku dengan judul buku1 tidak sedang dipinjam.\n");
                printf("Tekan sembarang tombol untuk kembali...");
                getch();
                return;
            }
            
            // Kembalikan buku
            temp->stock++;
            temp->pinjam--;
            printf("Buku dengan judul buku1 berhasil dikembalikan!\n");
            printf("Memeriksa antrian peminjam untuk buku dengan judul buku1...\n");
            
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
        } else {
            printf("(Tidak ada buku yang sedang dipinjam)\n");
        }
    }
   
    printf("\n===== Test Case Selesai =====\n");
    
    free(judul1);
	free(judul2);
    
    // Bersihkan memori
    deallocateListBook(&perpustakaan);
	
}
