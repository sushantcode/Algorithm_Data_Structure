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
		if(readFH[i] == NULL)
		{
			printf("Error: File not found!!!");
			exit(0);
		}
	}
	//create and open out.dat file
	FILE *outFH = fopen("out.dat", "w");
	char *word[n];
	char fileLine[50];
	int a;
	for(a = 0; a < n; a++)
	{
		word[a] = (char*) malloc(50 * sizeof(char));
		if (!word[a])
		{
  			printf("malloc failed %d\n",__LINE__);
  			exit(0);
		}
	}
	int b;
	for(b = 0; b < n; b++)
	{
		fgets(fileLine, 50, readFH[b]);
		strcpy(word[b], fileLine);
		printf(" %s ", word[b]);
	}
	/*int b;
	for(b = 0; b < n; b++)
	{
		printf(" %s ", *word[b]);
	}*/
	//each lines are read and stored in fileLine
	/*while(fgets(fileLine, 100, readFH) != NULL &&)
	{
		//extracting first letter to draw
		char *dLetter = strtok(fileLine, "|");
		//extracting draw command from fileline
		char *dCommand = strtok(NULL, "|");
		//printf("%s\n", dCommand);
		addNode(*dLetter, dCommand, &LLH);
	}*/
	//closing file
	int j;
	for(j = 0; j < n; j++)
	{
		fclose(readFH[j]);
	}
	fclose(outFH);
	return 0;
}
