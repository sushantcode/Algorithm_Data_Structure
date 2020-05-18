// Demo of insertions into open address hash table using double hashing

#include <stdio.h>
#include <stdlib.h>

int main()
{
int *hash;
int inValue;
int i,j,m,n;
int h1,h2;

scanf("%d",&m);
if (m<1) {
  printf("Bad m %d\n",m);
  exit(0);
  }
hash=(int*) malloc(m*sizeof(int));
if (!hash) {
  printf("malloc failed\n");
  exit(0);
  }

// Flag all slots as never-used
for (i=0;i<m;i++)
  hash[i]=(-1);

// Insert a set of keys
scanf("%d",&inValue);
n=0;
while (inValue>=0 && n<m) {
  // Scan probe sequence until unused slot or key is found.
  i=h1=inValue%m;
  h2=inValue%(m-1)+1;
  while (hash[i]!=(-1) && hash[i]!=inValue)
    i=(i+h2)%m;
  if (hash[i]==inValue)
    printf("Duplicate key %d not inserted\n",inValue);
  else {
    hash[i]=inValue;
    n++;
    }
  scanf("%d",&inValue);
  }

if (m==n)
  printf("All slots used\n");

// Print table and useful trace info
for (i=0;i<m;i++) {
  printf("%d %d",i,hash[i]);
  if (hash[i]!=(-1)) {
    j=h1=hash[i]%m;
    h2=hash[i]%(m-1)+1;
    printf(" %d %d: ",h1,h2);
    // Output subscripts of accessed probe sequence slots.
    while (printf(" %d",j),hash[j]!=hash[i])
      j=(j+h2)%m;
    }
  printf("\n");
  }

free(hash);
}
