//
//  main.c
//  Library Management System
//
//  Created by NU CS479 Team
//  Copyright © 2019 All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "KarimLibraryFunctions.h"
#include "AbdoLibraryFunctions.h"
#include "THE ABSOLUTE FUCKING LEGEND.h"
#include "MohanadLibraryFunctions.h"

void mainMenu(void);
void loginScreen(void);


int main(int argc, const char * argv[]) {
    loginScreen();
    return 0;
}


void loginScreen(){
    char* adminOptions[5] = {"Login", "Register", "\0"};
    char willRegister = 'N';
    
    createMenuStructure("Login Screen", adminOptions);
    
    switch (chooseOptions("Enter Your Choice")) {
        case 0:
            if(adminCheckPass() == true){
                mainMenu();
                
            } else {
                createTitle("Incorrect, Would you like to Register? (Y/N)");
                scanf(" %c", &willRegister);
                
                if(willRegister == 'Y' || willRegister == 'y'){
                    adminRegister();
                }
                
                loginScreen();
            }
            
            break;
            
        case 1:
            adminRegister();
            loginScreen();
            break;
    }
}


void mainMenu(){
    char* MainMenuOptions[10] = {"Add Books", "Delete Books", "Search Books", "Issue Books", "View Book List", "Edit Book\'s Record", "Recover Record","Close Application", "\0"};
    
    createMenuStructure("Main Menu", MainMenuOptions);
    
    switch (chooseOptions("Enter Your Choice")) {
        case 0:
            addBooks();
            mainMenu();
            break;
            
        case 1:
            deleteBook();
            mainMenu();
            break;
            
        case 2:
            printBookRecord();
            mainMenu();
            break;
            
        case 3:
            IssueBooks();
            mainMenu();
            break;
            
        case 4:
            ViewBookList();
            mainMenu();
            break;
            
        case 5:
            editBooks();
            mainMenu();
            break;
            
        case 6:
            RecoverRecord();
            mainMenu();
            break;
            
        case 7:
            break;
            
        default:
            printf("Please Input a Valid Number (0-7)\n");
            mainMenu();
    }
    
}
