// bibo.h
#ifndef BIBO_H
#define BIBO_H

#define MAX_ENTRIES 100

typedef struct {
    char entryType[30];
    char citationKey[50];
    char author[100];
    char doi[100];
    char issn[30];
    char issue[10];
    char journal[100];
    char keywords[100];
    char month[10];
    char pages[20];
    char publisher[100];
    char title[100];
    char volume[10];
    char url[300];
    char year[10];
} refEntry;
int displayMenu();
// File handling
int loadEntries(const char *filename, refEntry entries[]);

// Utilities
void trim(char *str);
void toLowerCase(char *str);

// Search functions
void searchByAuthor(refEntry entries[], int count, const char *query);
void searchByTitle(refEntry entries[], int count, const char *query);
void searchByYear(refEntry entries[], int count, const char *year);

#endif
