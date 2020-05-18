#include <stdio.h>

int binSearchLeft(int *count, int n, int k, int key)
{
	int high;
	high = n - 1;
	while(high >= 0)
	{
		if (count[high] == key)
		{
			return high; 
		}
		high = high - 1;
	}
	return k;	
}

int binSearchRight(int *count, int n, int l, int key)
{
	int low;
	low = 0;
	while(low < n)
	{
		if (count[low] == key)
		{
			return low;
		}
		low++;
	}
	return l;	
}

int main()
{
    printf("Enter the number of counters n: ");
	int n;
	scanf("%d", &n);
	int count[n];
	int map[n];
	int index[n];
	int j;
	for(j = 0; j < n; j++)
	{
		count[j] = 0;
		map[j] = j;
		index[j] = j;
	}                                                                                                                                                
	printf("\nEnter your command options: ");
	int command;
	scanf("%d", &command);
	while(command != 0)
	{
		int i = 0;
		int k = 0;
		int l = 0;
		switch (command)
		{
			case 1:
			{
				//execute command 1
				printf("\nPrint by index: \n");
				for (i = 0; i < n; i++)
					printf("%d %d\n", i, count[map[i]]);
				printf("\n----------------\n");
				break;
			}
			case 2:
			{
				//execute command 2 operation
				printf("\nPrint by count: \n");
				for (i = 0; i < n; i++)
					printf("%d %d\n", index[i], count[i]);
				printf("\n---------------\n");
				break;
			}
			case 3:
			{
				//execute command 3 operation
				printf("\nEnter indexed position to be increased: ");
				scanf("%d", &k); 
				int result = binSearchLeft(count, n, map[k], count[map[k]]);
				int temp = count[map[k]];
				int temp1 = index[map[k]];
				count[map[k]] = count[result];
				index[map[k]] = index[result];
				count[result] = temp + 1;
				index[result] = temp1;
				int temp2 = map[index[map[k]]];
				map[index[map[k]]] = map[index[result]];
				map[index[result]] = temp2;
				break;
			}
			case 4:
			{
				//execute command 4 operation
				printf("\nEnter idexed position to be decreased: ");
				scanf("%d", &l); 
				int result1 = binSearchRight(count, n, map[l], count[map[l]]);
				int temp = count[map[l]];
				int temp1 = index[map[l]];
				count[map[l]] = count[result1];
				index[map[l]] = index[result1];
				count[result1] = temp - 1;
				index[result1] = temp1;
				int temp2 = map[index[map[l]]];
				map[index[map[l]]] = map[index[result1]];
				map[index[result1]] = temp2;	
				break;
			}
			case 5:
			{
				//execute command 5 operation
				printf("\nEnter lower range: ");
				int lower;
				scanf("%d", &lower);
				printf("\nEnter upper range: ");
				int upper;
				scanf("%d", &upper);
				int m;
				int c = 0;
				for(m = 0; m < n; m++)
				{
					if((count[m] >= lower) && (count[m] <= upper))
					{
						c++;
					}
				}
				printf("\n%d counters valued between %d and %d \n", c, lower, upper);
				break;
			}
			default:
			{
				break;
			}
		}
		printf("\nEnter your command options: ");
		scanf("%d", &command);
	}
    return 0;
}
