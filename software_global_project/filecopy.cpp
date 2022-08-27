#include<stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp, *fpo;
	char ch;

	if(argc == 2)
		fp = fopen(argv[1], "r");
	else if(argc == 1)
		fp = fopen("filecopy.cpp", "r");

	if(fp == NULL)
	{
		printf("File Open ERROR for reading\n");
		return 0;
	}

	fpo = fopen("result.cpp", "w");

	if(fpo == NULL)
	{
		printf("File Open ERROR for writing\n");
		return 0;
	}

	while((ch = fgetc(fp)) != EOF)
		fputc(ch, fpo);

	fclose(fp);
	fclose(fpo);

	fpo = fopen("result.cpp", "r");
	
	if(fpo == NULL)
	{
		printf("result.cpp File Open ERROR for reading\n");
		return 0;
	}

	while((ch = fgetc(fpo)) != EOF)
		putchar(ch);

	fclose(fpo);
}