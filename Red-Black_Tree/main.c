/* 	Name: Sushant Gupta
	ID: 1001520302
	Command: gcc Sushant_Lab4.c
			 ./a.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define node struct
struct Rbnode{
	char color;
	struct Rbnode *lchild;
	struct Rbnode *rchild;
};

typedef struct Rbnode *rbnode;
//making root node global
rbnode root;
int i = 0;
//defining varibales to keep track of validation of each RB properties
int p1 = 0;
int p2 = 0;
int p3 = 0;
int p4 = 0;

//function to create new node
rbnode new_node(char rb){
	rbnode node;
	node = malloc(sizeof *node);
	if (node == NULL){
		printf("Memory allocation failed.");
		exit(0);
	}
	node->color = rb;
	node->lchild = NULL;
	node->rchild = NULL;
	return node;
}

//fills tree structure recursively
rbnode fillTree(char *input){
	rbnode node;
	char c = input[i++];
	if (c != '.'){
		node = new_node(c);
		node->lchild = fillTree(input);
		node->rchild = fillTree(input);
	}
	else{
		node = NULL;
	}
	return node;
}

//print the tree recursively
void printTree(rbnode node) {
	if (node == NULL) {
		printf("%c", '.');
	}
	else{
		printf("%c", node->color);
		printTree(node->lchild);
		printTree(node->rchild);
	}
}

//check the 1st property
void redOrBlack(rbnode node) {
	if (node != NULL) {
		if ((node->color == 'R') || (node->color == 'B')){
			redOrBlack(node->lchild);
			redOrBlack(node->rchild);
		}
		else{
			p1 = 1;
		}
	}
}

//check the 2nd property
void blackRoot(rbnode node){
	if (node->color != 'B'){
		p2 = 1;
	}
	else{
		p2 = 0;
	}
}

//check the 3rd property
void twoRed(rbnode node, char c){
	if (node == NULL){
		return;
	}
	if (c == 'R' && node->color == 'R'){
		p3 = 1;
	}
	twoRed(node->lchild, node->color);
	twoRed(node->rchild, node->color);
}

//count the black nodes of first left path
int blackHeight(rbnode node){
	if (node == NULL){
		return 1;
	}
	if (node->color == 'B'){
		return blackHeight(node->lchild) + 1;
	}
	else{
		return blackHeight(node->lchild);
	}
}

//check the black height property 
void checkBH(rbnode node, int bnCount){
	if (node == NULL){
		if (bnCount == 1){
			return;
		}
		else{
			p4 = 1;
		}
	}
	else{
		if (node->color == 'R'){
			checkBH(node->lchild, bnCount);
			checkBH(node->rchild, bnCount);
		}
		else{
			checkBH(node->lchild, bnCount - 1);
			checkBH(node->rchild, bnCount - 1);
		}
	}
}

//check and print message for each RB properties
void propertyCheck(){
	redOrBlack(root);
	if (p1){
		printf("Property 1: At least one of the node is neither RED nor BLACK. Failed\n");
	}
	else{
		printf("Property 1: Each nodes are Red or Black. Ok\n");
	}
	blackRoot(root);
	if (p2){
		printf("Property 2: Root is not black. Failed\n");
	}
	else{
		printf("Property 2: Root is black. Ok\n");
	}
	twoRed(root, 0);
	if (p3){
		printf("Property 3: Parent and child are Red. Failed\n");
	}
	else{
		printf("Property 3: No red parent and child in row. Ok\n");
	}
	printf("Black height should be %d\n", blackHeight(root->lchild));
	checkBH(root, blackHeight(root->lchild) + 1);
	if (p4){
		printf("Property 4: Black height is not same. Failed\n");
	}
	else{
		printf("Property 4: Black height is same. Ok\n");
	}
	if (p1 || p2 || p3 || p4){
		printf("\nDoes not satisfy all RB properties. Failed!\n\n");
	}
	else{
		printf("\nSastisfies all Red-Black tree properties. Ok!\n\n");
	}
}

//free the malloced memory
void deleteTree(rbnode node){
	if (node == NULL) {
		return;
	}
	deleteTree(node->lchild);
	deleteTree(node->rchild);
	free(node);
}
int main(){
	char *input;
	input = (char*) malloc(200 * sizeof(char));
	printf("Enter the string of the graph: \n");
	fgets(input, 200, stdin);
	input[strlen(input) - 1] = '\0';
	root = fillTree(input);
	printTree(root);
	printf("\n\n");
	propertyCheck();
	deleteTree(root);
	free(input);
}
