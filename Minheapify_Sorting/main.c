#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct item
{
	char *word;
	int pos;
} item;

void swap(item *old, item *new)
{
	item temp = *old;
	*old = *new;
	*new = temp;
}

int parent(int i)
{
  return i/2;
}

int left(int i)
{
  return 2*i+1;
}

int right(int i)
{
  return 2*i+2;
}

void minheapify(item array[], int n)
{
	int k;
	for (k = parent(n); k >= 0; k--) 
	{
		int j;
		while (left(k) <= n)
		{
			j = left(k);	//left child
			if (j < n && strcmp(array[j].word, array[j+1].word) > 0)
			{
				j = right(k); //take right child instead
			}
			if (strcmp(array[k].word, array[j].word) > 0)
			{
				swap(&array[k], &array[j]);
			}
			else
			{
				break;
			}
			k = j;
		}
  	}
}

void initialHeapify(item array[], FILE *readFH[], int n)
{
	char fileLine[50];
	int b;
	for(b = 0; b < n; b++)
	{
		fgets(fileLine, 50, readFH[b]);
		if (fileLine[strlen(fileLine) - 1] == '\n')
		{
			fileLine[strlen(fileLine) - 1] = '\0';
			if (isspace(fileLine[strlen(fileLine) - 2]))
			{
				fileLine[strlen(fileLine) - 2] = '\0';
			}
		}
		if (isspace(fileLine[strlen(fileLine) - 1]))
		{
			fileLine[strlen(fileLine) - 1] = '\0';
		}
		strcpy(array[b].word, fileLine);
		array[b].pos = b;
	}
	minheapify(array, n-1);
}

void mergeMinStr(item array[], FILE *readFH[], FILE *outFH, int n)
{
	char fileLine[50];
	int a = n;
	int k = 1;
	int p = array[0].pos;
	char *minStr = (char*) malloc(50 * sizeof(char));
	while(a > 0)
	{
		strcpy(minStr, array[0].word);
		p = array[0].pos;
		strcpy(array[0].word, array[a-1].word);
		array[0].pos = array[a-1].pos;
		if (fgets(fileLine, 50, readFH[p]) == NULL)
		{
			a = a - 1;
		}
		else
		{
			if (fileLine[strlen(fileLine) - 1] == '\n')
			{
				fileLine[strlen(fileLine) - 1] = '\0';
				if (isspace(fileLine[strlen(fileLine) - 2]))
				{
					fileLine[strlen(fileLine) - 2] = '\0';
				}
			}
			if (isspace(fileLine[strlen(fileLine) - 1]))
			{
				fileLine[strlen(fileLine) - 1] = '\0';
			}
			strcpy(array[a-1].word, fileLine);
			array[a-1].pos = p;
		}
		minheapify(array, a-1);
		if(strcmp(minStr, array[0].word) != 0)
		{
			fprintf(outFH, "%s %d \n", minStr, k);
			k = 1;
		}
		else
		{
			k++;
		}
	}
	fprintf(outFH, "%s %d \n", minStr, k-1);
	free(minStr);
}

int main(int argc, char *argv[])
{
	//ask number of files
	int n;
	printf("Enter the number of files: ");
	scanf("%d", &n);
	//ask files' names and open them
	int i;
	char filename[30];
	FILE *readFH[n];
	for(i = 0; i < n; i++)
	{
		printf("Enter the file name %d: ", i+1);
		scanf(" %s", filename);
		readFH[i] = fopen(filename, "r");
		if(readFH[i] == NULL)
		{
			printf("\nError: File not found!!!");
			exit(0);
		}
	}
	//create and open out.dat file
	FILE *outFH = fopen("out.dat", "w");
	item array[n]; 
	int c;
	for(c = 0; c < n; c++)
	{
		array[c].word = (char*) malloc(50 * sizeof(char));
		if (!array[c].word)
		{
  			printf("malloc failed %d\n",__LINE__);
  			exit(0);
		}
	}
	//creating initial minheap
	initialHeapify(array, readFH, n);
	//extracting and merging files
	mergeMinStr(array, readFH, outFH, n);
	//closing files and freeing heap allocated memory
	int j;
	for(j = 0; j < n; j++)
	{
		fclose(readFH[j]);
		free(array[j].word);
	}
	fclose(outFH);
	return 0;
}
