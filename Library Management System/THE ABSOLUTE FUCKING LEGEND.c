
#include "THE ABSOLUTE FUCKING LEGEND.h"
#include "KarimLibraryFunctions.h"
#include <string.h>

void deleteBook(void){
    char bookID[50];
    char FileDetail[50];
    
    FILE* fp;
    FILE* fp1;
    FILE* fp3;
    
    printf("Enter the id of the book you wanna delete:");
    scanf("%s",bookID);
    strcat(bookID,"\n");
    
    fp = fopen("Book Records.txt","r");
    fp1 = fopen("temp.txt","w");
    fp3 = fopen("recoveryfile.txt","a");
    
    while(fgets(FileDetail, 50, fp) != NULL){
        
        if(strcmp(FileDetail,bookID) == 0){
            
            for(int i = 0; i < 5; i++) { // skip a record
                
                fprintf(fp3,"%s",FileDetail); // write the skipped record to the recovery file
                fgets(FileDetail,50,fp);
                
            }
            
            fprintf(fp3, "\n");
            
        } else {
            fprintf(fp1,"%s",FileDetail);
        }
    }
    
    fclose(fp);
    fclose(fp1);
    fclose(fp3);
    
    remove("Book Records.txt");
    rename("temp.txt","Book Records.txt");
    
}

void RecoverRecord(){
    char bookID1[50];
    FILE* fp;
    FILE* fp2;
    char recoverydata[50];
    
    printf("Enter book ID");
    scanf("%s",bookID1);
    
    fp = fopen("recoveryfile.txt","r");
    fp2 = fopen("Book Records.txt","a");
    
    strcat(bookID1,"\n");
    
    while(fgets(recoverydata,50,fp) != NULL){
        
        if(strcmp(bookID1,recoverydata) == 0){
            
            for(int i=0;i<5;i++){
                fprintf(fp2,"%s",recoverydata);
                fgets(recoverydata, 50, fp);
            }
            fprintf(fp2, "\n");
            break;
        }
    }
    
    if(feof(fp) == true){
        createTitle("Record Not Found In Recovery File");
    }
    
    fclose(fp);
    fclose(fp2);
}
