/* 
	File name	: linked.c
  	Made by		: Muhammad Nabil Syauqi Rasyiq
   	Date		: 30 March 2025
  	Description	: Implementation of linked list supporting both int and char* types
*/

#include "linked.h"

/*========================================================*/
/*==================== MAIN FUNCTIONS ====================*/
/*========================================================*/

boolean isEmpty(address P) {
    return (P == Nil);
}

boolean ListEmpty(List L) {
    return (First(L) == Nil);
}

void CreateAddress(address *P) {
    *P = Nil;
}

void CreateList(List *L) {
    First(*L) = Nil;
}


address alokasi(infotype info, DataType type) {
    address P = (address) malloc(sizeof(ElmtList));
    switch (type)
    {
        case TYPE_INTEGER:
            if (P != Nil) {
                info_integer(P) = info.integer;
                next(P) = Nil;
            }
            return P;
        case TYPE_STRING:
            if (P != Nil) {
                info_string(P) = strdup(info.str); // Deep copy menggunakan strdup
                if (info_string(P) == NULL) {
                    free(P); // mendealokasikan node bila gagal mengcopy string
                    return Nil;
                }
                next(P) = Nil;
            }
            return P;
        case TYPE_STRUCT:
            return alokasi_struct(info.strct);
        default:
            return Nil;
    }
}

void dealokasi(address P) {
    if (P != Nil) {
        if(Type(P) == TYPE_STRING){
            if (info_string(P) != NULL) {
                free(info_string(P)); // mendealokasikan String literal
            }
        }else if(Type(P) == TYPE_STRUCT){
            dealokasi_struct(P);
        }
        next(P) = Nil; // Pencegahan jiak next(P) belum Nil
        free(P);
    }
}

/*=======================================================*/
/*================= INSERTION FUNCTIONS =================*/
/*=======================================================*/

void InsertFirst(address *P, address newNode) {
    next(newNode) = *P;
    *P = newNode;
}

void InsertLast(address *P, address newNode) {
    if (*P == Nil) {
        *P = newNode;
    } else {
        address last = *P;
        while (next(last) != Nil) {
            last = next(last);
        }
        next(last) = newNode;
    }
}

void InsertAfter(address *pBef, address PNew) {
    next(PNew) = next(*pBef);
    next(*pBef) = PNew;
}

void InsertBefore(address *pAft, address *p, address PNew) {
    
    if (*pAft == *p) {
    	// jika pAft elemen pertama
        next(PNew) = *p;
        *p = PNew;
    } else {
        address prev = *p;
        while (next(prev) != *pAft) {
            prev = next(prev);
        }
        next(PNew) = *pAft;
        next(prev) = PNew;
    }
}

void insert_value_first(address *P, infotype info, DataType type) {
    address newNode = alokasi(info, type);
    if (newNode != Nil){
        InsertFirst(&(*P), newNode);
    }
}


void insert_value_last(address *P, infotype info, DataType type) {
    address newNode = alokasi(info, type);
    if (newNode != Nil) {
        InsertLast(&(*P), newNode);
    }
}

void insert_value_after(address *P, infotype before, infotype info, DataType type_before, DataType type_insert) {
    if (*P != Nil) {
        boolean found = false;
        address current = *P;
        while(current != Nil && !found) {
            if(current->type == type_before) {
                switch (type_before) {
                    case TYPE_INTEGER:
                        if (current->info.integer == before.integer) {
                            found = true;
                        }
                        break;
                        
                    case TYPE_STRING:
                        if (strcmp(current->info.str, before.str) == 0) {
                            found = true;
                        }
                        break;
                        
                    case TYPE_STRUCT:
                        if (compare_struct(info_struct(current), before.strct) == 0) {
                            found = true;
                        }
                        break;
                        
                    default:
                        return;
                }
            }
            current = next(current);
        }
        
        if (current != Nil) { // Jika node After berhasil ditemukan
            address newNode = alokasi(info, type_insert);
            if (newNode != Nil) {
                InsertAfter(&current, newNode);
            }
        }
    }
}

