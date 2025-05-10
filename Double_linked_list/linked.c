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

void CreateList(List *L, DataType type) {
    First(*L) = Nil;
    L->type = type;
}

address AlokasiInt(int info) {
    address P = (address) malloc(sizeof(ElmtList));
    if (P != Nil) {
        infoInt(P) = info;
        next(P) = Nil;
    }
    return P;
}

address AlokasiCharS(string info) {
    address P = (address) malloc(sizeof(ElmtList));
    if (P != Nil) {
        infoStr(P) = strdup(info); // Deep copy menggunakan strdup
        if (infoStr(P) == NULL) {
            free(P); // mendealokasikan node bila gagal mengcopy string
            return Nil;
        }
        next(P) = Nil;
    }
    return P;
}

void DeAlokasiInt(address P) {
    if (P != Nil) {
        next(P) = Nil; // Pencegahan jiak next(P) belum Nil
        free(P);
    }
}

void DeAlokasiCharS(address P) {
    if (P != Nil) {
        if (infoStr(P) != NULL) {
            free(infoStr(P)); // mendealokasikan String literal
        }
        next(P) = Nil; // Pencegahan jiak next(P) belum Nil
        free(P);
    }
}

void DeAlokasi(address P) {
    if (P != Nil) {
        next(P) = Nil; // Ensure next pointer is NULL before deallocation
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

void InsertFVInt(address *P, int info) {
    address newNode = AlokasiInt(info);
    if (newNode != Nil) {
        InsertFirst(&(*P), newNode);
    }
}

void InsertFVCharS(address *P, string info) {
    address newNode = AlokasiCharS(info);
    if (newNode != Nil) {
        InsertFirst(&(*P), newNode);
    }
}

void InsertLVInt(address *P, int info) {
    address newNode = AlokasiInt(info);
    if (newNode != Nil) {
        InsertLast(&(*P), newNode);
    }
}

void InsertLVCharS(address *P, string info) {
    address newNode = AlokasiCharS(info);
    if (newNode != Nil) {
        InsertLast(&(*P), newNode);
    }
}

void InsertAVInt(address *P, int Before, int info) {
    if (*P != Nil) {
        address current = *P;
        while (current != Nil && infoInt(current) != Before) {
            current = next(current);
        }
        
        if (current != Nil) { // Jika node Before berhasil ditemukan
            address newNode = AlokasiInt(info);
            if (newNode != Nil) {
                InsertAfter(&current, newNode);
            }
        }
    }
}

void InsertAVCharS(address *P, string Before, string info) {
    if (*P != Nil) {
        address current = *P;
        while (current != Nil && strcmp(infoStr(current), Before) != 0) {
            current = next(current);
        }
        
        if (current != Nil) { // Jika node Before berhasil ditemukan
            address newNode = AlokasiCharS(info);
            if (newNode != Nil) {
                InsertAfter(&current, newNode);
            }
        }
    }
}

void InsertBVInt(address *P, int After, int info) {
    if (*P != Nil) {
        address current = *P;
        while (current != Nil && infoInt(current) != After) {
            current = next(current);
        }
        
        if (current != Nil) { // Jika node After berhasil ditemukan
            address newNode = AlokasiInt(info);
            if (newNode != Nil) {
                InsertBefore(&current, P, newNode);
            }
        }
    }
}

void InsertBVCharS(address *P, string After, string info) {
    if (*P != Nil) {
        address current = *P;
        while (current != Nil && strcmp(infoStr(current), After) != 0) {
            current = next(current);
        }
        
        if (current != Nil) { // // Jika node After berhasil ditemukan
            address newNode = AlokasiCharS(info);
            if (newNode != Nil) {
                InsertBefore(&current, P, newNode);
            }
        }
    }
}

/*========================================================*/
/*================== DELETION FUNCTIONS ==================*/
/*========================================================*/

void DeleteFirstInt(List *L, int *info) {
    if (!ListEmpty(*L)) {
        address P = First(*L);
        *info = infoInt(P);
        First(*L) = next(P);
        DeAlokasiInt(P);
    }
}

void DeleteFirstCharS(List *L, string *info) {
    if (!ListEmpty(*L)) {
        address P = First(*L);
        *info = infoStr(P);
        infoStr(P) = NULL; // Memastikan sebelum didealokasikan infoStr tidak berisi string literal karena string masih digunakan 
        First(*L) = next(P);
        DeAlokasiCharS(P);
    }
}

void DeleteLastInt(List *L, int *info) {
    if (!ListEmpty(*L)) {
        address last = First(*L);
        address prec = Nil;
        
        while (next(last) != Nil) {
            prec = last;
            last = next(last);
        }
        
        *info = infoInt(last);
        
        if (prec == Nil) { // Jika hanya berisi Satu elemen, maka list kosong
            First(*L) = Nil;
        } else {
            next(prec) = Nil;
        }
        
        DeAlokasiInt(last);
    }
}

void DeleteLastCharS(List *L, string *info) {
    if (!ListEmpty(*L)) {
        address last = First(*L);
        address prec = Nil;
        
        while (next(last) != Nil) {
            prec = last;
            last = next(last);
        }
        
        *info = infoStr(last);
        infoStr(last) = NULL; // Memastikan sebelum didealokasikan infoStr tidak berisi string literal karena string masih digunakan 
        
        if (prec == Nil) { // Jika hanya berisi Satu elemen, maka list kosong
            First(*L) = Nil;
        } else {
            next(prec) = Nil;
        }
        
        DeAlokasiCharS(last);
    }
}

void DeleteByVInt(List *L, int info) {
    if (!ListEmpty(*L)) {
        address P = First(*L);
        address temp;
        
        // jika value ada di posisi First
        if (infoInt(P) == info) {
            First(*L) = next(P);
            DeAlokasiInt(P);
            return;
        }
        
        // cari nilai info lalu delete
        while (next(P) != Nil) {
            if (infoInt(next(P)) == info) {
                temp = next(P);
                next(P) = next(temp);
                DeAlokasiInt(temp);
                return;
            }
            P = next(P);
        }
    }
}

void DeleteByVCharS(List *L, string info) {
    if (!ListEmpty(*L)) {
        address P = First(*L);
        address temp;
        
        // jika value ada di posisi First
        if (strcmp(infoStr(P), info) == 0) {
            First(*L) = next(P);
            DeAlokasiCharS(P);
            return;
        }
        
        // Cari nilai info lalu delete
        while (next(P) != Nil) {
            if (strcmp(infoStr(next(P)), info) == 0) {
                temp = next(P);
                next(P) = next(temp);
                DeAlokasiCharS(temp);
                return;
            }
            P = next(P);
        }
    }
}

void ClearList(List *L) {
    address P, temp;
    P = First(*L);
    
    // dealokasi terlebih dahulu nilai yang tidak ditunjuk First(*L)
    while (P != Nil) {
        temp = next(P);
        
        // dealokasi sesuai tipe list
        if (L->type == TYPE_INT) {
            DeAlokasiInt(P);
        } else if (L->type == TYPE_STRING) {
            DeAlokasiCharS(P);
        } else if (L->type == TYPE_STRUCT) {
            DeAlokasiStruct(P);
        }
        
        P = temp;
    }
    
    First(*L) = Nil;
}

/*=======================================================*/
/*================== DISPLAY FUNCTIONS ==================*/
/*=======================================================*/

void printInfoInt(List L) {
    if (ListEmpty(L)) {
        printf("List Kosong\n");
    } else {
        address P = First(L);
        printf("%d", infoInt(P));
        P = next(P);
        
        while (P != Nil) {
            printf(", %d", infoInt(P));
            P = next(P);
        }
        printf("\n");
    }
}

void printInfoCharS(List L) {
    if (ListEmpty(L)) {
        printf("List Kosong\n");
    } else {
        address P = First(L);
        printf("%s", infoStr(P));
        P = next(P);
        
        while (P != Nil) {
            printf(", %s", infoStr(P));
            P = next(P);
        }
        printf("\n\n");
    }
}

/*================================================================*/
/*================== COUNT AND SEARCH FUNCTIONS ==================*/
/*================================================================*/

int CountList(List L) {
    int count = 0;
    address P = First(L);
    
    while (P != Nil) {
        count++;
        P = next(P);
    }
    
    return count;
}

address SearchPrec(List L, int info) {
    if (ListEmpty(L) || L.type != TYPE_INT) {
        return Nil;
    }
    
    address P = First(L);
    
    // jika nilai info berada di node dengan posisi first
    if (infoInt(P) == info) {
        return Nil;
    }
    
    while (next(P) != Nil) {
        if (infoInt(next(P)) == info) {
            return P;
        }
        P = next(P);
    }
    
    return Nil; // mereturn Nil jika tidak ditemukan
}

address SearchByVInt(List L, int info) {
    if (ListEmpty(L) || L.type != TYPE_INT) {
        return Nil;
    }
    
    address P = First(L);
    
    while (P != Nil) {
        if (infoInt(P) == info) {
            return P;
        }
        P = next(P);
    }
    
    return Nil; // mereturn Nil jika tidak ditemukan
}

address SearchByVCharS(List L, char* info) {
    if (ListEmpty(L) || L.type != TYPE_STRING) {
        return Nil;
    }
    
    address P = First(L);
    
    while (P != Nil) {
        if (strcmp(infoStr(P), info) == 0) {
            return P;
        }
        P = next(P);
    }
    
    return Nil; // mereturn Nil jika tidak ditemukan
}

/*================================================================*/
/*===================== ADDITIONAL FUNCTIONS =====================*/
/*================================================================*/

address getReverseList(List L) {
    if (ListEmpty(L)) {
        return Nil;
    }
    
    address result = Nil;
    address P = First(L);
    address newNode;
    
    while (P != Nil) {
        if (L.type == TYPE_INT) {
            newNode = AlokasiInt(infoInt(P));
        } else if (L.type == TYPE_STRING) {
            newNode = AlokasiCharS(infoStr(P));
        } else { // TYPE_STRUCT
            newNode = AlokasiStruct(info(P));
        }
        
        if (newNode != Nil) {
            InsertFirst(&result, newNode);
        }
        
        P = next(P);
    }
    
    return result;
}


void ReverseList(List *L) {
    if (!ListEmpty(*L)) {
        address reversed = getReverseList(*L);
        
        // Hapus List yang belum di reverse
        ClearList(L);
        
        // set list dengan list yang sudah di reverse
        First(*L) = reversed;
    }
}

void CopyList(List L1, List *L2) {
    CreateList(L2, L1.type);
    
    if (!ListEmpty(L1)) {
        address P = First(L1);
        
        while (P != Nil) {
            if (L1.type == TYPE_INT) {
                InsertLVInt(&(First(*L2)), infoInt(P));
            } else if (L1.type == TYPE_STRING) {
                InsertLVCharS(&(First(*L2)), infoStr(P));
            } else { // TYPE_STRUCT
                InsertLVStruct(&(First(*L2)), info(P));
            }
            P = next(P);
        }
    }
}

int GetFrontValueInt(List L) {
    if (ListEmpty(L) || L.type != TYPE_INT) {
        return 0; // return 0 jika kosong atau tipe list bukan integer
    }
    
    return infoInt(First(L));
}

string GetFrontValueCharS(List L) {
    if (ListEmpty(L) || L.type != TYPE_STRING) {
        return NULL; // return NULL jika kosong atau tipe list bukan String
    }
    
    return infoStr(First(L));
}

int GetTailValueInt(List L) {
    if (ListEmpty(L) || L.type != TYPE_INT) {
        return 0; // return 0 jika kosong atau tipe list bukan integer
    }
    
    address P = First(L);
    
    while (next(P) != Nil) {
        P = next(P);
    }
    
    return infoInt(P);
}

string GetTailValueCharS(List L) {
    if (ListEmpty(L) || L.type != TYPE_STRING) {
        return NULL; // return NULL jika kosong atau tipe list bukan String
    }
    
    address P = First(L);
    
    while (next(P) != Nil) {
        P = next(P);
    }
    
    return infoStr(P);
}



/*=================================================================*/
/*================== IMPLEMENTATION STURCT MODUL ==================*/
/*=================================================================*/

address AlokasiStruct(Struct data) {
    address P = (address)malloc(sizeof(ElmtList));
    if (P != Nil) {
        info(P) = data;
        next(P) = Nil;
    }
    return P;
}

void DeAlokasiStruct(address P) {
    if (P != Nil) {
        next(P) = Nil; 
        free(P);
    }
}

/*
Fungsi insert first untuk tipe Struct
*/
void InsertFVStruct(address *P, Struct info) {
    address newNode = AlokasiStruct(info);
    if (newNode != Nil) {
        InsertFirst(P, newNode);
    }
}

/*
Fungsi insert last untuk tipe Struct
*/
void InsertLVStruct(address *P, Struct info) {
    address newNode = AlokasiStruct(info);
    if (newNode != Nil) {
        InsertLast(P, newNode);
    }
}

/*
Fungsi insert after untuk tipe Struct
*/
void InsertAVStruct(address *P, Struct Before, Struct info) {
    if (*P != Nil) {
        address current = *P;
        // Cari node dengan nilai Struct yang sama (perbandingan ID)
        while (current != Nil && (info(current)->type != Before->type || 
                                 info(current)->username != Before->username)) {
            current = next(current);
        }
        
        if (current != Nil) { // Jika node Before berhasil ditemukan
            address newNode = AlokasiStruct(info);
            if (newNode != Nil) {
                InsertAfter(&current, newNode);
            }
        }
    }
}

/*
Fungsi insert before untuk tipe Struct
*/
void InsertBVStruct(address *P, Struct After, Struct info) {
    if (*P != Nil) {
        address current = *P;
        // Cari node dengan nilai Struct yang sama
        while (current != Nil && (info(current)->type != After->type ||
                                 info(current)->username != After->username)) {
            current = next(current);
        }
        
        if (current != Nil) { // Jika node After berhasil ditemukan
            address newNode = AlokasiStruct(info);
            if (newNode != Nil) {
                InsertBefore(&current, P, newNode);
            }
        }
    }
}

/*
Fungsi delete first untuk tipe Struct
*/
void DeleteFirstStruct(List *L, Struct *info) {
    if (!ListEmpty(*L)) {
        address P = First(*L);
        *info = info(P);
        First(*L) = next(P);
        DeAlokasiStruct(P);
    }
}

/*
Fungsi delete last untuk tipe Struct
*/
void DeleteLastStruct(List *L, Struct *info) {
    if (!ListEmpty(*L)) {
        address last = First(*L);
        address prec = Nil;
        
        while (next(last) != Nil) {
            prec = last;
            last = next(last);
        }
        
        *info = info(last);
        
        if (prec == Nil) { // Jika hanya berisi Satu elemen, maka list kosong
            First(*L) = Nil;
        } else {
            next(prec) = Nil;
        }
        
        DeAlokasiStruct(last);
    }
}

/*
Fungsi delete by value untuk tipe Struct
*/
void DeleteByVStruct(List *L, Struct info) {
    if (!ListEmpty(*L)) {
        address P = First(*L);
        address temp;
        
        // jika value ada di posisi First (perbandingan ID dan jenis)
        if (info(P)->type == info->type && info(P)->username == info->username) {
            First(*L) = next(P);
            DeAlokasiStruct(P);
            return;
        }
        
        // cari nilai info lalu delete
        while (next(P) != Nil) {
            if (info(next(P))->type == info->type && info(next(P))->username == info->username) {
                temp = next(P);
                next(P) = next(temp);
                DeAlokasiStruct(temp);
                return;
            }
            P = next(P);
        }
    }
}

/*
Fungsi print info untuk tipe Struct
*/
void printInfoStruct(List L) {
    if (ListEmpty(L)) {
        printf("List Kosong\n");
    } else {
        address P = First(L);
        printf("Username: %s Prioritas: %d", 
               info(P)->username, info(P)->type);
        P = next(P);
        
        while (P != Nil) {
            printf("|| Username: %s Prioritas: %d", 
                   info(P)->username, info(P)->type);
            P = next(P);
        }
        printf("\n");
    }
}

/*
Fungsi search untuk tipe Struct
*/
address SearchByVStruct(List L, Struct info) {
    if (ListEmpty(L) || L.type != TYPE_STRUCT) {
        return Nil;
    }
    
    address P = First(L);
    
    while (P != Nil) {
        if (info(P)->type == info->type && info(P)->username == info->username) {
            return P;
        }
        P = next(P);
    }
    
    return Nil; // mereturn Nil jika tidak ditemukan
}

/*
Fungsi get front value untuk tipe Struct
*/
Struct GetFrontValueStruct(List L) {
    if (ListEmpty(L) || L.type != TYPE_STRUCT) {
        return NULL; // return NULL jika kosong atau tipe list bukan Struct
    }
    
    return info(First(L));
}

/*
Fungsi get tail value untuk tipe Struct
*/
Struct GetTailValueStruct(List L) {
    if (ListEmpty(L) || L.type != TYPE_STRUCT) {
        return NULL; // return NULL jika kosong atau tipe list bukan Struct
    }
    
    address P = First(L);
    
    while (next(P) != Nil) {
        P = next(P);
    }
    
    return info(P);
}







