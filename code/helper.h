#ifndef HELPER_H
#define HELPER_H

#define MAX_ENTRIES 100
typedef struct {
    char entryType[256];     // e.g. article, inproceedings, etc.
    char citationKey[256];   // the citation key after the @type{
    
    char author[1024];
    char title[1024];
    char journal[512];
    char booktitle[512];
    char abstract[2048];
    char keywords[512];
    
    char doi[256];
    char isbn[128];
    char issn[128];
    char url[512];
    
    char publisher[512];
    char volume[64];
    char issue[64];
    char pages[64];
    char month[64];
    char year[64];
} refEntry;


int displayMenu(void);

int loadEntries(const char *filename, refEntry entries[]);
void FieldName(char *line, char *firstWord);
int fieldValue(char *line, char *output, int max_len);
void set_entry_field(refEntry *entry, char *field,  char *value);
int isEqual(char *src1,char *src2);
void displayUWEHarwardRef(refEntry entry);
void toLowerCase(char *str);
void processChoice(int choice,refEntry entries[100],int count);
void searchByTitle(refEntry entries[], int count, const char *query);
void searchByAuthor(refEntry entries[], int count, const char *query);
void searchBySignleYear(refEntry entries[], int count, const char *query);


#endif


