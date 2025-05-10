/*  
	File name	: CaseBook.c
    Made by		: Muhammad Nabil Syauqi Rasyiq
    Date		: 2 April 2025
    Description	: Implementation of linked list Casebook.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CaseBook.h"

int i; // Variabel Perulangan

/*========================================================*/
/*==================== MAIN FUNCTIONS ====================*/
/*========================================================*/

boolean ListBookEmpty(ListBook C) {
    return (Head(C) == NULL);
}

void CreatePbook(Pbook *A) {
	*A = NULL;
}

void CreatebookList(ListBook *C) {
    Head(*C) = NULL;
}

Pbook Constructor(char* judul, int stock) {
    Pbook newNode = (Pbook) malloc(sizeof(BookData));
    if (newNode != NULL) {
    	// set Judul
        Judul(newNode) = strdup(judul); // Deep copy of string
        if (Judul(newNode) == NULL) {
            free(newNode);
            return NULL;
        }
        // set stock
        Stock(newNode) = stock;
        // set antrian
        CreateAddress(&(Antrian(newNode)));
        // set next
        next(newNode) = NULL;
    }
    return newNode;
}

void Destructor(Pbook A) {
    if (A != NULL) {
        if (A->judul != NULL) {
            free(A->judul);
        }
        if (!isEmpty(Antrian(A))) {
        	List temp;
        	CreateList(&temp,TYPE_STRUCT);
        	First(temp) = Antrian(A);
            ClearList(&temp);
        }
        free(A);
    }
}

/*=======================================================*/
/*================= INSERTION FUNCTIONS =================*/
/*=======================================================*/

void InsertAwal(Pbook *A, Pbook newNode) {
    if (newNode != NULL) {
        next(newNode) = *A;
        *A = newNode;
    }
}

void InsertAkhir(Pbook *A, Pbook newNode) {
    if (*A == NULL) {
        InsertAwal(&(*A), newNode); 
    } else {
        Pbook temp = *A;
        while (next(temp) != NULL) {
            temp = next(temp);
        }
        next(temp) = newNode;
    }
}

void InsertSetelah(Pbook *pBef, Pbook PNew) {
    if (*pBef != NULL && PNew != NULL) {
        next(PNew) = next(*pBef);
        next(*pBef) = PNew;
    }
}

void InsertSebelum(Pbook *pAft, Pbook *p, Pbook PNew) {
    if (PNew != NULL) {
        if (*p == *pAft) {
            InsertAwal(&(*p), PNew);
        } else {
            Pbook temp = *p;
            while (temp != NULL && next(temp) != *pAft) {
                temp = next(temp);
            }
            if (temp != NULL) {
                InsertSetelah(&temp, PNew);
            }
        }
    }
}

void InsertAwalV(Pbook *P, char *judul, int stock) {
    Pbook newNode = Constructor(judul, stock);
    if (newNode != NULL) {
        InsertAwal(&(*P), newNode);
    }
}

void InsertAkhirV(Pbook *P, char *judul, int stock) {
    Pbook newNode = Constructor(judul, stock);
    if (newNode != NULL) {
        InsertAkhir(&(*P), newNode);
    }
}

/*========================================================*/
/*================== DELETION FUNCTIONS ==================*/
/*========================================================*/

void DeleteAwal(ListBook *C) {
    if (!ListBookEmpty(*C)) {
        Pbook temp = Head(*C);
        Head(*C) = next(temp);
        Destructor(temp);
    }
}

void DeleteAkhir(ListBook *C) {
    if (!ListBookEmpty(*C)) {
        if (next(Head(*C)) == NULL) {
            DeleteAwal(C);
        } else {
            Pbook last = Head(*C);
            Pbook prev = NULL;
            
            while (next(last) != NULL) {
                prev = last;
                last = next(last);
            }
            
            next(prev) = NULL;
            Destructor(last);
        }
    }
}

void DeleteByName(ListBook *C, char* judul) {
    if (!ListBookEmpty(*C)) {
        Pbook temp = Head(*C);
        
        if (strcmp(Judul(temp), judul) == 0) {
            DeleteAwal(C);
        } else {
            Pbook prev = temp;
            temp = next(temp);
            
            while (temp != NULL && strcmp(Judul(temp), judul) != 0) {
                prev = temp;
                temp = next(temp);
            }
            
            if (temp != NULL) {
                next(prev) = next(temp);
                Destructor(temp);
            }
        }
    }
}

void ClearListBook(ListBook *C) {
    while (!ListBookEmpty(*C)) {
        DeleteAwal(C);
    }
}

/*================================================================*/
/*===================== ADDITIONAL FUNCTIONS =====================*/
/*================================================================*/

Pbook Findbook(ListBook C, char* judul) {
    Pbook temp = Head(C);
    while (temp != NULL) {
        if (strcmp(Judul(temp), judul) == 0) {
            return temp;
        }
        temp = next(temp);
    }
    return NULL;
}

void PrintAllBookData(ListBook C) {
    Pbook temp = Head(C);
    printf("List of Cities:\n");
    if (temp == NULL) {
        printf("(Empty List)\n");
    } else {
        while (temp != NULL) {
            PrintBookData(temp);
            temp = next(temp);
        }
    }
}

void PrintBookData(Pbook bookNode) {
    if (bookNode != NULL) {
        printf("book: %s\n", Judul(bookNode));
        
        if (!isEmpty(Antrian(bookNode))) {
            printf("Names in %s: ", Judul(bookNode));
            List temp;
        	CreateList(&temp,TYPE_STRUCT);
        	First(temp) = Antrian(bookNode);
            PrintList(temp);
            }
        else {
            printf("No names in this book.\n");
        }
    }else {
        printf("book node is NULL.\n");
    }
}

int countBook(ListBook C){
	int bookCount = 0;
    Pbook book = Head(C);
    while (book != NULL) {
        bookCount++;
        book = next(book);
    }
    return bookCount;
}

int countNameInBook(Pbook bookNode) {
    if (bookNode == NULL ||  isEmpty(Antrian(bookNode))) {
        return 0;
    }
	
	List temp;
	CreateList(&temp,TYPE_STRUCT);
	First(temp) = Antrian(bookNode);
    int count = CountList(temp);
    return count;
}

int CountTotalNames(Pbook A) {
    int total = 0; 
    Pbook temp = A;
    
    while (temp != NULL) {
        total += countNameInBook(temp);
        temp = next(temp);
    }
    
    return total;
}

