//소프트웨어 글로벌 프로젝트(A)
//1492018 서희선
//Minesweeper 프로그램
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>

typedef struct Field{
	int *data;
}Field;

void init(Field *field, int n, int m);
int IsInField(int i, int j, int n, int m);
void setMine(int row, int col, Field *field, int n, int m);
void printField(int nField, Field *field, int n, int m);

int main(int argc, char *argv[])
{ 
	int n, m; 
	int nField = 1; 
	Field *field;
	FILE *fp = NULL;

	if(argc!=1)
	{
		fp = fopen(argv[1], "r");
		if(fp == NULL)
		{
			printf("File Open ERROR for reading\n");
			return 0;
		}
	}

	for (;;)
	{ 
		int i, j;

		if (argc == 1)
			scanf(" %d %d", &n, &m); 
		else
			fscanf(fp, " %d %d", &n, &m);

		if (n == 0 && m == 0) break; 

		field = (Field*)malloc(sizeof(Field)*n);
		for(i=0; i<n; i++)
		{
			(field+i)->data = (int*)malloc(sizeof(int)*m);
		}

		init(field, n, m); 

		for (i=0; i<n; i++) 
		{ 
			char line[200];  

			if(argc == 1)
				scanf(" %s", line); 
			else
				fscanf(fp, " %s", line);

			for (j=0; j<m; j++) 
			{ 
				char currentChar = line[j]; 
				if (currentChar == '*')
				{ 
					setMine(i, j, field, n, m); 
				} 
			} 
		} 

		printField(nField, field, n, m);
		++nField; 

		for(i=0; i<n; i++)
		{
			free((field+i)->data);
		}
		free(field);
	} 
	if(argc!=1)
		fclose(fp);

	return 0; 
} 
void init(Field *field, int n, int m) 
{     
	int i, j; 
	for (i=0; i<n; i++)
	{ 
		for (j=0; j<m; j++)
		{ 
			field[i].data[j] = 0; 
		}
	} 
} 
int IsInField(int i, int j, int n, int m)
{ 
	return i >= 0 && i < n && j >=0 && j < m; 
} 
void setMine(int row, int col, Field *field, int n, int m)
{ 
	int i, j; 
	field[row].data[col] = -1;	//지뢰가 있는 곳
	for (i=-1; i<=1; i++)
	{ 
		for (j=-1; j<=1; j++)
		{ 
			if (IsInField(row+i, col+j, n, m) && field[row+i].data[col+j] != -1)	//그래프안의 점, 자기 자신(지뢰가 있는 곳)은 세지 않음
			{ 
				++field[row+i].data[col+j]; 
			} 
		} 
	} 
} 
void printField(int nField, Field *field, int n, int m)
{ 
	int i, j; 
	printf("\nField #%d:\n", nField); 
	for (i=0; i<n; i++)
	{ 
		for (j=0; j<m; j++)
		{ 
			int x = field[i].data[j]; 

			if (x == -1) //지뢰가 있는 곳
			{
				printf("*"); 
			}
			else
			{ 
				printf("%d", x); 
			} 
		} 
		printf("\n"); 
	} 
	printf("\n");
} 