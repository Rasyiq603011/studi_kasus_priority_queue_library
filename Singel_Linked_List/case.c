#include "case.h"
#include <conio.h>

int read_stock() {
    int stock;
    char temp;
    
    while (1) {
        printf("Masukan Jumlah Stock: ");
        
        if (scanf("%d", &stock) == 1 && stock > 0) {
            while ((temp = getchar()) != '\n' && temp != EOF);
            return stock;  
        } 
        else {
            while ((temp = getchar()) != '\n' && temp != EOF);
            printf("Input tidak valid! Masukkan angka positif.\n");
        }
    }
}

void readBookName(char** bookName) {
    char temp[100];
    
    // Baca input dari pengguna
    printf("Masukkan Judul buku: ");
    scanf(" %99[^\n]", temp); 
    fflush(stdin); // Membersihkan buffer input
    
    // Hitung panjang string
    size_t len = strlen(temp);
    
    // Alokasi memori untuk nama dengan ukuran yang tepat
    *bookName = (char *)malloc((len + 1) * sizeof(char));
    if (*bookName == NULL) {
        displayMemoryErrorMessage();
        return;
    }
    
    // Salin buffer ke pointer nama
    strcpy(*bookName, temp);
}

void readPersonName(char** personName) {
    char temp[100];
    
    // Baca input dari pengguna
    printf("Masukkan Nama: ");
    scanf(" %99[^\n]", temp); 
    fflush(stdin); // Membersihkan buffer input
    
    // Hitung panjang string
    size_t len = strlen(temp);
    
    // Alokasi memori untuk nama dengan ukuran yang tepat
    *personName = (char *)malloc((len + 1) * sizeof(char));
    if (*personName == NULL) {
        displayMemoryErrorMessage();
        return;
    }
    
    // Salin buffer ke pointer nama
    strcpy(*personName, temp);
}

int get_role(){
    int pilihan = 0;    
    while(1){
        printf("Pilih role:\n");
        printf("1. Dosen\n");
        printf("2. Mahasiswa\n");
        printf("3. Umum\n");
        printf("Masukan Pilihan: ");
        if (scanf("%d", &pilihan) != 1) {
            // Clear input buffer if scanf fails
            while (getchar() != '\n');
            printf("Input tidak valid, masukkan angka.\n");
            continue;
        }
        fflush(stdin);
        
        if(pilihan != 1 && pilihan != 2 && pilihan != 3){
            printf("Pilihan tidak sesuai, pilih antara 1 - 3\n");
        }
        else{
            break;
        }
    }
    return pilihan;
}

/*
Alur Daftar Peminjaman Buku:
1. Tampilkan daftar buku yang tersedia.
2. Minta pengguna untuk memasukkan judul buku yang ingin dipinjam.
*/

void Daftar_Peminjaman(library *perpus) {
    if (perpus == NULL || *perpus == NULL || (*perpus)->data == NULL) {
        printf("Error: Perpustakaan tidak valid\n");
        return;
    }
    
    char* judul = NULL;
    char* username = NULL;
    address temp;
    Struct peminjam;
    int priority;
    
    // Tampilkan daftar buku yang tersedia
    system("cls");
    printf("===== Daftar Buku Tersedia =====\n");
    
    if (ListEmpty(*((*perpus)->data))) {
        printf("(Belum ada buku)\n");
        printf("Tekan sembarang tombol untuk kembali...");
        getch();
        return;
    } else {
        printInfoPbook(*((*perpus)->data));
        printf("==============================\n\n");
    }
    
    // Cek buku yang ingin dipinjam
    readBookName(&judul);
    if (judul == NULL) {
        printf("Error: Gagal membaca judul buku\n");
        return;
    }
    
    temp = SearchByVPbook((*perpus)->data->First, judul);
    
    if (temp == Nil) {
        printf("Buku dengan judul '%s' tidak ditemukan.\n", judul);
        free(judul);
        printf("Tekan sembarang tombol untuk kembali...");
        getch();
        return;
    }
    
    readPersonName(&username);
    if (username == NULL) {
        printf("Error: Gagal membaca nama peminjam\n");
        free(judul);
        return;
    }
    
    // Alokasi memori untuk peminjam
    peminjam = (Struct)malloc(sizeof(User));
    if (peminjam == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk peminjam\n");
        free(username);
        free(judul);
        return;
    }
    
    peminjam->username = username;
    peminjam->type = get_role();

    List *antrian = search_queue_by_book(*perpus, judul);

    if (antrian == Nil) {
        antrian = insert_queue(perpus, &temp);
        if (antrian == Nil) {
            printf("Error: Gagal membuat antrian untuk buku\n");
            free(peminjam->username);
            free(peminjam);
            free(judul);
            return;
        }
    }

    insert_value_first(&(antrian->First), STRUCT_INFO(peminjam), TYPE_STRUCT);

    printf("Peminjam '%s' berhasil ditambahkan ke antrean buku '%s'.\n", username, judul);
    free(judul);
    printf("Tekan sembarang tombol untuk kembali...");
    getch();
}