void insert_value_before(address *P, infotype after, infotype info, DataType type_after, DataType type_insert) {
    if (*P != Nil) {
        boolean found = false;
        address current = *P;
        while(current != Nil && !found) {
            if(current->type == type_after) {
                switch (type_after) {
                    case TYPE_INTEGER:
                        if (current->info.integer == after.integer) {
                            found = true;
                        }
                        break;
                        
                    case TYPE_STRING:
                        if (strcmp(current->info.str, after.str) == 0) {
                            found = true;
                        }
                        break;
                        
                    case TYPE_STRUCT:
                        if (compare_struct(info_struct(current), after.strct) == 0) {
                            found = true;
                        }
                        break;
                        
                    default:
                        return;
                }
            }
            current = next(current);
        }
        
        if (current != Nil) { // Jika node After berhasil ditemukan
            address newNode = alokasi(info, type_insert);
            if (newNode != Nil) {
                InsertBefore(&current, P, newNode);
            }
        }
    }
}

/*========================================================*/
/*================== DELETION FUNCTIONS ==================*/
/*========================================================*/

void delete_first(address *P, infotype *info) {
    if (*P != Nil) {
        address temp = *P;
        
        if (info != NULL) {
            *info = temp->info;
        }
        
        *P = next(temp);
        
        if (temp->type == TYPE_STRING) {
            info_string(temp) = Nil;
        } else if (temp->type == TYPE_STRUCT) {
            info_struct(temp) = Nil;
        } else if (temp->type == TYPE_BOOK) {
            info_buku(temp) = Nil;
        }
        
        dealokasi(temp);
    }
}

void delete_last(address *P, infotype *info){
    if (*P != Nil) {
        address last = *P;
        address prec = Nil;

        while (next(last) != Nil) {
            prec = last;
            last = next(last);
        }

        *info = last->info;
        if (prec == Nil) {
            *P = Nil;
        } else {
            next(prec) = Nil;
        }
        
        if (last->type == TYPE_STRING){
            info_string(last) = Nil;
        }
        dealokasi(last);
    }
}

void delete_by_value(address *P, infotype info, DataType type) {
    address head = *P;
    address temp;
        
    switch (type) {
        case TYPE_INTEGER:
            while (head != Nil && info_integer(next(head)) != info.integer) {
                head = next(head);
            }
            break;
                
        case TYPE_STRING:
            while (head != Nil && strcmp(info_string(next(head)), info.str) != 0) {
                head = next(head);
            }
            break;
                
        case TYPE_STRUCT:
            while (head != Nil && compare_struct(info_struct(next(head)), info.strct) != 0) {
                head = next(head);
            }
            break;
        default:
            return;
    }
    temp = next(head);
    next(head) = next(temp);
    if (temp != Nil) {
        if (temp->type == TYPE_STRING){
            info_string(temp) = Nil;
        }
        dealokasi(temp);
    }
}

void clear_list(address *P) {
    if (P == NULL || *P == NULL) {
        return;
    }
    
    infotype dummy_info;
    
    while (*P != Nil) {
        delete_first(P, &dummy_info);
    }
    *P = Nil;
}

/*=======================================================*/
/*================== DISPLAY FUNCTIONS ==================*/
/*=======================================================*/

void print_info(address P) {
    if (P != Nil) {
        switch (P->type)
        {
            case TYPE_INTEGER:
                printf("%d", info_integer(P));
                break;

            case TYPE_STRING:
                printf("%s", info_string(P));
                break;

            case TYPE_STRUCT:
                print_struct(info_struct(P));
                break;
            
            default:
                return;
        }
    }
}

void print_list(List L) {
    if (ListEmpty(L)) {
        printf("List Kosong\n");
    } else {
        address P = First(L);
        while (P != Nil) {
            print_info(P);
            P = next(P);
            if (P != Nil) {
                printf(" -> ");
            }
        }
        printf("\n");
    }
}
/*================================================================*/
/*================== COUNT AND SEARCH FUNCTIONS ==================*/
/*================================================================*/

int count_list(List L) {
    int count = 0;
    address P = First(L);
    
    while (P != Nil) {
        count++;
        P = next(P);
    }
    
    return count;
}

