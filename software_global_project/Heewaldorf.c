//2015.11.23
//1492018 서희선
//소프트웨어글로벌프로젝트(A)
//Where’s Waldorf? (Program #2)
//한글 & 영문 혼합 버전

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define Exist 1
#define NotExist 0

typedef struct COL{
	int is_eng; //영어=1, 한글=0
	char *ch;
}COL;
typedef struct ROW {
	int len; //문자열의 글자 수 (그래프의 열 수)
	COL *col;
}ROW;
typedef struct Graph{
	int line; //그래프의 행 수
	ROW *row;
}Graph;

void Malloc_grid(Graph *grid); //argc==1일 때 grid 생성 
void f_Malloc_grid(Graph *grid, FILE **fp); //argc==2일 때 grid 생성
void Malloc_wordlist(Graph *list); //argc==1일 때 wordList 생성
void f_Malloc_wordlist(Graph *list, FILE **fp); //argc==2일 때 wordList 생성
void FREE_graph(Graph *graph); //그래프 동적할당해제
int Search3(int k, int r, int c, Graph *grid, Graph *wordlist); //grid의 해당 행렬(r, c)위치의 글자와 wordList의 k번째 단어 글자 비교
void Search2(int k, Graph *grid, Graph *wordlist); //단어를 비교할 행(r)과 열(c)을 선택
void Search1(Graph *grid, Graph *wordlist); //wordList에서 비교할 k번째 단어 선택

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
	grid->row = (ROW*)malloc(sizeof(ROW)*m); //행 할당

	for (i = 0; i<m; i++)
	{
		grid->row[i].len = n;
		grid->row[i].col = (COL*)malloc(sizeof(COL)*n); //열 할당
		j=0;

		scanf(" %s", temp);
		len = strlen(temp);

		for(c=0; c<len; )
		{
			if(*(temp+c) & 0x80) //한글
			{
				grid->row[i].col[j].is_eng=0;
				grid->row[i].col[j].ch = (char*)malloc(sizeof(char)*2); //1글자 할당
				memcpy(grid->row[i].col[j].ch, temp + c, sizeof(char) * 2);
				c+=2;
			}
			else //영어
			{
				grid->row[i].col[j].is_eng=1;
				grid->row[i].col[j].ch = (char*)malloc(sizeof(char)*1);
				if(65 <= temp[c] && temp[c] <= 90) //대문자이면
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
	grid->row = (ROW*)malloc(sizeof(ROW)*m); //행 할당

	for (i = 0; i<m; i++)
	{
		grid->row[i].len = n;
		grid->row[i].col = (COL*)malloc(sizeof(COL)*n); //열 할당
		j=0;

		fscanf(*fp, " %s", temp);
		len = strlen(temp);

		for(c=0; c<len; )
		{
			if(*(temp+c) & 0x80) //한글
			{
				grid->row[i].col[j].is_eng=0;
				grid->row[i].col[j].ch = (char*)malloc(sizeof(char)*2); //1글자 할당
				memcpy(grid->row[i].col[j].ch, temp + c, sizeof(char) * 2);
				c+=2;
			}
			else //영어
			{
				grid->row[i].col[j].is_eng=1;
				grid->row[i].col[j].ch = (char*)malloc(sizeof(char)*1);
				if('A' <= temp[c] && temp[c] <= 'Z') //대문자이면
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
	list->row = (ROW*)malloc(sizeof(ROW)*k); //행 할당

	for (i = 0; i<k; i++)
	{
		scanf(" %s", temp);
		list->row[i].col = (COL*)malloc(sizeof(COL)*strlen(temp)); //열 할당
		j=0;
		len = strlen(temp);

		for(c=0; c<len; )
		{
			if(*(temp+c) & 0x80) //한글
			{
				list->row[i].col[j].is_eng=0;
				list->row[i].col[j].ch = (char*)malloc(sizeof(char)*2); //1글자 할당
				memcpy(list->row[i].col[j].ch, temp + c, sizeof(char) * 2);
				c+=2;
			}
			else //영어
			{
				list->row[i].col[j].is_eng=1;
				list->row[i].col[j].ch = (char*)malloc(sizeof(char)*1);
				if(65 <= temp[c] && temp[c] <= 90) //대문자이면
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
	list->row = (ROW*)malloc(sizeof(ROW)*k); //행 할당

	for (i = 0; i<k; i++)
	{
		fscanf(*fp, " %s", temp);
		list->row[i].col = (COL*)malloc(sizeof(COL)*strlen(temp)); //열 할당
		j=0;
		len = strlen(temp);

		for(c=0; c<len; )
		{
			if(*(temp+c) & 0x80) //한글
			{
				list->row[i].col[j].is_eng=0;
				list->row[i].col[j].ch = (char*)malloc(sizeof(char)*2); //1글자 할당
				memcpy(list->row[i].col[j].ch, temp + c, sizeof(char) * 2);
				c+=2;
			}
			else //영어
			{
				list->row[i].col[j].is_eng=1;
				list->row[i].col[j].ch = (char*)malloc(sizeof(char)*1);
				if(65 <= temp[c] && temp[c] <= 90) //대문자이면
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
	if(grid->row[r].col[c].is_eng == 1) //영문
	{
		if(grid->row[r].col[c].ch[0]!=wordlist->row[k].col[kk].ch[0]) return NotExist;
	}
	else //한글
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
			if(rr>=grid->line || rr<0 || cc>=grid->row[r].len || cc<0) break; //범위를 벗어나면 break
			if(grid->row[rr].col[cc].is_eng != wordlist->row[k].col[kk].is_eng) break; //영문 한글이 맞지 않으면 break
			if(grid->row[rr].col[cc].is_eng == 1) //영문
			{
				if(grid->row[rr].col[cc].ch[0]!=wordlist->row[k].col[kk].ch[0]) break;
			}
			else //한글
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



