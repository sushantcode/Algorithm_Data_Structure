#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
	char *word[n];
	char fileLine[100];
	while(n > 0)
	{
		fgets(fileLine, 100, readFH[n-1]);
		fileLine[strlen(fileLine) - 1] = '\0';
		word[n-1] = malloc(strlen(fileLine) * sizeof(char));
		strcpy(word[n-1], fileLine);
		n--;
	}
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
	int j;
	for(j = 0; j < n; j++)
	{
		fclose(readFH[j]);
	}
	fclose(outFH);
	return 0;
}
