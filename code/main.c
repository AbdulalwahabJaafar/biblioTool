#include <stdio.h>
#include <stdlib.h>
#include "helper.h"




int main(void)
{
	const char *filename = "2425resitbiblio.txt";
	int choice;
	refEntry entries[100];
	loadEntries(filename, entries);
	
    do{
    	choice = displayMenu();
    	processChoice(choice,entries,15);
	}while(choice!=0);
    
    //printf(entries[0].author);
	//readFile(filename,entries);
    //printf("\n%d",isEqual("String","StriNg"));
    //displayUWEHarwardRef(entries[2]);
    return 0;
}

