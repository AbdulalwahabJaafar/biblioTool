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

			//printf(entry.entryType);
			//printf("\n");
			//printf(entry.citationKey);
			//printf("\n");
            while (fgets(line, sizeof(line), file)) {
            	//printf(line);
            	FieldName(line,fName);
            	fieldValue(line,fValue,256); 
				set_entry_field(&entry, fName, fValue); 
				//printf(entry.author);
            	//printf("\n");
				//printf(fValue);
                if (line[0] == '}') //one entry complete
				{
					entries[count] = entry; //copy entry and exit inner loop
					break;
				 } 
            }
            
        }
        
        count++;
      
    }
    printf("count = %d\n",count);
    
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

void set_entry_field(refEntry *entry, char *field, char *value) {
    
	if (isEqual(field, "entryType") == 1)
        strncpy(entry->entryType, value, sizeof(entry->entryType) - 1);
        
    else if (isEqual(field, "citationKey") == 1)
        strncpy(entry->citationKey, value, sizeof(entry->citationKey) - 1);
        
    else if (isEqual(field, "author") == 1)
        strncpy(entry->author, value, sizeof(entry->author) - 1);
        
    else if (isEqual(field, "title") == 1)
        strncpy(entry->title, value, sizeof(entry->title) - 1);
        
    else if (isEqual(field, "journal") == 1)
        strncpy(entry->journal, value, sizeof(entry->journal) - 1);
        
    else if (isEqual(field, "booktitle") == 1)
        strncpy(entry->booktitle, value, sizeof(entry->booktitle) - 1);
        
    else if (isEqual(field, "abstract") == 1)
        strncpy(entry->abstract, value, sizeof(entry->abstract) - 1);
        
    else if (isEqual(field, "keywords") == 1)
        strncpy(entry->keywords, value, sizeof(entry->keywords) - 1);
        
    else if (isEqual(field, "doi") == 1)
        strncpy(entry->doi, value, sizeof(entry->doi) - 1);
        
    else if (isEqual(field, "isbn") == 1)
        strncpy(entry->isbn, value, sizeof(entry->isbn) - 1);
        
    else if (isEqual(field, "issn") == 1)
        strncpy(entry->issn, value, sizeof(entry->issn) - 1);
        
    else if (isEqual(field, "url") == 1)
        strncpy(entry->url, value, sizeof(entry->url) - 1);
        
    else if (isEqual(field, "publisher") == 1)
        strncpy(entry->publisher, value, sizeof(entry->publisher) - 1);
        
    else if (isEqual(field, "volume") == 1)
        strncpy(entry->volume, value, sizeof(entry->volume) - 1);
        
    else if (isEqual(field, "issue") == 1)
        strncpy(entry->issue, value, sizeof(entry->issue) - 1);
        
    else if (isEqual(field, "pages") == 1)
        strncpy(entry->pages, value, sizeof(entry->pages) - 1);
        
    else if (isEqual(field, "month") == 1)
        strncpy(entry->month, value, sizeof(entry->month) - 1);
        
    else if (isEqual(field, "year") == 1)
        strncpy(entry->year, value, sizeof(entry->year) - 1);
}

void displayUWEHarwardRef(refEntry entry)
{
    printf("@%s{%s\n", entry.entryType, entry.citationKey); //print type and citation key

    //check which field is present  //print non empty fields
    if (strlen(entry.author))      printf("  author = {%s},\n", entry.author);
    if (strlen(entry.title))       printf("  title = {%s},\n", entry.title);
    if (strlen(entry.journal))     printf("  journal = {%s},\n", entry.journal);
    if (strlen(entry.booktitle))   printf("  booktitle = {%s},\n", entry.booktitle);
    if (strlen(entry.abstract))    printf("  abstract = {%s},\n", entry.abstract);
    if (strlen(entry.keywords))    printf("  keywords = {%s},\n", entry.keywords);
					
    if (strlen(entry.doi))         printf("  doi = {%s},\n", entry.doi);
    if (strlen(entry.isbn))        printf("  isbn = {%s},\n", entry.isbn);
    if (strlen(entry.issn))        printf("  issn = {%s},\n", entry.issn);
   
					
    if (strlen(entry.publisher))   printf("  publisher = {%s},\n", entry.publisher);
    if (strlen(entry.volume))      printf("  volume = {%s},\n", entry.volume);
    if (strlen(entry.issue))       printf("  issue = {%s},\n", entry.issue);
    if (strlen(entry.pages))       printf("  pages = {%s},\n", entry.pages);
    if (strlen(entry.month))       printf("  month = {%s},\n", entry.month);
    if (strlen(entry.url))         printf("  url = {%s},\n", entry.url);
    if (strlen(entry.year))        printf("  year = {%s},\n", entry.year);

    printf("}\n\n");
}

