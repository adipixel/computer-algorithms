#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
//struct of matrix
struct mat
{
	int matrix[100][100];
	int row;
	int col;
	int quad;
};
//char matrix for printing results
struct charMat
{
	char matrix[100][100];
};

struct mat makeMatrix(int m, struct mat matD);
void printMatrix(int m, struct mat matD);
int powerTwo(int n);
struct mat setHole(int n, struct mat board);
struct mat trominoTile(int n, struct mat board);
struct mat getMatrix(int i1, int i2, int j1, int j2, struct mat resMat);
struct mat getAllocated(int n, struct mat board);
struct mat joinMatrix(int n, struct mat c11, struct mat c12, struct mat c21, struct mat c22);
int tile = 1;

//main function
int main(int argc, char const *argv[])
{
	int n = atoi(argv[1]);
	int m = powerTwo(n);
	
	struct mat *matA = malloc(sizeof(struct mat));
	
	matA->row = atoi(argv[2]);
	matA->col = atoi(argv[3]);
	
	//check for valid inputs
	if(m<=matA->row || m<=matA->col)
	{
		printf("Hole position out of range!\n\n");
		return;
	}

	//constructing the board and setting the hole at given position
	struct mat resA = makeMatrix(m, *matA);
	struct mat board = getAllocated(m, setHole(m,resA));
	
	//the tromino tile algorithm
	struct mat res = trominoTile(m, board);
	printf("Tromino tiling:\n\n");
	printMatrix(m, res);
	return 0;
}

// this is the tromino algorithm function
struct mat trominoTile(int n, struct mat board)
{
	//if n==2, then find x and place number in rest
	//return board
	//else
	//find quad
	//place 3 tiles in the corners of other quads
	//divide n/2  four recursive calls
	//join n/2 matrices into n and return

	if(2==n)
	{
		int i;
		for(i=0;i<n;i++)
		{
			int j;
			for (j=0; j<n; j++)
			{
				if(board.matrix[i][j] == 0)
				{
					if(tile > 9)
					{
						tile = 1;
					}
					board.matrix[i][j] = tile;
				}
			}
		}
		tile = tile + 1;
		return board;
	}
	else
	{
		if(tile > 9)
			{
				tile = 1;
			}
		//placing tiles at corners of other quadrants
		if(board.quad == 1)
		{
			//board.matrix[(n/2)-1][(n/2)-1] = tile; //quad1
			board.matrix[(n/2)-1][(n/2)] = tile; //quad2
			board.matrix[(n/2)][(n/2)-1] = tile; //quad3
			board.matrix[(n/2)][(n/2)] = tile; //quad4
			tile = tile + 1;
		}
		else if(board.quad == 2)
		{
			board.matrix[(n/2)-1][(n/2)-1] = tile; //quad1
			//board.matrix[(n/2)-1][(n/2)] = tile; //quad2
			board.matrix[(n/2)][(n/2)-1] = tile; //quad3
			board.matrix[(n/2)][(n/2)] = tile; //quad4
			tile = tile + 1;
		}
		else if (board.quad == 3)
		{
			board.matrix[(n/2)-1][(n/2)-1] = tile; //quad1
			board.matrix[(n/2)-1][(n/2)] = tile; //quad2
			//board.matrix[(n/2)][(n/2)-1] = tile; //quad3
			board.matrix[(n/2)][(n/2)] = tile; //quad4
			tile = tile + 1;
		}
		else
		{
			board.matrix[(n/2)-1][(n/2)-1] = tile; //quad1
			board.matrix[(n/2)-1][(n/2)] = tile; //quad2
			board.matrix[(n/2)][(n/2)-1] = tile; //quad3
			//board.matrix[(n/2)][(n/2)] = tile; //quad4
			tile = tile + 1;
		}


		struct mat *c = malloc(4*sizeof(struct mat));
		struct mat *d = malloc(4*sizeof(struct mat));
		
		c[0] = getAllocated(n/2, getMatrix(0, (n/2), 0, (n/2), board));
		c[1] = getAllocated(n/2, getMatrix(0, (n/2), (n/2), n, board));
		c[2] = getAllocated(n/2, getMatrix((n/2), n, 0, (n/2), board));
		c[3] = getAllocated(n/2, getMatrix((n/2), n, (n/2), n, board));

		//dividing the matrix and recursive calls tromino function
		d[0] = trominoTile(n/2, c[0]);
		d[1] = trominoTile(n/2, c[1]); 
		d[2] = trominoTile(n/2, c[2]);
		d[3] = trominoTile(n/2, c[3]);

		//call to build the result matrix
		struct mat *joinedMatrix = malloc (sizeof(struct mat));
		*joinedMatrix = joinMatrix(n, d[0], d[1], d[2], d[3]);
		return *joinedMatrix;
	}


}

//sets the hole in the board
struct mat setHole(int n, struct mat board)
{
	board.matrix[board.row][board.col] = 120;
	return board;

}

// get location of the filled / allocated quadrant
struct mat getAllocated(int n, struct mat board)
{
	if(board.row >= 0 && board.row<(n/2))
	{
		if(board.col >= 0 && board.col < (n/2))
		{
			board.quad = 1;	
		}
		else
		{
			board.quad = 2;
		}
	}
	else if(board.row >= (n/2) && board.row < n)
	{
		if(board.col >= 0 && board.col < (n/2))
		{
			board.quad = 3;	
		}
		else
		{
			board.quad = 4;
		}
		
	}
	return board;
}

//constructs the matrix/board
struct mat makeMatrix(int m, struct mat matD)
{
	int i=0;
	for(i=0; i<m; i++)
	{
		int j=0;
		for (j=0; j<m; j++)
		{
			matD.matrix[i][j] = 0;
		}
	}
	return matD;
}

//prints the given matrix/board
void printMatrix(int m, struct mat matD)
{
	struct charMat *board = malloc(sizeof(struct charMat));
	int i=0;
	for(i=0; i<m; i++)
	{
		int j=0;
		for (j=0; j<m; j++)
		{
			if(matD.matrix[i][j] == 120)
			{
				board->matrix[i][j] = 120;
			}
			else
			{
				board->matrix[i][j] = '0'+matD.matrix[i][j];
			}
			printf("%c ", board->matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");

}

//this returns the n th power of two
int powerTwo(int n)
{
	int i, total = 1;
	for(i=1;i<=n;i++)
	{
		total = total * 2;
	}
	return total;
}

//returns a sub matrix of the given matrix
struct mat getMatrix(int i1, int i2, int j1, int j2, struct mat resMat)
{
	struct mat *addRes = malloc(sizeof(struct mat));
	int i=0,m=0;
	for(i=i1; i<i2; i++)
	{
		int j=0, n=0;
		for (j=j1; j<j2; j++)
		{
			if(resMat.matrix[i][j] != 0)
			{
				addRes->row = m;
				addRes->col = n;
			}
			addRes->matrix[m][n] = resMat.matrix[i][j];
			n= n+1;
		}
		m=m+1;
	}
	struct mat board = getAllocated(m,*addRes);
	return board;
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
