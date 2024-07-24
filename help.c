#include <stdio.h>
#include "help.h"

void help_menu() {
    int choice;
    do {
        printf("\n--- Help Menu ---\n");
        printf("1. View instructions\n");
        printf("2. About the calculator\n");
        printf("0. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("\nInstructions:\n");
                printf("1. Start by inputting or generating matrices.\n");
                printf("2. Use the various menus to perform operations on your matrices.\n");
                printf("3. Always enter matrix indices starting from 1.\n");
                printf("4. For operations involving multiple matrices, ensure dimensions are compatible.\n");
                printf("5. Use the View/Search menu to check your matrices at any time.\n");
                break;
            case 2:
                printf("\nAbout the Matrix Calculator:\n");
                printf("This is a comprehensive matrix calculator that allows you to perform\n");
                printf("various operations on matrices, including basic arithmetic, properties\n");
                printf("calculation, transformations, and solving systems of linear equations.\n");
                printf("It's a project with C language, which is used for my porfolio.\n");
                break;
            case 0:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}
