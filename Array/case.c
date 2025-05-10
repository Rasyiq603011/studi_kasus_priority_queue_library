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
    int indeksbook;
    Struct orang;
    
    // Tampilkan daftar buku yang tersedia
    system("cls");
    printf("===== Daftar Buku Tersedia =====\n");
    if (isEmptyBook(*buku)) {
        printf("(Belum ada buku)\n");
        printf("Tekan sembarang tombol untuk kembali...");
        getch();
        return;
    } else {
        printAllBook(*buku);
        printf("==============================\n\n");
    }
    
    // Cek buku yang ingin dipinjam
    readBookName(&judul);
    indeksbook = Findbook(*buku, judul);
    
    if (indeksbook == -1){
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
//    printf("keluar dari get role");
    
    // Masukkan ke antrean buku
    address *antri = &(buku->Head[indeksbook]->antrian);

    InsertLastV(antri, orang);
    
    printf("Peminjam '%s' berhasil ditambahkan ke antrean buku '%s'.\n", username, judul);
    
    free(judul);
    printf("Tekan sembarang tombol untuk kembali...");
    getch();
}

int proses_prioritas(address *Antrian, int prioritas, int *Stock, int *pinjam){
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
                (*pinjam)++;
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
    
    if (isEmptyBook(*book)) {
        printf("Belum ada buku yang tersedia.\n");
        printf("Tekan sembarang tombol untuk kembali...");
        getch();
        return;
    }
    
    printf("===== Memproses Antrian Peminjaman =====\n");
    
    int j;
    
    for(i = 0; i < book->size; i++){
        Pbook temp = book->Head[i];
        printf("Memproses buku '%s':\n", temp->judul);
        
        if (isEmpty(temp->antrian)) {
            printf("- Tidak ada antrian peminjam untuk buku ini.\n");
        } else {
            // Proses berdasarkan prioritas (1=Dosen, 2=Mahasiswa, 3=Umum)
            for(j = 1; j <= 3; j++){
                if (temp->stock <= 0) {
                    printf("- Stok buku habis, tidak dapat memproses antrian lebih lanjut.\n");
                    break;
                }
                
                if(!proses_prioritas(&(temp->antrian), j, &(temp->stock), &(temp->pinjam))){
                    printf("- Stok buku habis, tidak dapat memproses antrian lebih lanjut.\n");
                    break;
                }
            }
        }
        printf("\n");
    }
    
    printf("Proses antrian selesai.\n");
    printf("Tekan sembarang tombol untuk kembali...");
    getch();
}

void Daftar_Pengembalian(ListBook *buku){
    char* judul;
    char* username;
    int indeks;
    
    // Tampilkan daftar buku
    system("cls");

    printf("===== Daftar Buku =====\n");
    if (isEmptyBook(*buku)) {
        printf("(Belum ada buku)\n");
        printf("Tekan sembarang tombol untuk kembali...");
        getch();
        return;
    } else {
        printAllBook(*buku);
        printf("=====================\n\n");
    }
    
    // Cek buku yang dikembalikan
    readBookName(&judul);
    indeks = Findbook(*buku, judul);
    
    if (indeks == -1){
        printf("Buku dengan judul '%s' tidak ditemukan.\n", judul);
        free(judul);
        printf("Tekan sembarang tombol untuk kembali...");
        getch();
        return;
    }
    
    // Baca data peminjam
    readPersonName(&username);
    
    // Kembalikan buku 
    buku->Head[indeks]->pinjam--;
    buku->Head[indeks]->stock++;
    
    printf("Buku '%s' telah dikembalikan oleh '%s'.\n", judul, username);
    printf("Stok buku sekarang: %d\n", buku->Head[indeks]->stock );
    
    free(judul);
    free(username);
    
    printf("Tekan sembarang tombol untuk kembali...");
    getch();
}
