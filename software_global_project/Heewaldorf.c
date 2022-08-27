//2015.11.23
//1492018 ����
//����Ʈ����۷ι�������Ʈ(A)
//Where��s Waldorf? (Program #2)
//�ѱ� & ���� ȥ�� ����

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define Exist 1
#define NotExist 0

typedef struct COL{
	int is_eng; //����=1, �ѱ�=0
	char *ch;
}COL;
typedef struct ROW {
	int len; //���ڿ��� ���� �� (�׷����� �� ��)
	COL *col;
}ROW;
typedef struct Graph{
	int line; //�׷����� �� ��
	ROW *row;
}Graph;

void Malloc_grid(Graph *grid); //argc==1�� �� grid ���� 
void f_Malloc_grid(Graph *grid, FILE **fp); //argc==2�� �� grid ����
void Malloc_wordlist(Graph *list); //argc==1�� �� wordList ����
void f_Malloc_wordlist(Graph *list, FILE **fp); //argc==2�� �� wordList ����
void FREE_graph(Graph *graph); //�׷��� �����Ҵ�����
int Search3(int k, int r, int c, Graph *grid, Graph *wordlist); //grid�� �ش� ���(r, c)��ġ�� ���ڿ� wordList�� k��° �ܾ� ���� ��
void Search2(int k, Graph *grid, Graph *wordlist); //�ܾ ���� ��(r)�� ��(c)�� ����
void Search1(Graph *grid, Graph *wordlist); //wordList���� ���� k��° �ܾ� ����

