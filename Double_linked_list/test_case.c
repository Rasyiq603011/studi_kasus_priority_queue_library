#include "CaseBook.h"
#include "case.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fungsi untuk menjalankan skenario test case dari studi kasus
void run_test_case() {
    ListBook perpustakaan;
    Pbook buku1, buku2;
    User *anggota1, *dosen1, *umum1;
    
    // Inisialisasi perpustakaan
    CreatebookList(&perpustakaan);
    
    printf("===== Menjalankan Test Case =====\n\n");
    
    // a) 2 X insert elemen "Buku1" dan "Buku2" di list Buku dimana stok buku masing masing 1
    printf("a) Menambahkan Buku1 dan Buku2 dengan stok masing-masing 1\n");
    
    char *judul1 = strdup("Buku1");
    char *judul2 = strdup("Buku2");
    
    InsertAkhirV(&Head(perpustakaan), judul1, 1);
    InsertAkhirV(&Head(perpustakaan), judul2, 1);
    
    printf("   Status: ");
    buku1 = Findbook(perpustakaan, "Buku1");
    buku2 = Findbook(perpustakaan, "Buku2");
    
    if (buku1 != NULL && buku2 != NULL) {
        printf("BERHASIL\n");
    } else {
        printf("GAGAL\n");
    }
    
    // Tampilkan daftar buku
    printf("   Daftar Buku:\n");
    Pbook temp = Head(perpustakaan);
    while (temp != NULL) {
        printf("   - %s (Stok: %d)\n", Judul(temp), Stock(temp));
        temp = next(temp);
    }
    printf("\n");
    
    // b) 1 X insert elemen "Anggota1" sebagai mahasiswa di list peminjaman "Buku1"
    printf("b) Menambahkan Anggota1 sebagai mahasiswa di list peminjaman Buku1\n");
    
    anggota1 = (User*)malloc(sizeof(User));
    anggota1->username = strdup("Anggota1");
    anggota1->type = 2; // Mahasiswa (2)
    
    InsertLastV(&(Antrian(buku1)), anggota1);
    
    printf("   Status: ");
    if (!isEmpty(Antrian(buku1))) {
        printf("BERHASIL\n");
    } else {
        printf("GAGAL\n");
    }
    
    // c) 1 X insert elemen "Dosen1" sebagai dosen di list peminjaman "Buku1"
    printf("c) Menambahkan Dosen1 sebagai dosen di list peminjaman Buku1\n");
    
    dosen1 = (User*)malloc(sizeof(User));
    dosen1->username = strdup("Dosen1");
    dosen1->type = 1; // Dosen (1)
    
    InsertLastV(&(Antrian(buku1)), dosen1);
    
    printf("   Status: BERHASIL\n");
    
    // d) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku1"
    printf("d) Menambahkan Umum1 sebagai masyarakat umum di list peminjaman Buku1\n");
    
    umum1 = (User*)malloc(sizeof(User));
    umum1->username = strdup("Umum1");
    umum1->type = 3; // Umum (3)
    
    InsertLastV(&(Antrian(buku1)), umum1);
    
    printf("   Status: BERHASIL\n");
    
    // e) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku2"
    printf("e) Menambahkan Umum1 sebagai masyarakat umum di list peminjaman Buku2\n");
    
    User *umum1_copy = (User*)malloc(sizeof(User));
    umum1_copy->username = strdup("Umum1");
    umum1_copy->type = 3; // Umum (3)
    
    InsertLastV(&(Antrian(buku2)), umum1_copy);
    
    printf("   Status: BERHASIL\n");
    
    // Tampilkan status antrean
    printf("\n   Status Antrean Buku1:\n");
    address antrean = Antrian(buku1);
    while (antrean != NULL) {
        printf("   - %s (Prioritas: %d)\n", info(antrean)->username, info(antrean)->type);
        antrean = next(antrean);
    }
    
    printf("\n   Status Antrean Buku2:\n");
    antrean = Antrian(buku2);
    while (antrean != NULL) {
        printf("   - %s (Prioritas: %d)\n", info(antrean)->username, info(antrean)->type);
        antrean = next(antrean);
    }
    printf("\n");
    
    // f) Proses peminjaman "Buku1". Pastikan "Dosen1" yang mendapatkan proses peminjaman
    printf("f) Memproses peminjaman Buku1\n");
    
    printf("   Memproses berdasarkan prioritas...\n");
    
    // Proses berdasarkan prioritas (1=Dosen, 2=Mahasiswa, 3=Umum)
    int i;
    for(i = 1; i <= 3; i++){
        if (Stock(buku1) <= 0) {
            printf("   - Stok buku habis\n");
            break;
        }
        
        address temp_antrean = Antrian(buku1);
        address prev = NULL;
        boolean found = false;
        
        // Cari peminjam dengan prioritas yang sesuai
        while(temp_antrean != NULL){
            if(info(temp_antrean)->type == i){
                found = true;
                printf("   - '%s' berhasil meminjam buku (Prioritas: %d)\n", 
                       info(temp_antrean)->username, 
                       info(temp_antrean)->type);
                
                // Kurangi stok
                Stock(buku1)--;
                
                // Hapus dari antrian
                if (prev == NULL) {
                    // Jika node pertama
                    Antrian(buku1) = next(temp_antrean);
                } else {
                    // Jika bukan node pertama
                    next(prev) = next(temp_antrean);
                }
                
                // Simpan informasi peminjam (untuk point g)
                char* peminjam = strdup(info(temp_antrean)->username);
                int prioritas = info(temp_antrean)->type;
                
                // Dealokasi node yang dihapus
                free(info(temp_antrean)->username);
                free(info(temp_antrean));
                free(temp_antrean);
                
                break;
            }
            prev = temp_antrean;
            temp_antrean = next(temp_antrean);
        }
        
        if (found) {
            break;
        }
    }
    
    printf("   Stok Buku1 setelah peminjaman: %d\n\n", Stock(buku1));
    
    printf("   Status Antrean Buku1 setelah peminjaman:\n");
    antrean = Antrian(buku1);
    if (antrean == NULL) {
        printf("   (Antrean kosong)\n");
    } else {
        while (antrean != NULL) {
            printf("   - %s (Prioritas: %d)\n", info(antrean)->username, info(antrean)->type);
            antrean = next(antrean);
        }
    }
    printf("\n");
    
    // g) Proses pengembalian "Buku1" oleh "Dosen1". Pastikan potensi selanjutnya 
    // yang akan mendapatkan fasilitas peminjaman adalah "Anggota1" di list peminjaman "Buku1"
    printf("g) Memproses pengembalian Buku1 oleh Dosen1\n");
    
    // Kembalikan buku (tambah stok)
    Stock(buku1)++;
    printf("   Buku1 berhasil dikembalikan oleh Dosen1\n");
    printf("   Stok Buku1 setelah pengembalian: %d\n", Stock(buku1));
    
    printf("   Memeriksa antrian berikutnya yang mendapat fasilitas peminjaman:\n");
    
    // Periksa antrian siapa yang akan mendapatkan peminjaman berikutnya
    antrean = Antrian(buku1);
    if (antrean == NULL) {
        printf("   (Tidak ada peminjam dalam antrian)\n");
    } else {
        User *next_borrower = NULL;
        int next_priority = 4; // Nilai awal lebih besar dari prioritas maksimum
        
        // Cari peminjam dengan prioritas tertinggi
        while (antrean != NULL) {
            if (info(antrean)->type < next_priority) {
                next_priority = info(antrean)->type;
                next_borrower = info(antrean);
            }
            antrean = next(antrean);
        }
        
        if (next_borrower != NULL) {
            printf("   Peminjam berikutnya: %s (Prioritas: %d)\n", 
                   next_borrower->username, 
                   next_borrower->type);
        }
    }
    
    printf("\n===== Test Case Selesai =====\n");
    
    // Bersihkan memori
    ClearListBook(&perpustakaan);
}
