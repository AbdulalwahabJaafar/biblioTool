#include "stdio.h"
#include "string.h"

//Bilio struct

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

void readFile(const char *filename, refEntry entries[])
{
	
	char line[512];
    int count = 0;
    refEntry entry = {0}; // Initialize all fields to zero/empty
	FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        return 0;
    }
    
    
    while (fgets(line, sizeof(line), file) && count < 100) {
    	
    	if (line[0] == '@') { //marks the start of new entry
            
    		//extracting entry type from char @ to { 
    		// Get entryType and citationKey
            char *start = strchr(line, '@') + 1; //return location of @
            char *brace = strchr(start, '{');    //return index of {
            strncpy(entry.entryType, start, brace - start); //in between @ { there is entry type --copying it
            entry.entryType[brace - start] = '\0'; //terminating entry type string with \0
            
			//between { and , there is citation key
			char *comma = strchr(brace, ','); //index of comma
            strncpy(entry.citationKey, brace + 1, comma - brace - 1);
            entry.citationKey[comma - brace - 1] = '\0';
    		
			//printf(entry.citationKey);
  		
		  
		  
		}
    	//printf(line);
    	
    	 if (line[0] == '}') break; // End of entry
    	 
    	}
    
}
int main(void)
{
	const char *filename = "2425resitbiblio.txt";
	refEntry entries[100];
	
    //int total = loadEntries("biblio.txt", entries);
	readFile(filename,entries);
    
    
    return;
}
