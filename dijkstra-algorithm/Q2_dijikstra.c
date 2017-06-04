#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct mat
{
	int matrix[100][100];
};
struct values
{
	int col;
	int val[50];
};
struct solution
{
	int node;
	int shortest_distance;
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
	vals.col = i; //adds one col extra
	
	return vals;
}
// implementation dijikstra's algorithm
void dijikstra(int size, struct mat input)
{
	int i,j,k,m,n;
	//considering s0 as starting node
	struct solution sol[size];
	int updated_distances[size], offset=0;
	for(i=0;i<size;i++)
	{
		updated_distances[i]=10000;
	}
	//for s0 to s0
	sol[0].node = 0;
	sol[0].shortest_distance =0;
	int solCounter=1;

	for(i=0;i<size;i++)
	{
		int minDistance=-99;
		int minDistanceIndex =0;
		int flag =0, sflag=0;
		for(j=0;j<size;j++)
		{
			if(i!=j)
			{
				int cur = input.matrix[i][j];
				
				if(updated_distances[j] > cur)
				{
					if(cur>0)
					{
						for(m=0;m<i;m++)
						{
							if(sol[m].node == j)
							{
								flag = 1;
							}
						}
						if(flag ==0)
						{
							updated_distances[j] = cur;
						}
					}
				}

				if((cur < minDistance || minDistance==-99) && (cur>0))
				{
					for(k=0;k<i+1;k++)
					{
						if(sol[k].node == j)
						{
							//printf("index found: %d\n",j);
							sflag = 1;
						}
					}
					if (sflag == 0)
					{
						minDistance = cur;
						minDistanceIndex = j;
					}
					else
					{
						minDistance = updated_distances[i+1];
						minDistanceIndex = i+1;
						sflag =1;
					}
				}
			}
		}
		if(sflag == 0)
		{
			sol[i+1].node = minDistanceIndex;
			sol[i+1].shortest_distance = minDistance+offset;
			offset = minDistance+offset;
		}
		else
		{
			sol[i+1].node = minDistanceIndex;
			sol[i+1].shortest_distance = minDistance;
		}

	}

/*	for (int i = 0; i < size; ++i)
	{
		printf("%d ", updated_distances[i]);
	}
	printf("\n");*/
	printf("-----------------------------------\n");
	printf("Dijikstra's Algorithm\n");
	printf("-----------------------------------\n");
	printf("Shortest Path: {");
	for (i = 0; i < size; ++i)
	{
		if(sol[i].shortest_distance == 10000)
		{
			sol[i].shortest_distance = -99;
		}
		printf("(S%d, %d)", sol[i].node, sol[i].shortest_distance);
		if(i<size-1)
		{
			printf(", ");
		}
	}
	printf("}\n");

}

int main(int argc, char const *argv[])
{
	int i,j,k;
	FILE *fp;
	char buff[255];
	int size;

	fp = fopen(argv[1], "r");
		
	fscanf(fp, "%s", buff);
	struct values w = arrange(buff);	
	size = w.col;
	struct mat input;
	for(k=0;k<size;k++)
	{
		for (i = 0; i < size; i++) 
		{
			input.matrix[k][i] = w.val[i];
		}
		fscanf(fp, "%s", buff);
		w = arrange(buff);
	}

/*	 //Test code: print input matrix
	for(k=0;k<size;k++)
	{
		for (i = 0; i < size; i++) 
		{
			printf("%d ",input.matrix[k][i]);
		}
		printf("\n");
	}
*/
	dijikstra(size, input);

	fclose(fp);	
	return 0;
}