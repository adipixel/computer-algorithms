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
int optimal=0;
int optimal_weight = 0;
int itemNo_array[20];
int opt_items_len =0;
void combinations(int n, int r, int *arr, int size, int capacity, struct item items[n]);

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
//if optimal, stores it into global variables
void getOptimal(int wsum, int psum, int *arr, int capacity, int size)
{
	
	if(capacity>=wsum)
	{
		if(optimal<psum)
		{
			optimal = psum;
			opt_items_len =size;
			optimal_weight = wsum;
		}
	}
}
//finds combinations for the brute force technique
void combinations(int elements, int r, int *arr, int size, int capacity, struct item items[elements])
{
	int i,j;
	for(i=elements;i>=r; i--)
	{

		arr[(r)-1]=i;
		if(r>1)
		{
			combinations(i-1,r-1,arr,size, capacity,items);
		}
		else
		{
			
			
			//write logic here
			int wsum =0, psum=0;
			for(j=0; j<size; j++)
			{
				wsum = wsum + items[arr[j]-1].w;
				psum = psum + items[arr[j]-1].p;
			}
			if(wsum<=capacity)
			{
				if(optimal<psum)
				{
					
					for (j = 0; j < size; j++)
					{
						itemNo_array[j] = arr[j];
					}
				}
			}
			getOptimal(wsum,psum,arr,capacity,size);

		}
	}
}
//Driver method
int main(int argc, char const *argv[])
{
	int i,j,k;
	FILE *fp;
	char buff[255];
	printf("-----------------------------------\n");
	printf("Brute Force\n");
	printf("-----------------------------------\n");
	fp = fopen(argv[1], "r");
	fscanf(fp, "%s", buff);
	int elements = atoi(buff);
	printf("Number of elements : %d\n", elements);
	
	//reading data from input file
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


	int *arr =malloc(10*sizeof(int));
	for (i = 1; i <= elements; i++)
	{
		combinations(elements,i,arr,i,capacity,items);
	}


	printf("Capacity: %d\n",capacity );
	printf("Total weight: %d\n", optimal_weight);
	printf("Total profit: %d\n", optimal);
	printf("Knapsack: " );
	for (i = 0; i < opt_items_len; i++)
	{
		printf("item%d ", itemNo_array[i]);
	}
	printf("\n");

	fclose(fp);	
	return 0;
}
