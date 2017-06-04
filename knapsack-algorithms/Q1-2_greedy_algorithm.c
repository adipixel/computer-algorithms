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
//returns index of maximum benefit of an unit
int getMaxUnitIndex(int capacity, int elements, struct item items[elements])
{
	int i;
	int maxUnit_item_index=0;
	int maxUnit = (items[0].p)/(items[0].w);
	for (i = 0; i < elements; i++)
	{
		int curUnit = (items[i].p)/(items[i].w);
		if(maxUnit<curUnit)
		{
			maxUnit = curUnit;
			maxUnit_item_index = i;
		}
	}
	return maxUnit_item_index;
}
// returns index of element with max weight
int getMaxWeightIndex(int capacity, int elements, struct item items[elements])
{
	int i;
	int maxWeight_item_index=0;
	int maxWeight = items[0].w;
	for (i = 0; i < elements; i++)
	{
		if(maxWeight<items[i].w)
		{
			maxWeight = items[i].w;
			maxWeight_item_index = i;
		}
	}
	return maxWeight_item_index;
}

// returns index of element with min weight
int getMinWeightIndex(int capacity, int elements, struct item items[elements])
{
	int i;
	int minWeight_item_index=0;
	int minWeight = items[0].w;
	for (i = 0; i < elements; i++)
	{
		if(minWeight>items[i].w)
		{
			minWeight = items[i].w;
			minWeight_item_index = i;
			//printf("%d = %d\n",i+1, maxProfit);
		}
	}
	return minWeight_item_index;
}

// returns index of element with max profit
int getMaxIndex(int capacity, int elements, struct item items[elements])
{
	int i;
	int max_item_index=0;
	int maxProfit = 0;
	for (i = 0; i < elements; i++)
	{
		if(maxProfit<items[i].p)
		{
			maxProfit = items[i].p;
			max_item_index = i;
			//printf("%d = %d\n",i+1, maxProfit);
		}
	}
	return max_item_index;
}

//generic method to call respected methods according to the greedy algorithms
int getIndex(int greedyAlgoNo, int capacity, int elements, struct item items[elements])
{
	int index =0;
	switch(greedyAlgoNo)
	{
		case 1: //max profit first
			index = getMaxIndex(capacity,elements,items);
			return index;
		case 2:
			index = getMinWeightIndex(capacity,elements,items);
			return index;
		case 3:
			index = getMaxWeightIndex(capacity,elements,items);
			return index;
		case 4:
			index = getMaxUnitIndex(capacity,elements,items);
			return index;

	}
}

// gets the appropriate index, stores the respective element in the result data structure, and
// deletes the element from input data structure
void calculate(int greedyAlgoNo, int capacity, int elements, struct item items[elements])
{
	int i,k,m;
	struct item cached_items[elements];
	for (i = 0; i < elements; i++) {
		cached_items[i].w = items[i].w;
		cached_items[i].p = items[i].p;
	
	}
	int index=0, cachedIndex=elements-1;
	int profit =0, weight=0;
	int itemNos[elements];
	int j=0;
	for(i=0; i<elements; i++)
	{
		index = getIndex(greedyAlgoNo,capacity,elements-i,items);
		if((capacity - items[index].w)>=0)
		{
			capacity = capacity - items[index].w;
			profit = profit + items[index].p;
			weight = weight + items[index].w;
			if(index >= cachedIndex)
			{
				itemNos[j] = index+1;
				cachedIndex = index;
			}
			else
			{
				itemNos[j] = index;
				cachedIndex = index;
			}
			j++;
			for(k=index; k<(elements-index)-i; k++)
			{
				items[k] = items[k+1];
			}
		
		}
	}
	printf("Total Profit: %d, Total Weight: %d\n",profit,weight );
	printf("Knapsack: ");
	for(m=0; m<j;m++)
	{
		printf("\nItem%d {Profit: %d, Weight: %d} ",itemNos[m]+1, cached_items[itemNos[m]].p, cached_items[itemNos[m]].w );
	}
	printf("\n");
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

	struct item items[elements], g1_items[elements], g2_items[elements], g3_items[elements], g4_items[elements];

	for (i = 0; i < elements; i++) {
		items[i].w = w.val[i];
		items[i].p = p.val[i];
	}

	//duplicating input for each greedy algorithm
	for (i = 0; i < elements; i++) {
		g1_items[i].w = items[i].w;
		g1_items[i].p = items[i].p;
		g2_items[i].w = items[i].w;
		g2_items[i].p = items[i].p;
		g3_items[i].w = items[i].w;
		g3_items[i].p = items[i].p;
		g4_items[i].w = items[i].w;
		g4_items[i].p = items[i].p;
	}
	printf("-----------------------------------\n");
	printf("Greedy Algorithms\n");
	printf("-----------------------------------\n");
	printf("Number of elements : %d\n", elements);
	printf("Capacity: %d\n",capacity);
	printf("-----------------------------------\n");

	printf("Greedy1 (Max Benefit First)\n");
	calculate(1,capacity, elements, g1_items);
	printf("-----------------------------------\n");
	printf("Greedy2 (Minimum Weight First)\n");
	calculate(2,capacity, elements, g2_items);
	printf("-----------------------------------\n");
	printf("Greedy3 (Maximum Weight First)\n");
	calculate(3,capacity, elements, g3_items);
	printf("-----------------------------------\n");
	printf("Greedy4 (Maximum Benefit First)\n");
	calculate(4,capacity, elements, g4_items);


	fclose(fp);	
	return 0;
}