address search_prec(List L, infotype info) {
    if (ListEmpty(L)) {
        return Nil;
    }
    
    address P = First(L);
    switch (P->type)
    {
        case TYPE_INTEGER:
            if (info_integer(P) == info.integer) {
                return Nil;
            }
            break;
        case TYPE_STRING:
            if (strcmp(info_string(P), info.str) == 0) {
                return Nil;
            }
            break;
        case TYPE_STRUCT:
            if (compare_struct(info_struct(P), info.strct) == 0) {
                return Nil;
            }
            break;
        default:
            break;
    }
    while (next(P) != Nil) {
        switch (next(P)->type) 
        {
            case TYPE_INTEGER:
                if (info_integer(next(P)) == info.integer) {
                    return P;
                }
                break;
            case TYPE_STRING:
                if (strcmp(info_string(next(P)), info.str) == 0) {
                    return P;
                }
                break;
            case TYPE_STRUCT:
                if (compare_struct(info_struct(next(P)), info.strct) == 0) {
                    return P;
                }
                break;
            default:
                break;
        }
        P = next(P);
    }
    
    return Nil;
}

address search_by_value(address P, infotype info) {
    while (P != Nil) {
        switch (P->type) 
        {
            case TYPE_INTEGER:
                if (info_integer(P) == info.integer) {
                    return P;
                }
                break;
            case TYPE_STRING:
                if (strcmp(info_string(P), info.str) == 0) {
                    return P;
                }
                break;
            case TYPE_STRUCT:
                if (compare_struct(info_struct(P), info.strct) == 0) {
                    return P;
                }
                break;
            default:
                break;
        }
        P = next(P);
    }
    return Nil; // mereturn Nil jika tidak ditemukan
}

/*================================================================*/
/*===================== ADDITIONAL FUNCTIONS =====================*/
/*================================================================*/

address get_reverse_list(List L) {
    if (ListEmpty(L)) {
        return Nil;
    }
    
    address result = Nil;
    address P = First(L);
    address newNode;
    
    while (P != Nil) {
        address newNode = alokasi(P->info, P->type); 
        if (newNode != Nil) {
            InsertFirst(&result, newNode);
        }
        
        P = next(P);
    }
    return result;
}


void reverse_list(List *L) {
    if (!ListEmpty(*L)) {
        address reversed = get_reverse_list(*L);
        
        // Hapus List yang belum di reverse
        clear_list(&First(*L));

        // set list dengan list yang sudah di reverse
        First(*L) = reversed;
    }
}

void copy_list(List L1, List *L2) {
    CreateList(L2);
    
    if (!ListEmpty(L1)) {
        address P = First(L1);
        
        while (P != Nil) {
            address newNode = alokasi(P->info, P->type); // Alokasikan node baru
            if (newNode != Nil) {
                InsertLast(&First(*L2), newNode); // Masukkan node baru ke list L2
            }
            P = next(P);
        }
    }
}

infotype get_front_value(List L) {
    if (ListEmpty(L)) {
        return; 
    }
    address P = First(L);
    return info(P); 
}

infotype get_tail_value(List L) {
    if (ListEmpty(L)) {
        return;
    }
    address P = First(L);
    while (next(P) != Nil) {
        P = next(P);
    }
    return info(P);
}

/*=================================================================*/
/*================== IMPLEMENTATION STURCT MODUL ==================*/
/*=================================================================*/
address alokasi_struct(Struct data) {
    address P = (address)malloc(sizeof(ElmtList));
    if (P != Nil) {
        info_struct(P) = data;
        next(P) = Nil;
    }
    return P;
}

void dealokasi_struct(address P) {
    if (P != Nil) {
        if (info_struct(P) != NULL) {
            if (info_struct(P)->username != NULL) {
                free(info_struct(P)->username);
                info_struct(P)->username = NULL;  
            }
            free(info_struct(P)); 
        }
        
        next(P) = Nil;
        free(P);
    }
}

void print_struct(Struct data) {
    if (data != NULL) {
        printf("Username: %s, Role: %d", data->username, data->type);
    }
}

int compare_struct(Struct data1, Struct data2) {
    if (data1 == NULL || data2 == NULL) {
        return -1; // return -1 jika salah satu struct kosong
    }
    
    if (strcmp(data1->username, data2->username) == 0 && data1->type == data2->type) {
        return 0; // return 0 jika sama
    } else {
        return -1; // return -1 jika tidak sama
    }
}

