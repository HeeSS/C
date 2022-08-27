#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fp, *fpo;
	char ch;
	int start=0, end=0;

	if(argc == 1)
	{
		fp = fopen("fileread.cpp", "r");
	}
	else if(argc == 2)
		fp = fopen(argv[1], "r");
	else 
		//start �� �־��� ���,
	{
		fp = fopen(argv[1], "r");
		start = atoi(argv[2])-1;		//start��° ���ں��� ���� �� �ֵ��� ���� ��ġ �����ڸ� �̵�

		if(start<0)		//�Է��� start���� 0���� �۰ų� ���� ��� ���� ��ġ �����ڸ� ������ �Ǿ����� �̵�
			start = 0;

		fseek(fp, start, SEEK_SET);
	}

	if(fp == NULL)
	{
		printf("File Open ERROR for reading\n");
		return 0;
	}

	//ifile �б�
	//end�� ������ ��������� ���� �� -> ���� �б�/���� ��ġ���� ���� ������ ȭ�鿡 ���
	if(argc == 1 || argc == 2 || argc == 3)
	{
		while((ch = fgetc(fp)) != EOF)
			putchar(ch);
	}
	//end�� �־��� ��� ��������� ���� �� --> ���� �б�/���� ��ġ���� end���� ȭ�鿡 ���
	else if(argc == 4)
	{
		end = atoi(argv[3]);		//end��° ���ڱ��� ����

		//�б� ��������(start)�� �� ����(end)���� �ڿ� ������� ERROR
		if(start>end)
		{
			printf("ERROR! Start position must be ahead of End position\n");
			return 0;
		}

		while(ftell(fp)!=end && (ch = fgetc(fp)) != EOF)	//end�� �ʹ� ũ�� EOF������ �б�
		{
			putchar(ch);
		}
	}
	//end �� ��������� ������ ��� --> --> ���� �б�/���� ��ġ���� end���� ������Ͽ� ���
	else if(argc ==5)
	{
		fpo = fopen(argv[4], "w");

		if(fpo == NULL)
		{
			printf("File Open ERROR for writing\n");
			return 0;
		}

		end = atoi(argv[3]);		//end��° ���ڱ��� ����

		while(ftell(fp)!=end && (ch = fgetc(fp)) != EOF)	//end�� �ʹ� ũ�� EOF������ �б�
		{
			fputc(ch, fpo);
		}

		fclose(fpo);
	}

	fclose(fp);
	return 0;
}