void processChoice(int choice,refEntry entries[100],int count)
{
	char input[100];
	switch (choice) {
        case 1:
            printf("Enter author name to search: ");
			scanf("%s", input);
			searchByAuthor(entries, count, input);
            break;

        case 2:
            printf("Enter title keyword to search: ");
            scanf("%s", input);
            searchByTitle(entries, count, input);
            break;

        case 3:
            printf("Enter publication year: ");
            scanf("%s", input);
            //searchByYear(entries, count, input);
            break;

        case 4:
        	scanf("%s", input);
            // search by year range
            //printf("Feature not implemented yet: Search by year range.\n");
            break;

        case 5:
        	scanf("%s", input);
            //  displayPublicationTypes()
            //printf("Feature not implemented yet: Display publication types.\n");
            break;

        case 6:
        	scanf("%s", input);
            //  displayAuthorsAlphabetically()
            //printf("Feature not implemented yet: Display authors alphabetically.\n");
            break;

        case 7:
        	scanf("%s", input);
            //  detectDuplicateEntries()
            break;

        case 8:
            //  showMissingFields()
            scanf("%s", input);
            break;

        case 9:
        	scanf("%s", input);
            //  showHarvardFormat()
            //displayUWEHarwardRef(entries[0]);
            break;

        case 10:
        	scanf("%s", input);
            // Implement addNewEntry()
            //printf("Feature not implemented yet: Add new bibliography entry.\n");
            break;

        case 0:
        	scanf("%s", input);
            printf("Exiting program. Good bye!\n");
            break;

        default:
        	
            printf("Invalid choice. Please try again.\n");
        }

    

}


void toLowerCase(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
        i++;
    }
}



void searchByAuthor(refEntry entries[], int count, const char *query) {
    char lowerQuery[100];
    char authorCopy[100];
    int i = 0;
    strncpy(lowerQuery, query, sizeof(lowerQuery)); //copy query
    toLowerCase(lowerQuery); //change to lower case

    int found = 0;
    //printf("\nSearch results for Author \"%s\":\n", query); //debug message

    for (i=0; i < count; i++) { //check  authors of all entries
        strncpy(authorCopy, entries[i].author, sizeof(authorCopy)); //copy author names
        toLowerCase(authorCopy);  //change case to lower

        if (strstr(authorCopy, lowerQuery)) {  //strstr() is a standard library function in C used to: Find the first occurrence of a substring within a string
            printf("Match found!\n");
			displayUWEHarwardRef(entries[i]);
			//printf("- %s \nby\n %s \n(%s)\n", entries[i].title, entries[i].author, entries[i].year); //found message
            found = 1;
        }
    }

    if (!found) {
        printf("No matching authors found.\n");
    }
}
void searchByTitle(refEntry entries[], int count, const char *query) {
    char lowerQuery[100];
    char authorCopy[100];
    int i = 0;
    strncpy(lowerQuery, query, sizeof(lowerQuery)); //copy query
    toLowerCase(lowerQuery); //change to lower case

    int found = 0;
    //printf("\nSearch results for Author \"%s\":\n", query); //debug message

    for (i=0; i < count; i++) { //check  authors of all entries
        strncpy(authorCopy, entries[i].title, sizeof(authorCopy)); //copy author names
        toLowerCase(authorCopy);  //change case to lower

        if (strstr(authorCopy, lowerQuery)) {  //strstr() is a standard library function in C used to: Find the first occurrence of a substring within a string
            printf("Match found!\n");
			displayUWEHarwardRef(entries[i]);
			//printf("- %s \nby\n %s \n(%s)\n", entries[i].title, entries[i].author, entries[i].year); //found message
            found = 1;
        }
    }

    if (!found) {
        printf("No matching authors found.\n");
    }
}
