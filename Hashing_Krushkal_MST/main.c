#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, m, root1, root2;
int *parent, *weight, numTrees;

typedef struct stringTable {
	char str[25];
} stringTable;
stringTable *strTable;

typedef struct edge{
	int tail, head, weight;
}edge;
edge *edgeTable;

//to find whether num is prime
int isPrime(int num){
	int i;
	for (i = 2; i <= (num/2); i++){
		if (num%i == 0)
			return 0;
	}
	return 1;
}

//fills hash table, stringTable, edgeTable and return the actual number of vertices
int fillTables(int p, int *hash){
	char key1[25];
	char key2[25];
	int i, h1, h2, j, c = 0;
	for (i = 0; i < m; i++){
		printf("\nEnter the tail-vertex: ");
		scanf(" %s", key1);
		j = h1 = key1[0]%p;
		h2 = key1[0]%(p-1) + 1;
		while (hash[j] != (-1) && strcmp(strTable[hash[j]].str, key1) != 0){
			j = (j + h2)%p;
		}
		if (hash[j] == (-1) || strcmp(strTable[hash[j]].str, key1) != 0) {
			hash[j] = c;
			strcpy(strTable[c].str, key1);
			c++;
			if (n < c) {
				printf("Error: there are more vertices than n.");
				exit(0);
			}
		}
		edgeTable[i].tail = hash[j];
		printf("\nEnter the head-vertex: ");
		scanf(" %s", key2);
		j = h1 = key2[0]%p;
		h2 = key2[0]%(p-1) + 1;
		while (hash[j] != (-1) && strcmp(strTable[hash[j]].str, key2) != 0){
			j = (j + h2)%p;
		}
		if (hash[j] == (-1) || strcmp(strTable[hash[j]].str, key2) != 0) {
			hash[j] = c;
			strcpy(strTable[c].str, key2);
			c++;
			if (n < c) {
				printf("Error: there are more vertices than n.\n");
				exit(0);
			}
		}
		edgeTable[i].head = hash[j];
		printf("\nEnter the weight of the edge: ");
		scanf("%d", &edgeTable[i].weight);
	}
	if (c < n){
		printf("Warning: continuing with only %d vertices when n is %d\n", c, n);
	}
	return c;
}

//to find the root of tree containing x
int findRoot(int x) {
	int i, j, root;
	//finding root
	for (i = x; parent[i] != i; i = parent[i]){
		;
	}
	root = i;
	//makes all nodes on path pointing directly at the root
	for (i = x; parent[i] != i; j = parent[i], parent[i] = root, i = j){
		;
	}
	return root;
}

//Here, i and j are roots!
void unionFunc(int i,int j){
	if (weight[i] > weight[j]){
		parent[j] = i;
		weight[i] += weight[j];
	}
	else
	{
		parent[i] = j;
		weight[j] += weight[i];
	}
	numTrees--;
}

//for the qsort()
int weightAscending(const void* xin, const void* yin) {
	edge *x,*y;
	x=(edge*) xin;
	y=(edge*) yin;
	return x->weight - y->weight;
}

//output the result in preffered format
void printResult(int inclSize){
	int i;
	if (numTrees == 1) {
		printf("\nOutputting tree with leader %d\n", root1);
		for (i = 0; i < inclSize; i++) {
			printf("%s    %s    %d\n", strTable[edgeTable[i].tail].str, strTable[edgeTable[i].head].str, edgeTable[i].weight);
		}
	}
	else {
		int edInclude[inclSize];
		//loop to print all trees
		while(numTrees){
			int incl = 0;
			qsort(edgeTable, inclSize, sizeof(edge), weightAscending);
			root1 = findRoot(edgeTable[0].head);
			printf("\n");
			printf("Outputting tree with leader %d\n", root1);
			printf("%s    %s    %d\n", strTable[edgeTable[0].tail].str, strTable[edgeTable[0].head].str, edgeTable[0].weight);
			for(i = 1; i < inclSize; i++){
				root2 = findRoot(edgeTable[i].tail);
				if(root1 == root2){
					printf("%s    %s    %d\n", strTable[edgeTable[i].tail].str, strTable[edgeTable[i].head].str, edgeTable[i].weight);
				}
				else{
					edInclude[incl] = i;
					incl++;
				}
			}
			for (i = 0; i < incl; i++) {
				edgeTable[i].tail = edgeTable[edInclude[i]].tail;
				edgeTable[i].head = edgeTable[edInclude[i]].head;
				edgeTable[i].weight = edgeTable[edInclude[i]].weight;
			}
			inclSize = incl;
			numTrees--;
		}
	}
}

int main(int argc, char *argv[])
{
	int i, MSTweight = 0;
	int *hash;
	//read number of vertices
	printf("Enter the number of vertices: ");
	scanf("%d", &n);
	if (n < 1){
		printf("Bad number of vertices %d\n", n);
		exit(0);
	}
	int p = 2*n;
	while (!isPrime(p)){
		p++;
	}
	//read number of edges
	printf("Enter the number of edges: ");
	scanf("%d", &m);
	if (m < 1){
		printf("Bad number of edges %d\n", m);
		exit(0);
	}
	//allocate memory 
	strTable = (stringTable*) malloc(n * sizeof(stringTable));
	edgeTable = (edge*) malloc(m * sizeof(edge));
	hash = (int*) malloc(p * sizeof(int));
	parent = (int*) malloc(n * sizeof(int));
	weight = (int*) malloc(n * sizeof(int));
	if (!strTable || !edgeTable || !hash || !parent || !weight) {
		printf("malloc failed\n");
		exit(0);
	}
	for (i = 0; i < p; i++){
		hash[i] = (-1);
	}
	//fill table and asign new/actual value of n
	n = fillTables(p, hash);
	for(i = 0; i < n; i++) {
		parent[i]=i;
		weight[i]=1;
	}
	numTrees = n;
	qsort(edgeTable, m, sizeof(edge), weightAscending);
	int edInclude[m];
	int inclSize = 0;
	for(i = 0; i < m; i++){
		root1 = findRoot(edgeTable[i].tail);
		root2 = findRoot(edgeTable[i].head);
		if(root1 != root2){
			edInclude[inclSize] = i;
			inclSize++;
			MSTweight += edgeTable[i].weight;
			unionFunc(root1, root2);
		}
	}
	printf("Sum of weights of spanning edges is %d\n", MSTweight);
	for (i = 0; i < inclSize; i++) {
		edgeTable[i].tail = edgeTable[edInclude[i]].tail;
		edgeTable[i].head = edgeTable[edInclude[i]].head;
		edgeTable[i].weight = edgeTable[edInclude[i]].weight;
	}
	printResult(inclSize);
	//free memory
	free(strTable);
	free(edgeTable);
	free(hash);
	free(parent);
	free(weight);
	return 0;
}
