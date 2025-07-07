#include <stdio.h>
#include <stdlib.h>
#include "helper.h"




int main(void)
{
	const char *filename = "2425resitbiblio.txt";
	refEntry entries[100];
	
	//displayMenu();
    loadEntries(filename, entries);
	//readFile(filename,entries);
    printf("\n%d",isEqual("String","StriNg"));
    
    return 0;
}

