#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void create(char *input_file);
int random1(int p, int r);
int compare(char *str1In, char *str2In);
int foundFlag = 0, exitFlag = 1;
int size=0;
typedef struct
	{
		char firstName[20];
		char lastName[20];
		char phone[20];
	} Contact;

Contact contacts[1000];

void create(char *input_file)
{
	FILE *file_ptr;
	char buff[10000];

	file_ptr =fopen(input_file,"r");
	if (!file_ptr)
	{
		printf("Invalid file. \n");;
	}
	

	char *split;
	
	while (fgets(buff,10000, file_ptr)!=NULL)
	{
		split = strtok(buff, " ,");
		
		Contact *list = (Contact*) malloc (sizeof (Contact));
		
		strcpy(contacts[size].firstName, split);
		split = strtok(NULL, " ,");
		strcpy(contacts[size].lastName, split);
		split = strtok(NULL, " ,\n");
		strcpy(contacts[size].phone, split);

		size++;
	}	

	fclose(file_ptr);	
}

void printList() 
{
	int i=0;
   for(i=0; i<=size; i++)
   {
   	printf(" %s %s %s \n",contacts[i].firstName, contacts[i].lastName, contacts[i].phone );
   }

 }

/* -------------------------------------------------- */


int random1(int p, int r)
{
    return p + rand()%(r - p + 1); 
}

int compare(char *str1In, char *str2In)
{
	int ret;
	char str1[15];
    char str2[15];

   	strcpy(str1, str1In);
   	strcpy(str2, str2In);

	int length = sizeof(str2);
 	if(sizeof(str1) > sizeof(str2))
 	{
 		length = sizeof(str1);
 	}
 	int i;
	for(i = 0; length > i; i++){
 	 str1[i] = tolower(str1[i]);
 	 str2[i] = tolower(str2[i]);
	}
	ret = strcmp(str1, str2);
	if(ret < 0)
   {
      return -1;
   }
   else if (ret == 0)
   {
   	 return 0;
   }
   else
   {
      return 1;
   }
   
}

int partition(Contact *A, int p, int q)
{
	int pi = random1(p,q);
	Contact pivot = A[pi];

	Contact temp1 = A[pi];
	A[pi] = A[q];
	A[q] = temp1;

	int i = p-1;
	//int	pivot = q;
	int j=0;
	for(j=p; j<=q; j++)
	{
		if(compare(A[j].lastName, pivot.lastName) == 0)
		//if(strcmp(A[j].lastName, pivot.lastName) == 0)
		{
			if(compare(A[j].firstName, pivot.firstName) < 0)
			{
				i++;
				Contact temp = A[i];
				A[i] = A[j];
				A[j] = temp;
			}
			else if(compare(A[j].firstName, pivot.firstName) == 0)
			{
				if(compare(A[j].phone, pivot.phone) < 0)
				{
					i++;
					Contact temp = A[i];
					A[i] = A[j];
					A[j] = temp;
				}
			}
		}
		else if(compare(A[j].lastName, pivot.lastName) < 0)
		{
			i++;
			Contact temp = A[i];
			A[i] = A[j];
			A[j] = temp;

		}
	}
	Contact temp = A[i+1];
			A[i+1] = A[q];
			A[q] = temp;
	return i+1;
}

void randomQuick(Contact *A, int p, int r)
{
		/*int i = random(p,r);
	Contact temp = A[i];
			A[i] = A[r];
			A[r] = temp;*/

		if(p < r)
		{
			int q = partition(A,p,r);
			randomQuick(A,p,q-1);
			randomQuick(A,q+1,r);
		}
}
void sort_contact()
{
	randomQuick(contacts,0,size-1);
}


int search(char *key1, char *key2)
{
	int i;
	int low = 0;
	int high = 0;
	
	int mid;
	high = size-1;
	while(low <= high)
	{
		mid = (low + high)/2;
		if (strcmp(key2, contacts[mid].lastName) == 0)
		{
			if(strcmp(key1, contacts[mid].firstName) == 0)
			{
				printf("Name Found\n");
				foundFlag = mid;
				return 0;
				//exit(0);
				
			}
			else if(strcmp(key2, contacts[mid].firstName) > 0)
			{
				high = high;
				low = mid + 1;
			}
			else
			{
				low = low;
				high = mid - 1;
			}
		}
		else if(strcmp(key2, contacts[mid].lastName) > 0)
		{
			high = high;
			low = mid + 1;
		}
		else
		{
			low = low;
			high = mid - 1;
		}
	}
	printf("name not found\n");
	foundFlag =0;
}



/*-----------------------------------------------------*/

void insert(char* name, char* phone_number)
{
	char  fn[20], ln[20];
	char *first, *last;
	first = strtok(name, ",");
	last = strtok(NULL, "");

	strcpy(contacts[size].firstName, first);
	strcpy(contacts[size].lastName, last);
	strcpy(contacts[size].phone, phone_number);
	size++;
	sort_contact();
	printf("Added to the directory and sorted!\n");
}

void delete(char* name)
{
	char  fn[20], ln[20];
	char *first, *last;
	int c;
	first = strtok(name, ",");
	last = strtok(NULL, "");

	search(first, last);

	if (foundFlag != 0)
	{
		for (c = foundFlag; c<size; c++)
		{
			contacts[c] = contacts[c+1];
		}
		printf("Record deleted from the directory!\n");
	}
	else
	{
		printf("Record not found!\n");
	}



}


/* ---------------------------------------------- */
int main(int argc, char **argv)
{
	create(argv[1]);
	char search_fn[20], search_ln[20], fn[20], ln[20], ph[20], full[50];
	int yn;
	
	sort_contact();
	//printList();
	printf("Contacts are sorted. Directory is ready to search!\n");

	printf("Do you want to see the sorted list? (1/2) \n");
	printf("1. Yes \n");
	printf("2. No \n");
	printf("Enter choice:");
 	scanf("%d",&yn);
 	if(yn == 1)
 	{
 		printList();
 	}

 	printf("Inserting into directory.\n");
 	printf("Enter Fulll name: ");
 	scanf("%s %s", &fn, &ln);
 	printf("Enter phone number: ");
 	scanf("%s",&ph);

 	strcat(fn, ",");
 	strcat(fn, ln);

 	insert(fn, ph);
	printf("Do you want to see the sorted list? (1/2) \n");
	printf("1. Yes \n");
	printf("2. No \n");
	printf("Enter choice:");
 	scanf("%d",&yn);
 	if(yn == 1)
 	{
 		printList();
 	}


	printf("Deleting from directory.\n");
 	printf("Enter Fulll name: ");
 	scanf("%s %s", &fn, &ln);
 	strcat(fn, ",");
 	strcat(fn, ln);
 	delete(fn);

	printf("Do you want to see the sorted list? (1/2) \n");
	printf("1. Yes \n");
	printf("2. No \n");
	printf("Enter choice:");
 	scanf("%d",&yn);
	if(yn == 1)
 	{
 		printList();
 	}


	printf("Enter full name to search in the directory: \n");
 	scanf("%s %s",&search_fn, &search_ln);

	search(search_fn, search_ln);

	return 0;
}
