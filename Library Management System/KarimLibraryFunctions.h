//
//  KarimLibraryFunctions.h
//  Library Management System
//

#ifndef KarimLibraryFunctions_h
#define KarimLibraryFunctions_h

#include <stdio.h>
#include <stdbool.h>

#endif /* KarimLibraryFunctions_h */

struct BookRecord {
    char bookID[50];
    char bookCategory[50];
    char bookName[50];
    char bookAuthor[50];
    char bookRackNumber[50];
};

struct AdminRecord {
    char userName[50];
    char password[50];
};

void createTitle(char*);
void createList(char* bla[]);
void createMenuStructure(char*, char* arrayOfItems[]);

int chooseOptions(char*);

FILE* fileRecordSearch(char* fileName);

struct BookRecord askForBookDetails(struct BookRecord);

void addBooks(void);
void printBookRecord(void);
void editBooks(void);


void adminRegister(void);
bool adminCheckPass(void);
