#include "MohanadLibraryFunctions.h"
#include "KarimLibraryFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void IssueBooks() // creating the function to search for the book in file
{
    char issuedPersonName[50] = "Renter Name: ";
    char userInputName[50];
    char bookID [15] ;
    char File_det [71] ; // creating an array to store in it the book id in it
    FILE *Fptr1; // creatting a pointer to a file
    Fptr1 = fopen("Book Records.txt","r");  //placing file in read mood to read from it line by line
    
    if (Fptr1 == NULL)  // file handling in case the file is not found or failed in any other case
    {
        printf( " \nThe file is not found\n");
        return ;
    }
    
    else {
        
        gets(bookID);
        printf("enter the book ID : ");
        gets(bookID);
        printf("enter the person\'s name: ");
        gets(userInputName);
        
        strcat(bookID, "\n");
        strcat(issuedPersonName, userInputName);
        
        if(CheckForDuplicateNames(issuedPersonName) == false){
        
            while (!feof (Fptr1))   // looping in file line by line
            {
                fgets(File_det,70, Fptr1 ); // reading from file line by line
                if(strcmp ( bookID, File_det) == 0)
                {
                    FILE * Fptr3  = NULL ;
                    Fptr3 = fopen ("Issued Records.txt", "a");
                    
                    for(int counter = 0;counter < 2; counter++)
                    {
                        fprintf(Fptr3, "%s", File_det);
                        fgets(File_det, 70, Fptr1);
                    }
                    fprintf(Fptr3, "%s\n", issuedPersonName);
                    printf("\n");
                    
                    fclose(Fptr3);
                }
            }
        }else{
            createTitle("This User Already Rented a Book");
        }
    }
    
    fclose(Fptr1);
}


bool CheckForDuplicateNames(char RenterName[50]){
    FILE* fp;
    char details[50];
    
    fp = fopen("Issued Records.txt", "r");
    strcat(RenterName, "\n");
    
    while (!feof(fp)) {
        fgets(details, 50, fp);
        
        if(strcmp(details, RenterName) == 0){
            fclose(fp);
            return true;
        }
    }
    
    fclose(fp);
    return false;
}
