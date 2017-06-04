#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct item
{
	int p;
	int w;
};
struct values
{
	int val[50];
};
struct mat
{
	int matrix[100][100];
};

//structuring data
struct values arrange(char* arr)
{
	struct values vals;
	const char s[2] = ",";
	char *token;
	int i=0;
	token = strtok(arr, s);
	while(token != NULL)
	{
		vals.val[i] = atoi(token);
		token = strtok(NULL, s);
		i++;
	}
	
	return vals;
}

//dynamic knapsack algorithm
void dynamic_knapsack(int elements, int capacity, struct item items[])
{
	int i,j,k;
	struct mat dk;
	int cached_max_profit =0;
	int cached_max_weight =0;
	int max_profit_row_number=0;
	for(i=0;i<capacity;i++)
	{
		dk.matrix[0][i] = 0;
	}

	for(i=1;i<=elements;i++)
	{
		for(j=1;j<=capacity;j++)
		{
			dk.matrix[i][0] = 0;
			int wk = items[i-1].w;
			int bk = items[i-1].p;
			if((wk<=j) && ((dk.matrix[i-1][j-wk] + bk) > (dk.matrix[i-1][j])))
			{
				dk.matrix[i][j] = dk.matrix[i-1][j-wk] + bk;
			}
			else
			{
				dk.matrix[i][j] = dk.matrix[i-1][j];
			}
			if(cached_max_profit < dk.matrix[i][j])
			{
				cached_max_profit = dk.matrix[i][j];
				cached_max_weight = j;
				max_profit_row_number = i;
			}
		}
	}

	/* //Test code: print matrix
	for (int i = 1; i <= elements; i++)
	{
		for (int j = 1; j <= capacity; j++)
		{
			printf("%d\t",dk.matrix[i][j]);
		}
		printf("\n");
	}*/

	//printing output
	printf("-----------------------------------\n");
	printf("Dynamic Knapsack\n");
	printf("-----------------------------------\n");
	printf("Total profit: %d\n", cached_max_profit);
	printf("Total weight: %d\n", cached_max_weight);
	printf("Knapsack Items: ");
	int knapsackItems[elements];
	j=0;
	for (i = max_profit_row_number; i > 0; i--)
	{
		if(cached_max_profit>0)
		{
			knapsackItems[j] = i;
			j++;

			cached_max_profit = cached_max_profit - items[i-1].p;
		}
	}

	for (i = 0; i < j; i++)
	{
		printf("Item%d ", knapsackItems[i]);
	}
	printf("\n-----------------------------------\n");
}

//driver method
int main(int argc, char const *argv[])
{
	int i;
	FILE *fp;
	char buff[255];

	fp = fopen(argv[1], "r");
	fscanf(fp, "%s", buff);
	int elements = atoi(buff);
	
	fscanf(fp, "%s", buff);
	struct values w = arrange(buff);
	fscanf(fp, "%s", buff);
	struct values p = arrange(buff);
	fscanf(fp, "%s", buff);
	int capacity = atoi(buff);

	struct item items[elements];

	for (i = 0; i < elements; i++) {
		items[i].w = w.val[i];
		items[i].p = p.val[i];
	}

	dynamic_knapsack(elements, capacity, items);

	fclose(fp);	
	return 0;
}