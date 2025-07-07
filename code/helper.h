#ifndef HELPER_H
#define HELPER_H

#define MAX_ENTRIES 2
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


int displayMenu(void);

int loadEntries(const char *filename, refEntry entries[]);
void FieldName(char *line, char *firstWord);
int fieldValue(char *line, char *output, int max_len);
void set_entry_field(refEntry *entry, char *field,  char *value);
int isEqual(char *src1,char *src2);
#endif


