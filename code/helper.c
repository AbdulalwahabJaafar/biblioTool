#include "stdio.h"
#include "string.h"
#include <ctype.h>
#include "helper.h"

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



int loadEntries(const char *filename, refEntry entries[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        return 0;
    }
	refEntry dummy;
    char line[512];
    char fName[512];
    char fValue[512];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < MAX_ENTRIES) {
        if (line[0] == '@') {
            refEntry entry = {0};

            // Parse entry type and citation key
            char *start = strchr(line, '@') + 1;
            char *brace = strchr(start, '{');
            strncpy(entry.entryType, start, brace - start);
            entry.entryType[brace - start] = '\0';

            char *comma = strchr(brace, ',');
            strncpy(entry.citationKey, brace + 1, comma - brace - 1);
            entry.citationKey[comma - brace - 1] = '\0';

            while (fgets(line, sizeof(line), file)) {
            	//printf(line);
            	FieldName(line,fName);
            	fieldValue(line,fValue,200);
            	
				
				set_entry_field(&dummy, fName, fValue); 
				printf(dummy.author);
            	printf("\n");
				printf(fValue);
            	break;
                if (line[0] == '}') break;
            }
            
        }
        
        count++;
      
    }
    
}


void FieldName(char *line, char *firstWord) {
    // Skip leading whitespace
    while (*line == ' ') {
        line++;
    }

    // Copy characters until space or end of word
    int i = 0;
    while (*line && *line != ' ') { 
        firstWord[i++] = *line++;
    }
    firstWord[i] = '\0'; // Null-terminate the string
}


#include <stdio.h>
#include <string.h>

int fieldValue(char *line, char *output, int max_len) {
    char *start = strchr(line, '{'); //start of {
    char *end = strchr(line, '}');   // index if }

    if (!start || !end || start > end) { //limits checking
        return 0; // Failed to find valid braces
    }

    int len = end - start - 1; //length of field value
    if (len >= max_len) { //if greater than size limit
        len = max_len - 1; // Prevent buffer overflow
    }

    strncpy(output, start + 1, len); //copying field value
    output[len] = '\0';  //null terminating 
    //printf(output);
    return 1; // Success
}


int isEqual(char *src1,char *src2)
{
	while(*src1 && *src2)
	{
		
		if(*src1!=*src2){
			return 0;
		}
		src1++;
		src2++;
	}
	if(*src1 == *src2) return 1; 
	else 
	return 0;
}

void set_entry_field(refEntry *entry, char *field,  char *value) {
    if (isEqual(field, "author") == 1)
        strncpy(entry->author, value, sizeof(entry->author) - 1);
    else if (isEqual(field, "doi") == 1)
        strncpy(entry->doi, value, sizeof(entry->doi) - 1);
    else if (isEqual(field, "issn") == 1)
        strncpy(entry->issn, value, sizeof(entry->issn) - 1);
    else if (isEqual(field, "issue") == 1)
        strncpy(entry->issue, value, sizeof(entry->issue) - 1);
    else if (isEqual(field, "journal") == 1)
        strncpy(entry->journal, value, sizeof(entry->journal) - 1);
    else if (isEqual(field, "keywords") == 1)
        strncpy(entry->keywords, value, sizeof(entry->keywords) - 1);
    else if (isEqual(field, "month") == 1)
        strncpy(entry->month, value, sizeof(entry->month) - 1);
    else if (isEqual(field, "pages") == 1)
        strncpy(entry->pages, value, sizeof(entry->pages) - 1);
    else if (isEqual(field, "publisher") == 1)
        strncpy(entry->publisher, value, sizeof(entry->publisher) - 1);
    else if (isEqual(field, "title") == 1)
        strncpy(entry->title, value, sizeof(entry->title) - 1);
    else if (isEqual(field, "volume") == 1)
        strncpy(entry->volume, value, sizeof(entry->volume) - 1);
    else if (isEqual(field, "url") == 1)
        strncpy(entry->url, value, sizeof(entry->url) - 1);
    else if (isEqual(field, "year") == 1)
        strncpy(entry->year, value, sizeof(entry->year) - 1);
    
}