int main(int argc, char *argv[])
{
	int t, testcase;
	Graph grid, wordList;
	FILE *fp = NULL;

	if (argc == 1)
	{
		scanf(" %d", &testcase);

		for (t = 0; t<testcase; t++)
		{
			Malloc_grid(&grid);
			Malloc_wordlist(&wordList);

			printf("\ncase #%d:\n", t + 1);
			Search1(&grid, &wordList);

			FREE_graph(&grid);
			FREE_graph(&wordList);
			printf("\n");
		}
	}
	else if (argc == 2)
	{
		fp = fopen(argv[1], "r");
		if (fp == NULL)
		{
			printf("File Open ERROR for reading\n");
			return 0;
		}

		fscanf(fp, " %d", &testcase);

		for (t = 0; t<testcase; t++)
		{
			f_Malloc_grid(&grid, &fp);
			f_Malloc_wordlist(&wordList, &fp);

			printf("\ncase #%d:\n", t + 1);
			Search1(&grid, &wordList);

			FREE_graph(&grid);
			FREE_graph(&wordList);
			printf("\n");
		}
		fclose(fp);
	}
	else
	{
		printf("INPUT ERROR!\n");
		return 0;
	}
	return 0;
}
void Malloc_grid(Graph *grid)
{
	int m, n, i, j, c, len;
	char temp[130];

	scanf(" %d %d", &m, &n);
	grid->line = m;
	grid->row = (ROW*)malloc(sizeof(ROW)*m); //�� �Ҵ�

	for (i = 0; i<m; i++)
	{
		grid->row[i].len = n;
		grid->row[i].col = (COL*)malloc(sizeof(COL)*n); //�� �Ҵ�
		j=0;

		scanf(" %s", temp);
		len = strlen(temp);

		for(c=0; c<len; )
		{
			if(*(temp+c) & 0x80) //�ѱ�
			{
				grid->row[i].col[j].is_eng=0;
				grid->row[i].col[j].ch = (char*)malloc(sizeof(char)*2); //1���� �Ҵ�
				memcpy(grid->row[i].col[j].ch, temp + c, sizeof(char) * 2);
				c+=2;
			}
			else //����
			{
				grid->row[i].col[j].is_eng=1;
				grid->row[i].col[j].ch = (char*)malloc(sizeof(char)*1);
				if(65 <= temp[c] && temp[c] <= 90) //�빮���̸�
					temp[c] = tolower(temp[c]);
				memcpy(grid->row[i].col[j].ch, temp + c, sizeof(char) * 1);
				c+=1;
			}
			j++;
		}
	}
}
void f_Malloc_grid(Graph *grid, FILE **fp)
{
	int m, n, i, j, c, len;
	char temp[130];

	fscanf(*fp, " %d %d", &m, &n);
	grid->line = m;
	grid->row = (ROW*)malloc(sizeof(ROW)*m); //�� �Ҵ�

	for (i = 0; i<m; i++)
	{
		grid->row[i].len = n;
		grid->row[i].col = (COL*)malloc(sizeof(COL)*n); //�� �Ҵ�
		j=0;

		fscanf(*fp, " %s", temp);
		len = strlen(temp);

		for(c=0; c<len; )
		{
			if(*(temp+c) & 0x80) //�ѱ�
			{
				grid->row[i].col[j].is_eng=0;
				grid->row[i].col[j].ch = (char*)malloc(sizeof(char)*2); //1���� �Ҵ�
				memcpy(grid->row[i].col[j].ch, temp + c, sizeof(char) * 2);
				c+=2;
			}
			else //����
			{
				grid->row[i].col[j].is_eng=1;
				grid->row[i].col[j].ch = (char*)malloc(sizeof(char)*1);
				if('A' <= temp[c] && temp[c] <= 'Z') //�빮���̸�
					temp[c] = tolower(temp[c]);
				memcpy(grid->row[i].col[j].ch, temp + c, sizeof(char) * 1);
				c+=1;
			}
			j++;
		}
	}
}
void Malloc_wordlist(Graph *list)
{
	int k, i, j, c, len;
	char temp[130];

	scanf(" %d", &k);

	list->line = k;
	list->row = (ROW*)malloc(sizeof(ROW)*k); //�� �Ҵ�

	for (i = 0; i<k; i++)
	{
		scanf(" %s", temp);
		list->row[i].col = (COL*)malloc(sizeof(COL)*strlen(temp)); //�� �Ҵ�
		j=0;
		len = strlen(temp);

		for(c=0; c<len; )
		{
			if(*(temp+c) & 0x80) //�ѱ�
			{
				list->row[i].col[j].is_eng=0;
				list->row[i].col[j].ch = (char*)malloc(sizeof(char)*2); //1���� �Ҵ�
				memcpy(list->row[i].col[j].ch, temp + c, sizeof(char) * 2);
				c+=2;
			}
			else //����
			{
				list->row[i].col[j].is_eng=1;
				list->row[i].col[j].ch = (char*)malloc(sizeof(char)*1);
				if(65 <= temp[c] && temp[c] <= 90) //�빮���̸�
					temp[c] = tolower(temp[c]);
				memcpy(list->row[i].col[j].ch, temp + c, sizeof(char) * 1);
				c+=1;
			}
			j++;
		}
		list->row[i].len = j;
	}
}
void f_Malloc_wordlist(Graph *list, FILE **fp)
{
	int k, i, j, c, len;
	char temp[130];

	fscanf(*fp, " %d", &k);

	list->line = k;
	list->row = (ROW*)malloc(sizeof(ROW)*k); //�� �Ҵ�

	for (i = 0; i<k; i++)
	{
		fscanf(*fp, " %s", temp);
		list->row[i].col = (COL*)malloc(sizeof(COL)*strlen(temp)); //�� �Ҵ�
		j=0;
		len = strlen(temp);

		for(c=0; c<len; )
		{
			if(*(temp+c) & 0x80) //�ѱ�
			{
				list->row[i].col[j].is_eng=0;
				list->row[i].col[j].ch = (char*)malloc(sizeof(char)*2); //1���� �Ҵ�
				memcpy(list->row[i].col[j].ch, temp + c, sizeof(char) * 2);
				c+=2;
			}
			else //����
			{
				list->row[i].col[j].is_eng=1;
				list->row[i].col[j].ch = (char*)malloc(sizeof(char)*1);
				if(65 <= temp[c] && temp[c] <= 90) //�빮���̸�
					temp[c] = tolower(temp[c]);
				memcpy(list->row[i].col[j].ch, temp + c, sizeof(char) * 1);
				c+=1;
			}
			j++;
		}
		list->row[i].len = j;
	}
}
void FREE_graph(Graph *graph)
{
	int r, c;
	for(r=0; r<graph->line; r++)
	{
		for (c = 0; c < graph->row[r].len; c++)
		{
			free(graph->row[r].col[c].ch);
		}
		free(graph->row[r].col);
	}
	free(graph->row);	
}
int Search3(int k, int r, int c, Graph *grid, Graph *wordlist)
{
	int x[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int y[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	int i, rr, cc, kk=0;

	if(grid->row[r].col[c].is_eng != wordlist->row[k].col[kk].is_eng) return NotExist;
	if(grid->row[r].col[c].is_eng == 1) //����
	{
		if(grid->row[r].col[c].ch[0]!=wordlist->row[k].col[kk].ch[0]) return NotExist;
	}
	else //�ѱ�
	{
		if(grid->row[r].col[c].ch[0]!=wordlist->row[k].col[kk].ch[0]) return NotExist;
		if(grid->row[r].col[c].ch[1]!=wordlist->row[k].col[kk].ch[1]) return NotExist;
	}

	for(i=0; i<8; i++)
	{
		rr=r; cc=c; 
		for(kk=1; kk<wordlist->row[k].len; kk++)
		{
			rr+=x[i]; cc+=y[i];
			if(rr>=grid->line || rr<0 || cc>=grid->row[r].len || cc<0) break; //������ ����� break
			if(grid->row[rr].col[cc].is_eng != wordlist->row[k].col[kk].is_eng) break; //���� �ѱ��� ���� ������ break
			if(grid->row[rr].col[cc].is_eng == 1) //����
			{
				if(grid->row[rr].col[cc].ch[0]!=wordlist->row[k].col[kk].ch[0]) break;
			}
			else //�ѱ�
			{
				if(grid->row[rr].col[cc].ch[0]!=wordlist->row[k].col[kk].ch[0]) break;
				if(grid->row[rr].col[cc].ch[1]!=wordlist->row[k].col[kk].ch[1]) break;
			}
		}
		if (kk==wordlist->row[k].len)
			return Exist;
	}
	return NotExist;
}
void Search2(int k, Graph *grid, Graph *wordlist)
{
	int r, c;
	for(r=0; r<grid->line; r++)
	{
		for(c=0; c<grid->row[r].len; c++)
		{
			if(Search3(k, r, c, grid, wordlist))
			{
				printf("%d %d\n", r, c);
				return;
			}
		}
	}
	printf("Not Exist\n");
}
void Search1(Graph *grid, Graph *wordlist)
{
	int k;
	for(k=0; k<wordlist->line; k++)
		Search2(k, grid, wordlist);
}



