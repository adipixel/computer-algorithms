#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
//structure containing the matrix
struct mat
{
	float matrix[100][100];
};
//declaration
struct mat makeMatrix(int n, int m, struct mat matD, char name);
void printMatrix(int m, struct mat matD, char name);
struct mat standardMultiplicationR(int m, struct mat matA, struct mat matB);
struct mat strassensMultiplicationR(int n, struct mat matA, struct mat matB);
struct mat addMatrix(int m, struct mat matA, struct mat matB);
struct mat minusMatrix(int m, struct mat matA, struct mat matB);
struct mat getMatrix(int i1, int i2, int j1, int j2, struct mat resMat);
struct mat joinMatrix(int n, struct mat c11, struct mat c12, struct mat c21, struct mat c22);
void standardMultiplication(int m, struct mat matA, struct mat matB);
void strassensMultiplication(int m, struct mat matA, struct mat matB);
float random1();
int getPowerOfTwo(int y);

//main function
void main(int argc, char *argv[])
{
	srand(time(NULL));
	int n = atoi(argv[1]);
	int m = getPowerOfTwo(n);
	
	struct mat *matA = malloc(sizeof(struct mat));
	struct mat *matB = malloc(sizeof(struct mat));

	//creating A and B matrix
	printf("Matrix A: \n");
	struct mat resA = makeMatrix(n, m, *matA, 'A');
	printf("Matrix B: \n");
	struct mat resB = makeMatrix(n, m, *matB, 'B');

	//call for Strassen's matrix multiplication
	strassensMultiplication(m, resA, resB);
	//call for Standard matrix multiplication
	standardMultiplication(m, resA, resB);
	

}
//Standard matrix multiplication function
void standardMultiplication(int m, struct mat matA, struct mat matB)
{
	struct mat stdResult = standardMultiplicationR(m, matA, matB);
	printf("Standard Multiplication Output: \n");
	printMatrix(m, stdResult, 'O');
	return;
}

//Strassen's matrix multiplication function
void strassensMultiplication(int m, struct mat matA, struct mat matB)
{
	struct mat strassenResult = strassensMultiplicationR(m, matA, matB);
	printf("Strassen’s Multiplication Output: \n");
	printMatrix(m, strassenResult, 'X');
	return;
}


/*------------------------------------------------------------------------*/
//function to generate random number matrix
struct mat makeMatrix(int n, int m, struct mat matD, char name)
{
	int i=0;
	for(i=0; i<m; i++)
	{
		int j=0;
		for (j=0; j<m; j++)
		{
			if(i>=n || j>=n)
			{
				matD.matrix[i][j] = 0.00;
			}
			else
			{
				matD.matrix[i][j] = random1();
			}
		}
	}
	
	printMatrix(m, matD, name);
	return matD;
}

