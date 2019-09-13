#include <stdio.h>
#include <string.h>
#include "AbdoLibraryFunctions.h"
#include "KarimLibraryFunctions.h"


void ViewBookList(){
    
    FILE *fptr;
    char c;
    
    fptr = fopen("Book Records.txt", "r");

    if(fptr == NULL){
        printf("Cannot open file \n");
    } else {
        
        c = fgetc(fptr);
        
        while (c != EOF) {
            printf("%c", c);
            c = fgetc(fptr);
        }
        
        fclose(fptr);
    }
}






