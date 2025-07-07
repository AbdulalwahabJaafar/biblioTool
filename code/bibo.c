// bibo.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "bibo.h"



int displayMenu() {
    int choice;
    printf("\n===========================\n");
    printf(" Bibliography Search Tool\n");
    printf("===========================\n\n");
    printf("1. Search by Author\n");
    printf("2. Search by Title\n");
    printf("3. Search by Year\n");
    printf("4. Search by Year Range\n");
    printf("5. Display Publication Types\n");
    printf("6. Display Authors Alphabetically\n");
    printf("7. Detect Duplicate Entries\n");
    printf("8. Show Missing Fields\n");
    printf("9. Show Entry in UWE Harvard Format\n");
    printf("10. Add a New Bibliography Entry\n");
    printf("0. Exit\n\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // clear newline
    return choice;
}



