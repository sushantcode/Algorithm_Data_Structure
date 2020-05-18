/* 	Name: Sushant Gupta
	ID: 1001520302
	Command: gcc Sushant_Lab3.c
*/

#include <stdio.h>
#include <stdlib.h>

//fill all the inputs
void takeInput(int *n, int *t1, int *t2, int **S, int ***C){
	int i;
	scanf("%d", n);
	scanf("%d", t1);
	scanf("%d", t2);
	//allocating memory for sequence and cost function table
	*S=(int*) malloc((*n+1)*sizeof(int));
	//*C=(int**) malloc(sizeof(int*)*(*t1+1)+sizeof(int)*(*t2+1)*(*t1+1));
	*C=(int**) malloc(sizeof(int*)*(*t1+1));
	for (i = 0; i <= (*t1); i++){
		(*C)[i] = (int*) malloc(sizeof(int)*(*t2+1));
	}
	
	if (!(*S) || !(*C))
	{
		printf("malloc failed %d\n",__LINE__);
		exit(0);
	}
	//base sequence in table
	(*S)[0] = 0;
	for (i = 1; i <= *n; i++){
		scanf("%d", *S+i);
	}
}

//calculate the cost function matrix
void subSetSum(int n, int t1, int t2, int *S, int **C){
	int i, j, k, potentialSum, leftover, leftover1, leftover2;
	
	C[0][0] = 0;
	
	for (potentialSum = 1; potentialSum <= t1; potentialSum++){
		for (j = 1; j <= n; j++){
			leftover = potentialSum - S[j];      // To be achieved with other values
			if (leftover >= 0 && C[leftover][0] < j){     
				break; 
			}
		}
		C[potentialSum][0] = j;
	}
	
	for (potentialSum = 1; potentialSum <= t2; potentialSum++){
		for (j = 1; j <= n; j++){
			leftover = potentialSum - S[j];      // To be achieved with other values
			if (leftover >= 0 && C[0][leftover] < j){     
				break; 
			}
		}
		C[0][potentialSum] = j;
	}
	
	for (i = 1; i <= t1; i++){
		for (k = 1; k <= t2; k++){
			for (j = 1; j <= n; j++){
				leftover1 = i-S[j];
				leftover2 = k-S[j];
				if ((leftover1 >= 0 && C[leftover1][k] < j) || (leftover2 >= 0 && C[i][leftover2] < j)){
					break;
				}
			}
			C[i][k] = j;
		}
	}
	
}

//output the result and backtrace function
void writeOutput(int n,int t1, int t2, int *S,int **C){
	int SS1[n+1];
	int SS2[n+1];
	int i, j;
	// Output the input set
	printf("Targets are %d and %d\n", t1, t2);
	printf("  i   S\n");
	printf("-------\n");
	for (i=1;i<=n;i++)
		printf("%3d %3d\n",i,S[i]);
	
	// Output the backtrace
	if (C[t1][t2] == n+1){
		printf("No solution.\n");
	}
	else{
		i = t1;
		j = t2;
		int l = 0;
		int k = 0;
		while (C[i][j] != 0){
			if(i >= S[C[i][j]] && S[C[i][j]] != 0){
				SS1[l] = S[C[i][j]];
				l++;
				i -= S[C[i][j]];
			}
			else if(j >= S[C[i][j]] && S[C[i][j]] != 0){
				SS2[k] = S[C[i][j]];
				k++;
				j -= S[C[i][j]];
			}
			else{
				break;
			}
		}
		if (i != 0 || j != 0){
			i = t1;
			j = t2;
			l = 0;
			k = 0;
			while (C[i][j] != 0){
				if(j >= S[C[i][j]] && S[C[i][j]] != 0){
					SS2[k] = S[C[i][j]];
					k++;
					j -= S[C[i][j]];
				}
				else if(i >= S[C[i][j]] && S[C[i][j]] != 0){
					SS1[l] = S[C[i][j]];
					l++;
					i -= S[C[i][j]];
				}
				else{
					break;
				}
			}
		}
		printf("Subsequence for %d:\n", t1);
		for (i = l-1; i >= 0; i--)
			printf("%d\n",SS1[i]);
		printf("Subsequence for %d:\n", t2);
		for (i = k-1; i >= 0; i--)
			printf("%d\n",SS2[i]);
	}
}

int main(){
	//n-num of elements in sequence, t1-first target, t2-second target, S-sequence data, C-cost function table
	int n;
	int t1;
	int t2;
	int *S;
	int **C;
	takeInput(&n, &t1, &t2, &S, &C);
	subSetSum(n, t1, t2, S, C);
	writeOutput(n, t1, t2, S, C);
	free(S);
	int i;
	free(C);
	return 0;
}