/*================================================================*/
/*======================= KHUSUS BOOK DATA =======================*/
/*================================================================*/
address AlokasiPbook(Pbook data) {
    address P = (address)malloc(sizeof(ElmtList));
    if (P != Nil) {
        info_buku(P) = data;
        Type(P) = TYPE_BOOK;
        next(P) = Nil;
    }
    return P;
}

void DeAlokasiPbook(address P) {
    if (P != Nil) {
        if (info_buku(P) != NULL) {
            if (info_buku(P)->judul != NULL) {
                free(info_buku(P)->judul);
                info_buku(P)->judul = NULL;
            }
            free(info_buku(P));  
            info_buku(P) = NULL;  
        }
        
        next(P) = Nil; 
        free(P);
    }
}

void InsertFVPbook(address *P, Pbook info) {
    address newNode = AlokasiPbook(info);
    if (newNode != Nil) {
        InsertFirst(P, newNode);
    }
}

void InsertLVPbook(address *P, Pbook info) {
    address newNode = AlokasiPbook(info);
    if (newNode != Nil) {
        InsertLast(P, newNode);
    }
}

void DeleteFirstPbook(List *L, Pbook *info) {
    if (!ListEmpty(*L)) {
        address P = First(*L);
        *info = info_buku(P);
        First(*L) = next(P);
        DeAlokasiPbook(P);
    }
}

void DeleteLastPbook(List *L, Pbook *info) {
    if (!ListEmpty(*L)) {
        address last = First(*L);
        address prec = Nil;
        
        while (next(last) != Nil) {
            prec = last;
            last = next(last);
        }
        
        *info = info_buku(last);
        
        if (prec == Nil) { // Jika hanya berisi Satu elemen, maka list kosong
            First(*L) = Nil;
        } else {
            next(prec) = Nil;
        }
        
        DeAlokasiPbook(last);
    }
}

void DeleteByVPbook(List *L, char *judul) {
    if (!ListEmpty(*L)) {
        address P = First(*L);
        address temp;
        
        if (strcmp(info_buku(P)->judul, judul) == 0) {
            First(*L) = next(P);
            DeAlokasiPbook(P);
            return;
        }
        
        while (next(P) != Nil) {
            if (strcmp(info_buku(next(P))->judul, judul) == 0) {
                temp = next(P);
                next(P) = next(temp);
                DeAlokasiPbook(temp);
                return;
            }
            P = next(P);
        }
    }
}

address SearchByVPbook(address P, char *judul) {
    while (P != Nil) {
        if (P->type == TYPE_BOOK && strcmp(info_buku(P)->judul, judul) == 0) {
            return P;
        }
        P = next(P);
    }
    return Nil;
}

void printInfoPbook(List L) {
    if (ListEmpty(L)) {
        printf("List Kosong\n");
    } else {
        address P = First(L);
        printf("Judul Buku: %s Stock: %d\n", 
               info_buku(P)->judul, info_buku(P)->stock);
        P = next(P);
        
        while (P != Nil) {
            printf(" Judul Buku: %s Stock: %d", 
                   info_buku(P)->judul, info_buku(P)->stock);
            P = next(P);
        }
        printf("\n");
    }
}

Pbook GetFrontValuePbook(List L) {
    if (ListEmpty(L)) {
        return NULL; // return NULL jika kosong
    }
    
    return info_buku(First(L));
}

Pbook GetTailValuePbook(List L) {
    if (ListEmpty(L)) {
        return NULL; // return NULL jika kosong 
    }
    
    address P = First(L);
    
    while (next(P) != Nil) {
        P = next(P);
    }
    
    return info_buku(P);
}

void print_borrowed_book(List L){
    boolean dipinjam = false;
    if (ListEmpty(L)) {
        printf("List Kosong\n");
    } else {
        address P = First(L);
        while (P != Nil) {
            if(info_buku(P)->pinjam > 0) {
                dipinjam = true;
                printf("Judul Buku: %s Stock: %d\n", 
                       info_buku(P)->judul, info_buku(P)->pinjam);
            }
            P = next(P);
        }
        if(!dipinjam){
            printf("Tidak ada buku yang sedang dipinjam");
        }
    }
}


