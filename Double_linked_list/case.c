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

void Daftar_Peminjaman(ListBook *buku){
    char* judul;
    char* username;
    Pbook book;
    Struct orang;
    
    // Tampilkan daftar buku yang tersedia
    system("cls");
    printf("===== Daftar Buku Tersedia =====\n");
    Pbook temp = Head(*buku);
    if (temp == NULL) {
        printf("(Belum ada buku)\n");
        printf("Tekan sembarang tombol untuk kembali...");
        getch();
        return;
    } else {
        while (temp != NULL) {
            printf("Judul: %s (Stok: %d)\n", Judul(temp), Stock(temp));
            temp = next(temp);
        }
        printf("==============================\n\n");
    }
    
    // Cek buku yang ingin dipinjam
    readBookName(&judul);
    book = Findbook(*buku, judul);
    
    if (book == NULL){
        printf("Buku dengan judul '%s' tidak ditemukan.\n", judul);
        free(judul);
        printf("Tekan sembarang tombol untuk kembali...");
        getch();
        return;
    }
    
    // Baca data peminjam
    readPersonName(&username);
    
    // Buat struct peminjam
    orang = (Struct)malloc(sizeof(User));
    if (orang == NULL) {
        displayMemoryErrorMessage();
        free(judul);
        free(username);
        printf("Tekan sembarang tombol untuk kembali...");
        getch();
        return;
    }
    
    orang->username = username;
    orang->type = get_role();
    
    // Masukkan ke antrean buku
    
    InsertLastV(&(Antrian(book)), orang);
    
    printf("Peminjam '%s' berhasil ditambahkan ke antrean buku '%s'.\n", username, judul);
    
    free(judul);
    printf("Tekan sembarang tombol untuk kembali...");
    getch();
}

int proses_prioritas(address *Antrian, int prioritas, int *Stock){
    // Proses antrian sesuai prioritas
    address temp;
    address prev = NULL;
    
    if (*Antrian == NULL) {
        return 1; // Tidak ada antrian, lanjutkan ke prioritas berikutnya
    }
    
    temp = *Antrian;
    
    // Cari peminjam dengan prioritas yang sesuai
    while(temp != NULL){
        if(info(temp)->type == prioritas){
            if(*Stock > 0){
                // Berhasil meminjam, kurangi stok
                (*Stock)--;
                printf("'%s' berhasil meminjam buku\n", info(temp)->username);
                
                // Hapus dari antrian
                if (prev == NULL) {
                    // Jika node pertama
                    *Antrian = next(temp);
                } else {
                    // Jika bukan node pertama
                    next(prev) = next(temp);
                }
                
                // Dealokasi node yang dihapus
                free(info(temp)->username);
                free(info(temp));
                free(temp);
                
                return 1;
            }
            else{
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

void proses_antrian_buku(ListBook *book){
    Pbook temp = Head(*book);
    int i;
    
    if (temp == NULL) {
        printf("Belum ada buku yang tersedia.\n");
        printf("Tekan sembarang tombol untuk kembali...");
        getch();
        return;
    }
    
    printf("===== Memproses Antrian Peminjaman =====\n");
    
    while(temp != NULL){
        printf("Memproses buku '%s':\n", Judul(temp));
        
        if (isEmpty(Antrian(temp))) {
            printf("- Tidak ada antrian peminjam untuk buku ini.\n");
        } else {
            // Proses berdasarkan prioritas (1=Dosen, 2=Mahasiswa, 3=Umum)
            for(i = 1; i <= 3; i++){
                if (Stock(temp) <= 0) {
                    printf("- Stok buku habis, tidak dapat memproses antrian lebih lanjut.\n");
                    break;
                }
                
                if(!proses_prioritas(&(Antrian(temp)), i, &(Stock(temp)))){
                    printf("- Stok buku habis, tidak dapat memproses antrian lebih lanjut.\n");
                    break;
                }
            }
        }
        
        temp = next(temp);
        printf("\n");
    }
    
    printf("Proses antrian selesai.\n");
    printf("Tekan sembarang tombol untuk kembali...");
    getch();
}

void Daftar_Pengembalian(ListBook *buku){
    char* judul;
    char* username;
    Pbook book;
    
    // Tampilkan daftar buku
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printf("===== Daftar Buku =====\n");
    Pbook temp = Head(*buku);
    if (temp == NULL) {
        printf("(Belum ada buku)\n");
        printf("Tekan sembarang tombol untuk kembali...");
        getch();
        return;
    } else {
        while (temp != NULL) {
            printf("Judul: %s (Stok: %d)\n", Judul(temp), Stock(temp));
            temp = next(temp);
        }
        printf("=====================\n\n");
    }
    
    // Cek buku yang dikembalikan
    readBookName(&judul);
    book = Findbook(*buku, judul);
    
    if (book == NULL){
        printf("Buku dengan judul '%s' tidak ditemukan.\n", judul);
        free(judul);
        printf("Tekan sembarang tombol untuk kembali...");
        getch();
        return;
    }
    
    // Baca data peminjam
    readPersonName(&username);
    
    // Kembalikan buku (tambah stok)
    Stock(book)++;
    
    printf("Buku '%s' telah dikembalikan oleh '%s'.\n", judul, username);
    printf("Stok buku sekarang: %d\n", Stock(book));
    
    free(judul);
    free(username);
    
    printf("Tekan sembarang tombol untuk kembali...");
    getch();
}
