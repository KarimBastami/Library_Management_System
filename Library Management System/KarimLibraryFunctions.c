//
//  KarimLibraryFunctions.c
//  Library Management System
//


#include <string.h>
#include <stdbool.h>
#include "KarimLibraryFunctions.h"


// GUI Utilities
void createTitle(char* title){
    char* fullLine = "----------------------------------------------------------\n";
    int halfTitle = strlen(title) / 2;
    
    
    printf("%s", fullLine);
    
    for(int i = 0; i < ((strlen(fullLine) / 2) - (strlen(title))) + halfTitle; i++){
        printf(" ");
    }
    
    printf("%s\n", title);
    printf("%s", fullLine);
}



void createList(char* arrayOfItems[]){
    int arrayLength = 0;
    
    for (int i = 1; arrayOfItems[i] != NULL; i++) {
        arrayLength++;
    }
    
    for(int i = 0; i < arrayLength; i++){
        printf("%d: %s\n", i, arrayOfItems[i]);
    }
}



void createMenuStructure(char* title, char* arrayOfItems[]){
    
    createTitle(title);
    createList(arrayOfItems);
    createTitle("----------------------------------------------------------");
    
}



int chooseOptions(char* text){
    int chosenOption;
    
    printf("%s: ", text);
    scanf("%d", &chosenOption);
    
    return chosenOption;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////



struct BookRecord askForBookDetails(struct BookRecord book){
    
    char* categories[9] = {"Computer", "Electronics", "Electrical", "Civil", "Mechanical", "Architecture", "Back To Main Menu", "\0"};
    
    // create GUI options
    createMenuStructure("Select Categories", categories);
    
    // Check for chosen category
    switch (chooseOptions("Enter Your Choice")) {
        case 0:
            strcpy(book.bookCategory, "Computer");
            break;
            
        case 1:
            strcpy(book.bookCategory, "Electronics");
            break;
            
        case 2:
            strcpy(book.bookCategory, "Electrical");
            break;
            
        case 3:
            strcpy(book.bookCategory, "Civil");
            break;
            
        case 4:
            strcpy(book.bookCategory, "Mechanical");
            break;
            
        case 5:
            strcpy(book.bookCategory, "Architecture");
            break;
            
        case 6:
            strcpy(book.bookCategory, "No Result");
            break;
            
            
        default:
            break;
    }
    
    if(strcmp(book.bookCategory, "No Result") != 0){
        char something[50];
        
        // prompt the user for details using the book structure
        printf("ID: ");
        scanf("%s", book.bookID);
        
        gets(something);// for some reason xcode my IDE prints text warning the first time i use gets which is stored in book.bookName, so i made a variable to store the text from the warning before i ask for the name
        printf("Book Name: ");
        gets(book.bookName);
        
        printf("Author: ");
        gets(book.bookAuthor);
        
        printf("Rack Number: ");
        gets(book.bookRackNumber);
    }
    
    
    return book;
}



void addBooks(){
    FILE* bookFilePtr = NULL;
    char willRepeat = 'N';
    
    
    bookFilePtr = fopen("Book Records.txt", "a");
    
    do {
        // checks if the file is open
        if(bookFilePtr == NULL){
            printf("Failed to open file...\n");
            
        } else {
            struct BookRecord book;
            strcpy(book.bookCategory, "shit");
            strcpy(book.bookID, "shit");
            strcpy(book.bookRackNumber, "shit");
            strcpy(book.bookAuthor, "shit");
            strcpy(book.bookName, "shit");
            
            book = askForBookDetails(book);// initilize the book record
            
            if(strcmp(book.bookCategory, "No Result") != 0){
                // save the record to the file
                fprintf(bookFilePtr, "\n%s\nBook Name: %s\nCategory: %s\nAuthor: %s\nRack Number: %s\n", book.bookID, book.bookName, book.bookCategory, book.bookAuthor, book.bookRackNumber);
                
                // prompt the user if he wants to add another record
                createTitle("Add Another Record? (Y/N): ");
                scanf(" %c", &willRepeat);
                }
            }
        
        } while(willRepeat == 'Y' || willRepeat == 'y');
    
    // close file
    fclose(bookFilePtr);
}



FILE* fileRecordSearch(char* fileName){
    char ID[50];
    char fileID[50];
    
    bool isMatchFound = false; // i thought it was memory management only but turns out it benefited the printing
    
    FILE* bookIDPtr = NULL;
    
    
    printf("Please Enter The ID: ");
    scanf("%s", ID);
    
    // later... fgets adds the \n to the string so we'll do it too
    strcat(ID, "\n");
    
    // Open book file
    bookIDPtr = fopen(fileName, "r");
    
    if(bookIDPtr == NULL){
        printf("File Does Not Exist...\n");
        
    } else {
        // check for record
        while(feof(bookIDPtr) == false && isMatchFound == false){
            
        // store file word in ID to later be checked // fscanf automatically moves the pointer to the next line
            fgets(fileID, sizeof(fileID), bookIDPtr);
            
            // checks grabbed ID to the user input ID
            if(strcmp(fileID, ID) == 0){
                createTitle("Match Found");
                isMatchFound = true;
            }
        }
        // prints if the record has not been found
        if(isMatchFound == false){createTitle("Match Not Found");}
        
        isMatchFound = false;
    }
    
    return bookIDPtr;
}



void printBookRecord(){
    char willRepeat = 'N';
    char fileBookDetails[50];
    
    
    do{
        FILE* bookIDPtr = fileRecordSearch("Book Records.txt");
        int shit = feof(bookIDPtr);
        if( shit == false){
            
            for(int j = 0; j < 4; j++){
                fgets(fileBookDetails, sizeof(fileBookDetails), bookIDPtr);
                printf("%s", fileBookDetails);
            }
            
            createTitle("Search For Another Record? (Y/N): ");
            scanf(" %c", &willRepeat);
        }
        
        fclose(bookIDPtr);
        
    } while(willRepeat == 'Y' ||  willRepeat == 'y');
    
}



void editBooks(){
    char ID[20];
    char fileWordHolder[50];
    char pointerLineIncrementor[50];
    char something[50];
    
    struct BookRecord book;
    
    FILE* newBookFilePtr;
    FILE* currentBookFilePtr;
    
    
    printf("Please Enter The Book\'s ID: ");
    scanf("%s", ID);
    strcat(ID, "\n");
    
    strcpy(book.bookID, ID); // copy ID to the struct instance
    
    gets(something);
    printf("Book Category: ");
    gets(book.bookCategory);
    
    printf("Book Name: ");
    gets(book.bookName);
    
    printf("Author: ");
    gets(book.bookAuthor);
    
    printf("Rack Number: ");
    gets(book.bookRackNumber);
    
    
    currentBookFilePtr = fopen("Book Records.txt", "r");
    newBookFilePtr = fopen("Book Records Copy.txt", "w");
    
    // while the end of the line is not reached
    while(fgets(fileWordHolder, 20, currentBookFilePtr) != NULL){// fgets will iterate the pointer automatically
        
        if(strcmp(fileWordHolder, ID) == 0){
            // to add 4 to the current pointer's position
            for(int i = 0; i <= 4; i++){
                fgets(pointerLineIncrementor, sizeof(pointerLineIncrementor), currentBookFilePtr);
            }
            // add edited stuff to the file as a replacement
            fprintf(newBookFilePtr, "%sCategory: %s\nName: %s\nAuthor: %s\nRack Number: %s\n", book.bookID, book.bookCategory, book.bookName, book.bookAuthor, book.bookRackNumber);
            
            
        } else {fputs(fileWordHolder, newBookFilePtr);}
    }
    
    fclose(currentBookFilePtr);
    fclose(newBookFilePtr);
    
    remove("Book Records.txt");
    rename("Book Records Copy.txt", "Book Records.txt");
}



void adminRegister(){
    struct AdminRecord adminRecord;
    
    FILE* adminDetailsPtr = fopen("Admin Records.txt", "a");
    
    if(adminDetailsPtr == NULL){
        printf("An error has occured while opening the file");
        
    } else {
        
        printf("Enter a username: ");
        scanf("%s", adminRecord.userName);
        
        printf("Enter a password: ");
        scanf("%s", adminRecord.password);
        
        fprintf(adminDetailsPtr, "\n%s\n%s\n", adminRecord.userName, adminRecord.password);
        fclose(adminDetailsPtr);
    }
}



bool adminCheckPass(){
    char userPassword[50];
    char fileDetails[50];
    
    FILE* admin = fopen("Admin Records.txt", "a"); // fileRecordSearch opens the file in read mode which doesnt create the actual file if it doesnt exist
    fclose(admin);
    
    FILE* adminCheckPtr = fileRecordSearch("Admin Records.txt");
    
    if(feof(adminCheckPtr) == false){ // the check is to prevent continuing if there was no match
        
        printf("Please Enter the Password: ");
        scanf("%s", userPassword);
        strcat(userPassword, "\n");
        
        fgets(fileDetails, sizeof(fileDetails), adminCheckPtr);
    }
    
    fclose(adminCheckPtr);
    
    if(strcmp(fileDetails, userPassword) == 0){
        return true;
        
    } else {
        return false;
    }
}