/*=================================================================*/
/*=================== KHUSUS Library MANAGEMENT ===================*/
/*=================================================================*/

void create_library(library *Perpustakaan) {
    (*Perpustakaan)->data = (List *)malloc(sizeof(List));
    if ((*Perpustakaan)->data == NULL) {
        printf("Gagal mengalokasikan memori untuk data perpustakaan\n");
        return;
    }
    
    CreateList((*Perpustakaan)->data);
    (*Perpustakaan)->next = Nil;
}

boolean is_queue_exits(library Perpustakaan){
    return (Perpustakaan->next != Nil);
}

List *insert_queue(library *Perpustakaan, address *buku) {
    if (*Perpustakaan == Nil) return Nil;

    library new_queue = (library)malloc(sizeof(elmtlib));
    if (new_queue == NULL) {
        printf("Gagal mengalokasikan memori untuk antrian baru\n");
        return Nil;
    }
    
    // Alokasi memori untuk data
    new_queue->data = (List *)malloc(sizeof(List));
    if (new_queue->data == NULL) {
        printf("Gagal mengalokasikan memori untuk data antrian\n");
        free(new_queue);
        return Nil;
    }
    
    CreateList(new_queue->data);
    new_queue->data->First = *buku;
    new_queue->next = Nil;

    if ((*Perpustakaan)->next == Nil) {
        (*Perpustakaan)->next = new_queue;
        return new_queue->data;
    }

    library temp = *Perpustakaan;
    while (temp->next != Nil) {
        temp = temp->next;
    }
    temp->next = new_queue;
    return new_queue->data;
}


void delete_queue_by_book(library *Perpustakaan, char *judul){
    if((*Perpustakaan) == Nil) return;
    if((*Perpustakaan)->next == Nil) return;

    library temp = (*Perpustakaan)->next;
    library prev;
    while(temp != Nil){
        if(temp->data->First != Nil){
            if(strcmp(get_judul_antrian(temp->data->First), judul) == 0){
                break;
            }
        }
        prev = temp;
        temp = temp->next;
    }
    prev->next = temp->next;
    clear_list(&(temp->data->First));
    free(temp);
}

string get_judul_antrian(address P) {
    if (P == Nil) return NULL;
    
    while (P != Nil && P->type != TYPE_BOOK) {
        P = next(P);
    }
    
    if (P != Nil && P->type == TYPE_BOOK) {
        return info_buku(P)->judul;
    }
    
    return NULL;
}

void delete_all_queue(library *Perpustakaan) {
    if (Perpustakaan == NULL || *Perpustakaan == NULL || (*Perpustakaan)->next == Nil) {
        return;
    }
    
    library current, next_lib;
    current = (*Perpustakaan)->next;
    
    (*Perpustakaan)->next = Nil;
    
    // Bebaskan setiap node antrian
    while (current != Nil) {
        next_lib = current->next;
        
        // Hapus list data terlebih dahulu jika ada
        if (current->data != NULL) {
            clear_list(&(current->data->First));
            free(current->data);  // Bebaskan pointer data juga
        }
        
        free(current);  // Bebaskan node antrian
        current = next_lib;
    }
}

List *search_queue_by_book(library Perpustakaan, char *judul){
    while(Perpustakaan != Nil){
        if(Perpustakaan->data->First != Nil){
            if(strcmp(get_judul_antrian(Perpustakaan->data->First), judul) == 0){
                return (Perpustakaan->data);
            }
        }
        Perpustakaan = Perpustakaan->next;
    }
    return Nil;
}

void deallocated_library(library *Perpustakaan) {
    if (Perpustakaan == NULL || *Perpustakaan == NULL) {
        return;
    }
    
    // Hapus semua antrian terlebih dahulu
    delete_all_queue(Perpustakaan);
    
    // Hapus daftar buku jika data masih ada
    if ((*Perpustakaan)->data != NULL) {
        clear_list(&((*Perpustakaan)->data->First));
        free((*Perpustakaan)->data);  // Bebaskan pointer data juga
    }
    
    // Bebaskan perpustakaan itu sendiri
    free(*Perpustakaan);
    *Perpustakaan = Nil;
}

