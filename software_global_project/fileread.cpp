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
		//start 가 주어진 경우,
	{
		fp = fopen(argv[1], "r");
		start = atoi(argv[2])-1;		//start번째 글자부터 읽을 수 있도록 파일 위치 지시자를 이동

		if(start<0)		//입력한 start값이 0보다 작거나 같을 경우 파일 위치 지시자를 파일의 맨앞으로 이동
			start = 0;

		fseek(fp, start, SEEK_SET);
	}

	if(fp == NULL)
	{
		printf("File Open ERROR for reading\n");
		return 0;
	}

	//ifile 읽기
	//end와 지정된 출력파일이 없을 때 -> 현재 읽기/쓰기 위치에서 문서 끝까지 화면에 출력
	if(argc == 1 || argc == 2 || argc == 3)
	{
		while((ch = fgetc(fp)) != EOF)
			putchar(ch);
	}
	//end가 주어진 경우 출력파일이 없을 때 --> 현재 읽기/쓰기 위치에서 end까지 화면에 출력
	else if(argc == 4)
	{
		end = atoi(argv[3]);		//end번째 글자까지 읽음

		//읽기 시작지점(start)이 끝 지점(end)보다 뒤에 있을경우 ERROR
		if(start>end)
		{
			printf("ERROR! Start position must be ahead of End position\n");
			return 0;
		}

		while(ftell(fp)!=end && (ch = fgetc(fp)) != EOF)	//end가 너무 크면 EOF까지만 읽기
		{
			putchar(ch);
		}
	}
	//end 와 출력파일이 지정된 경우 --> --> 현재 읽기/쓰기 위치에서 end까지 출력파일에 출력
	else if(argc ==5)
	{
		fpo = fopen(argv[4], "w");

		if(fpo == NULL)
		{
			printf("File Open ERROR for writing\n");
			return 0;
		}

		end = atoi(argv[3]);		//end번째 글자까지 읽음

		while(ftell(fp)!=end && (ch = fgetc(fp)) != EOF)	//end가 너무 크면 EOF까지만 읽기
		{
			fputc(ch, fpo);
		}

		fclose(fpo);
	}

	fclose(fp);
	return 0;
}