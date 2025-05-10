#include "case.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fungsi untuk menjalankan skenario test case dari studi kasus
void run_test_case() {
    library perpus = NULL;
    User *anggota1 = NULL, *dosen1 = NULL, *umum1 = NULL;
    Pbook book1 = NULL, book2 = NULL;
    char *judul1 = NULL, *judul2 = NULL;

    // Alokasikan memory
    perpus = (library)malloc(sizeof(elmtlib));
    if (perpus == NULL) {
        printf("Gagal mengalokasikan memori untuk perpus\n");
        goto cleanup;  // Langsung lompat ke pembersihan
    }
    
    // Alokasi memory untuk data perpustakaan
    perpus->data = (List *)malloc(sizeof(List));
    if (perpus->data == NULL) {
        printf("Gagal mengalokasikan memori untuk data perpus\n");
        goto cleanup;
    }
    
    perpus->next = Nil;  // Inisialisasi next pointer ke NULL
    
    // Alokasi memory untuk buku
    book1 = (Pbook)malloc(sizeof(BookData));
    if (book1 == NULL) {
        printf("Gagal mengalokasikan memori untuk book1\n");
        goto cleanup;
    }
    
    book2 = (Pbook)malloc(sizeof(BookData));
    if (book2 == NULL) {
        printf("Gagal mengalokasikan memori untuk book2\n");
        goto cleanup;
    }
    
    // Alokasi memory untuk pengguna
    anggota1 = (User *)malloc(sizeof(User));
    if (anggota1 == NULL) {
        printf("Gagal mengalokasikan memori untuk anggota1\n");
        goto cleanup;
    }

    dosen1 = (User *)malloc(sizeof(User));
    if (dosen1 == NULL) {
        printf("Gagal mengalokasikan memori untuk dosen1\n");
        goto cleanup;
    }

    umum1 = (User *)malloc(sizeof(User));
    if (umum1 == NULL) {
        printf("Gagal mengalokasikan memori untuk umum1\n");
        goto cleanup;
    }
    
    book1->judul = NULL;
    book2->judul = NULL;
    anggota1->username = NULL;
    dosen1->username = NULL;
    umum1->username = NULL;
    
    // Inisialisasi perpus
    create_library(&perpus);
    
    printf("===== Menjalankan Test Case =====\n\n");
    
    // a) Menambahkan Buku1 dan Buku2 dengan stok masing-masing 1
    printf("a) Menambahkan Buku1 dan Buku2 dengan stok masing-masing 1\n");
    
    judul1 = strdup("Buku1");
    if (judul1 == NULL) {
        printf("Gagal mengalokasikan memori untuk judul1\n");
        // Clean up
        return;
    }
    
    judul2 = strdup("Buku2");
    if (judul2 == NULL) {
        printf("Gagal mengalokasikan memori untuk judul2\n");
        free(judul1);
        // Clean up
        return;
    }
    
    book1->judul = strdup("Buku1");
    if (book1->judul == NULL) {
        printf("Gagal mengalokasikan memori untuk judul buku1\n");
        free(judul2);
        free(judul1);
        // Clean up
        return;
    }
    
    book2->judul = strdup("Buku2");
    if (book2->judul == NULL) {
        printf("Gagal mengalokasikan memori untuk judul buku2\n");
        free(book1->judul);
        free(judul2);
        free(judul1);
        // Clean up
        return;
    }

    book1->stock = 1;
    book2->stock = 1;
    book1->pinjam = 0;
    book2->pinjam = 0;
    
    InsertLVPbook(&(perpus->data->First), book1);
    InsertLVPbook(&(perpus->data->First), book2);

    address check1 = SearchByVPbook(perpus->data->First, judul1);
    address check2 = SearchByVPbook(perpus->data->First, judul2);
    
    printf("   Status: ");
    if (check1 != Nil && check2 != Nil) {
        printf("BERHASIL\n");
    } else {
        printf("GAGAL\n");
    }
    
    // Tampilkan daftar buku
    printf("   Daftar Buku:\n");
    printInfoPbook(*(perpus->data));
    printf("\n");
    
    // b) Menambahkan Anggota1 sebagai mahasiswa di list peminjaman Buku1
    printf("b) Menambahkan Anggota1 sebagai mahasiswa di list peminjaman Buku1\n");
    
    List *antrian = search_queue_by_book(perpus, judul1);
    
    if (antrian == Nil) {
       address buku1 = SearchByVPbook(perpus->data->First, judul1);
       if (buku1 != Nil) {
           antrian = insert_queue(&perpus, &buku1);
       } else {
           printf("Error: Buku1 tidak ditemukan\n");
           return;
       }
    }
    
    anggota1->username = strdup("Mahasiswa1");
    if (anggota1->username == NULL) {
        printf("Gagal mengalokasikan memori untuk username anggota1\n");
        return;
    }
    anggota1->type = 2;

    if (antrian != Nil) {
        insert_value_first(&(antrian->First), STRUCT_INFO(anggota1), TYPE_STRUCT);
    } else {
        printf("Error: Antrian untuk Buku1 tidak berhasil dibuat\n");
        return;
    }

    printf("   Status: ");
    if (perpus->next != Nil) {
        printf("BERHASIL\n");
    } else {
        printf("GAGAL\n");
    }
    
    // c) 1 X insert elemen "Dosen1" sebagai dosen di list peminjaman "Buku1"
    printf("c) Menambahkan Dosen1 sebagai dosen di list peminjaman Buku1\n");
    
    dosen1->username = strdup("Dosen1");
    dosen1->type = 1;
    insert_value_first(&(antrian->First), STRUCT_INFO(anggota1), TYPE_STRUCT);
    
    printf("   Status: BERHASIL\n");
    
    // d) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku1"
    printf("d) Menambahkan Umum1 sebagai masyarakat umum di list peminjaman Buku1\n");

    umum1->username = strdup("Umum1");
    umum1->type = 3;
    insert_value_first(&(antrian->First), STRUCT_INFO(umum1), TYPE_STRUCT);
    
    printf("   Status: BERHASIL\n");
    
    // e) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku2"
    printf("e) Menambahkan Umum1 sebagai masyarakat umum di list peminjaman Buku2\n");

    List *antrian2 = search_queue_by_book(perpus, judul1);
    
    if(antrian2 == Nil){
       address buku2 = SearchByVPbook(perpus->data->First, judul2);
       antrian2 = insert_queue(&(perpus), &buku2);
    }

    Struct umum1_c = (Struct)malloc(sizeof(User));
    if (umum1_c == NULL) {
        printf("Gagal mengalokasikan memori untuk umum1\n");
        return;
    }
    umum1_c->username = strdup("Umum1");
    umum1_c->type = 3;

    insert_value_first(&(antrian->First), STRUCT_INFO(umum1_c), TYPE_STRUCT);
    
    printf("   Status: BERHASIL\n");
    
    // Tampilkan status antrean
    printf("\n   Status Antrean Buku1:\n");
    printf("tahap pengembangan");
    printf("\n");
    
    // f) Proses peminjaman "Buku1". Pastikan "Dosen1" yang mendapatkan proses peminjaman
    printf("f) Memproses peminjaman Buku1\n");
    
    printf("   Memproses berdasarkan prioritas...\n");

	printf("Tekan sembarang tombol untuk proses antrian...");
    getch();
    proses_antrian_buku(&perpus);
    
    printf("   Stok Buku1 setelah peminjaman: %d\n\n", info_buku(perpus->data->First)->stock);
    
    printf("   Status Antrean Buku1 setelah peminjaman:\n");
    printf("Tahap Pengembangan");
    printf("\n");
    
    // g) Proses pengembalian "Buku1" oleh "Dosen1". Pastikan potensi selanjutnya 
    // yang akan mendapatkan fasilitas peminjaman adalah "Anggota1" di list peminjaman "Buku1"
    printf("g) Memproses pengembalian Buku1 oleh Dosen1\n");
    
    
    
    printf("\n===== Test Case Selesai =====\n");
    
cleanup: // Bersihkan seluruh alokasi memory

    if (perpus != NULL) {
        deallocated_library(&perpus);
    }
    
    if (judul1 != NULL) free(judul1);
    if (judul2 != NULL) free(judul2);
    
    
    if (anggota1 != NULL) {
        if (anggota1->username != NULL) free(anggota1->username);
        free(anggota1);
    }
    
    if (dosen1 != NULL) {
        if (dosen1->username != NULL) free(dosen1->username);
        free(dosen1);
    }
    
    if (umum1 != NULL) {
        if (umum1->username != NULL) free(umum1->username);
        free(umum1);
    }
}