// this prints the given matrix
void printMatrix(int m, struct mat matD, char name)
{
	//printf("Matrix %c\n", name);
	int i=0;
	for(i=0; i<m; i++)
	{
		int j=0;
		for (j=0; j<m; j++)
		{
			if((matD.matrix[i][j] <= (-0.00000000000000) && (-0.009) <= matD.matrix[i][j]))
			{
				matD.matrix[i][j] = +0.0;
			}
			printf("%.2f\t", matD.matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");

}

//this generates random number between -5.0 to 5.0
float random1()
{
	float temp = (float) (((double)(10)/RAND_MAX)*rand()-5.0);
    return temp;
}

//this returns the next nearest power of two
int getPowerOfTwo(int y)
{
	if(y == 1)
	{
		return 1;
	}
	int val =1;
 	while (true)
 	{
 		int j =1, i=0;
 		for(i=0; i<j; i++)
	 	{
	 		val = val * 2;
	 	}	
	 	if(val < y)
	 	{
	 		continue;
	 	}
	 	else
	 	{
	 		return val;
	 		break;
	 	}
	 	j++;
 	}
}

//actual standard multiplication function
struct mat standardMultiplicationR(int m, struct mat matA, struct mat matB)
{
	struct mat *stdResult = malloc(sizeof(struct mat));
	int i=0;
	for(i=0; i<m; i++)
	{
		int j=0;
		for(j=0; j<m; j++)
		{
			stdResult->matrix[i][j] =0.0;
			int k=0;
			for(k=0; k<m; k++)
			{
				stdResult->matrix[i][j] =stdResult->matrix[i][j] + (matA.matrix[i][k] * matB.matrix[k][j]);
			}
		}
	}
	return *stdResult;
}

// recursive Strassen's Multiplicaiton function
struct mat strassensMultiplicationR(int n, struct mat matA, struct mat matB)
{
	if(n>1)
	{
		//initialization
		struct mat *a = malloc(4*sizeof(struct mat));
		struct mat *b = malloc(4*sizeof(struct mat));
		struct mat *c = malloc(4*sizeof(struct mat));
		struct mat *mx = malloc(7*sizeof(struct mat));
		struct mat *temp = malloc(20*sizeof(struct mat));
		
		//setup
		a[0] = getMatrix(0, (n/2), 0, (n/2), matA);
		a[1] = getMatrix(0, (n/2), (n/2), n, matA);
		a[2] = getMatrix((n/2), n, 0, (n/2), matA);
		a[3] = getMatrix((n/2), n, (n/2), n, matA);

		b[0] = getMatrix(0, (n/2), 0, (n/2), matB);
		b[1] = getMatrix(0, (n/2), (n/2), n, matB);
		b[2] = getMatrix((n/2), n, 0, (n/2), matB);
		b[3] = getMatrix((n/2), n, (n/2), n, matB);

		//computing seven multiplications according to the algorithm
		temp[0] = addMatrix((n/2),a[0], a[3]);
		temp[1] = addMatrix((n/2), b[0], b[3]);
		mx[0] = strassensMultiplicationR((n/2), temp[0], temp[1]);
		

		temp[2] = addMatrix((n/2),a[2], a[3]);
		mx[1] = strassensMultiplicationR((n/2), temp[2], b[0]);
		
		temp[3] = minusMatrix((n/2), b[1], b[3]);
		mx[2] = strassensMultiplicationR((n/2), a[0], temp[3]);

		temp[4] = minusMatrix((n/2), b[2], b[0]);
		mx[3] = strassensMultiplicationR((n/2), a[3], temp[4]);

		temp[5] = addMatrix((n/2),a[0], a[1]);
		mx[4] = strassensMultiplicationR((n/2), temp[5], b[3]);

		temp[6] = minusMatrix((n/2),a[2], a[0]);
		temp[7] = addMatrix((n/2), b[0], b[1]);
		mx[5] = strassensMultiplicationR((n/2), temp[6], temp[7]);

		temp[8] = minusMatrix((n/2),a[1], a[3]);
		temp[9] = addMatrix((n/2), b[2], b[3]);
		mx[6] = strassensMultiplicationR((n/2), temp[8], temp[9]);


		//calculating part by part solution (c0, c1, c2 and c3)
		temp[10] = addMatrix((n/2), mx[0], mx[3]);
		temp[11] = minusMatrix((n/2),temp[10],mx[4]);
		c[0] = addMatrix((n/2), temp[11], mx[6]);

		temp[12] = addMatrix((n/2), mx[2], mx[4]);
		c[1] = temp[12];

		temp[13] = addMatrix((n/2), mx[1], mx[3]);
		c[2] = temp[13];

		temp[14] = addMatrix((n/2), mx[0], mx[2]);
		temp[15] = minusMatrix((n/2), temp[14], mx[1]);
		c[3] = addMatrix((n/2), (temp[15]), mx[5]);

		//call to build the calculated matrix
		struct mat *joinedMatrix = malloc (sizeof(struct mat));
		*joinedMatrix = joinMatrix(n, c[0], c[1], c[2], c[3]);
		return *joinedMatrix;

	}
	else
	{
		//multiplication
		struct mat *smat = malloc (sizeof(struct mat));
		smat->matrix[0][0] = matA.matrix[0][0] * matB.matrix[0][0];
		return *smat;
	}
}

//returns the addition of the two given matrices
struct mat addMatrix(int m, struct mat matA, struct mat matB)
{
	struct mat *addRes = malloc(sizeof(struct mat));
	int i=0;
	for(i=0; i<m; i++)
	{
		int j=0;
		for (j=0; j<m; j++)
		{
			addRes->matrix[i][j] = matA.matrix[i][j] + matB.matrix[i][j];
		}
	}
	return *addRes;
}

//returns the subtraction of the two given matrices
struct mat minusMatrix(int m, struct mat matA, struct mat matB)
{
	struct mat *addRes = malloc(sizeof(struct mat));
	int i=0;
	for(i=0; i<m; i++)
	{
		int j=0;
		for (j=0; j<m; j++)
		{
			addRes->matrix[i][j] = matA.matrix[i][j] - matB.matrix[i][j];
		}
	}
	return *addRes;
}

//returns a specific part of the given matrix
struct mat getMatrix(int i1, int i2, int j1, int j2, struct mat resMat)
{
	struct mat *addRes = malloc(sizeof(struct mat));
	int i=0,m=0;
	for(i=i1; i<i2; i++)
	{
		int j=0, n=0;
		for (j=j1; j<j2; j++)
		{
			addRes->matrix[m][n] = resMat.matrix[i][j];
			n= n+1;
		}
		m=m+1;
	}
	return *addRes;
}                        

//builds and returns a matrix by compiling given matrices
struct mat joinMatrix(int n, struct mat c11, struct mat c12, struct mat c21, struct mat c22)
{
	struct mat *addRes = malloc(sizeof(struct mat));
	int p=0, q=0;
	//for c-11
	int i1=0;
	for(i1=0; i1<n/2; i1++)
	{
		int j1=0, q = 0;
		for (j1=0; j1<n/2; j1++)
		{
			addRes->matrix[p][q] = c11.matrix[i1][j1];
			q = q+1;
		}
		p = p+1;
	}

	//for c-21
	p = n/2;
	q = 0;
	int i2=0;
	for(i2=0; i2<n/2; i2++)
	{
		int j2=0, q =0;
		for (j2=0; j2<n/2; j2++)
		{
			addRes->matrix[p][q] = c21.matrix[i2][j2];
			q = q+1;
		}
		p=p+1;
	}

	//for next half
	p = 0;
	q = (n/2);

	//for c-12
	int i3=0;
	for(i3=0; i3<n/2; i3++)
	{
		int j3=0, q=n/2;
		for (j3=0; j3<n/2; j3++)
		{
			addRes->matrix[p][q] = c12.matrix[i3][j3];
			q = q+1;
		}
		p=p+1;
	}

	//for c-22
	p = n/2;
	q = n/2;
	int i4=0;
	for(i4=0; i4<n/2; i4++)
	{
		int j4=0, q=n/2;
		for (j4=0; j4<n/2; j4++)
		{
			addRes->matrix[p][q] = c22.matrix[i4][j4];
			q = q + 1;
		}
		p=p+1;
	}

	return *addRes;
}
