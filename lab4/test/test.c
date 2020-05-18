#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int x,y;

void takeInput(char *input, int ***table){
	int i;
	*table = (int**) malloc(sizeof(int*) * 200);
	for (i = 0; i < 200; i++){
		(*table)[i] = (int*) malloc(sizeof(int) * 3);
	}
	fgets(input, 200, stdin);
	input[strlen(input) - 1] = '\0';
}

void fillNodePosition(char *input, int **table, int length){
	int i;
	for (i = 0; i < length; i++){
		table[i][0] = i;
	}
}

void fillTable(char *input, int **table, int length){
	int r = 2;
	int i;
	for (i = 1; i < length; i++){
		if (input[i] != '.' && input[i-1] != '.'){
			table[i-1][1] = i;
		}
		else if (input[i] != '.' && input[i-1] == '.'){
			table[i-r][2] = i;
			/*if (input[i+1] == '.'){
				r = 1;
			}*/
		}
		else if (input[i-1] != '.' && input[i] == '.'){
			table[i-1][1] = i;
			table[i][1] = -1;
			table[i][2] = -1;
		}
		
		else{
			table[i-2][2] = i;
			r = 2*r;
			table[i][1] = -1;
			table[i][2] = -1;
		}
	}
}

//void printTree(rbnode root) {

//}

int main(){
	char *input;
	int **table;
	takeInput(input, &table);
	int length = strlen(input);
	fillNodePosition(input, table, length);
	fillTable(input, table, length);
	int i;
	for (i = 0; i < length; i++){
		printf("%d %d %d\n", table[i][0], table[i][1], table[i][2]);
	}
	free(table);
}