int proses_prioritas(address *Antrian, int prioritas, int *Stock) {
    // Proses antrian sesuai prioritas
    if (Antrian == NULL || *Antrian == NULL) {
        return 1; // Tidak ada antrian, lanjutkan ke prioritas berikutnya
    }
    
    address temp = *Antrian;
    address prev = NULL;
    
    // Cari peminjam dengan prioritas yang sesuai
    while (temp != Nil && temp->type != TYPE_BOOK) {
        if (info_struct(temp) != NULL && info_struct(temp)->type == prioritas) {
            if (*Stock > 0) {
                // Berhasil meminjam, kurangi stok
                (*Stock)--;
                printf("'%s' berhasil meminjam buku\n", info_struct(temp)->username);
                
                // Hapus dari antrian
                if (prev == NULL) {
                    // Jika node pertama
                    *Antrian = next(temp);
                } else {
                    // Jika bukan node pertama
                    next(prev) = next(temp);
                }
                
                // Dealokasi node yang dihapus
                if (info_struct(temp)->username != NULL) {
                    free(info_struct(temp)->username);
                }
                free(info_struct(temp));
                free(temp);
                
                return 1;
            }
            else {
                // Stok habis
                return 0;
            }
        }
        prev = temp;
        temp = next(temp);
    }
    
    // Tidak ada peminjam dengan prioritas tersebut
    return 1;
}

void proses_antrian_buku(library *perpus) {
    if (perpus == NULL || *perpus == NULL) {
        printf("Error: Perpustakaan tidak valid\n");
        return;
    }
    
    if ((*perpus)->data == NULL) {
        printf("Error: Data perpustakaan tidak valid\n");
        return;
    }
    
    List buku;
    int j;
    buku = *((*perpus)->data);
    
    if (ListEmpty(*((*perpus)->data))) {
        printf("Belum ada buku yang tersedia.\n");
        printf("Tekan sembarang tombol untuk kembali...");
        getch();
        return;
    }
    
    system("cls");
    printf("===== Memproses Antrian Peminjaman =====\n");
    address temp = buku.First;
    while(temp != Nil) {
        printf("Memproses buku '%s':\n", info_buku(temp)->judul);
        
        List *antrianList = search_queue_by_book(*perpus, info_buku(temp)->judul);
        if (antrianList == NULL) {
            printf("- Tidak ada antrian untuk buku ini.\n");
        } else {
            address antrian = antrianList->First;
            if (isEmpty(antrian)) {
                printf("- Tidak ada antrian peminjam untuk buku ini.\n");
            } else {

                for(j = 1; j <= 3; j++) {
                    if (info_buku(temp)->stock <= 0) {
                        printf("- Stok buku habis, tidak dapat memproses antrian lebih lanjut.\n");
                        break;
                    }
                    
                    if(!proses_prioritas(&antrian, j, &(info_buku(temp)->stock))) {
                        printf("- Stok buku habis, tidak dapat memproses antrian lebih lanjut.\n");
                        break;
                    }
                }
            }
        }
        
        printf("\n");
        temp = next(temp);
    }
    
    printf("Proses antrian selesai.\n");
    printf("Tekan sembarang tombol untuk kembali...");
    getch();
}

void Daftar_Pengembalian(library *perpus){
    char* judul;
    char* username;
    List *buku = (*perpus)->data;
    address temp;
    int i;
    
    system("cls");
    printf("===== Daftar Buku =====\n");
    
    if (ListEmpty(*buku)) {
        printf("(Belum ada buku)\n");
        printf("Tekan sembarang tombol untuk kembali...");
        getch();
        return;
    } else {
        print_borrowed_book(*buku);
        printf("=====================\n\n");
    }
    
    // Cek buku yang dikembalikan
    readBookName(&judul);
    temp = SearchByVPbook((*perpus)->data->First , judul);
    
    if (temp == Nil){
        printf("Buku dengan judul '%s' tidak ditemukan.\n", judul);
        free(judul);
        printf("Tekan sembarang tombol untuk kembali...");
        getch();
        return;
    }
    
    // Baca data peminjam
    readPersonName(&username);
    
    // Kembalikan buku (tambah stok)
    (info_buku(buku->First)->stock)++;
    
    printf("Buku '%s' telah dikembalikan oleh '%s'.\n", judul, username);
    printf("Stok buku sekarang: %d\n", info_buku(buku->First)->stock);
    
    free(judul);
    free(username);
    
    printf("Tekan sembarang tombol untuk kembali...");
    getch();
}
