#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
  //initializing variable for input filename
  char filename[30];
  scanf(" %s", filename);
  //open the file with read mode
  FILE *readFH = fopen(filename, "r");
  //check whether the file opened successfully
  if (readFH == NULL)
    {
      printf("\nCould not open input file named %s. ", filename);
      exit(0);
    }
  //lines of file is stored in fileLine
  char fileLine[100];
  //first line is read and values are stored in respective variables
  fgets(fileLine, 100, readFH);
  char *token;
  token = strtok(fileLine, " ");
  //length of sequence
  int n = atoi(token);
  token = strtok(NULL, " ");
  //target 1
  int t1 = atoi(token);
  token = strtok(NULL, " ");
  //target 2
  int t2 = atoi(token);
  //initializing the sequence
  int s[n];
  //each lines are read and equivalent int are stored
  int i;
  for (i = 0; i < n; i++)
  {
      fgets(fileLine, 100, readFH)'
      fileLine[strlen(fileLine) - 1] = '\0';
      s[i] = atoi(fileLine);
  }
  //closing file
  fclose(readFH);
  return o;
}
