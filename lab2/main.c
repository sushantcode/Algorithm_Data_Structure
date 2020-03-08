#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *OpenFile(int argc, char *argv[])
{
	//initializing variable for file input
	char filename[30];
	//if command line contains 2 arguments, second one is copied to filename else user is asked to enter filename
	if(argc == 2)
	{
		strcpy(filename, argv[1]);
  }
	//file is opened with read only mode and stored in file handle
	FILE *readFH = fopen(filename, "r");
	//user is promted to enter new file if file is empty
	while(readFH == NULL)
	{
		printf("\nCould not open input file named %s.\nEnter the new filename: ", filename);
		scanf(" %s", &filename);
		getchar();
		readFH = fopen(filename, "r");
	}
	//file handle is returned
	return readFH;
}

int main(int argc, char *argv[])
{
	//ask number of files
	int n;
	scanf("%d", &n);
	//ask files' names and open them
	int i;
	char filename[30];
	FILE *readFH[n];
	for(i = 0; i < n; i++)
	{
		scanf(" %s", &filename);
		readFH[i] = fopen(filename, "r");
		if(readFH == NULL)
		{
			printf("Error: File not found!!!");
			exit(1);
		}
	}
	//create and open out.dat file
	FILE *outFH = fopen("out.dat", "w");
	//each lines are read and stored in fileLine
	while(fgets(fileLine, 100, readFH) != NULL &&)
	{
		//extracting first letter to draw
		char *dLetter = strtok(fileLine, "|");
		//extracting draw command from fileline
		char *dCommand = strtok(NULL, "|");
		//printf("%s\n", dCommand);
		addNode(*dLetter, dCommand, &LLH);
	}
	//closing file
	fclose(readFH);
	return 0;
}
