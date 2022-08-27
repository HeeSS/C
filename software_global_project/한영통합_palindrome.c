#include <stdio.h>
#include <string.h>

void main(int argc, char *argv[])
{
	char str[80], *ps, *pe;

	printf("argc : %d\n", argc);

	if (argc == 1) {
		printf("Type string : "); gets(str);
	}
	else if(argc == 2)
	{
		printf("str1:%s\n", argv[1]);
		strcpy(str, argv[1]);
	}
	else
	{
		printf("Error!\n");
		printf("\t file\n");
		printf("\t file str\n");
		return;
	}

	ps = &str[0];
	if(str[strlen(str)-1]>=65 && str[strlen(str)-1]<=90 && str[strlen(str)-1]>=97 && str[strlen(str)-1]<=122)
	{
		pe = &str[strlen(str)-1];
Eng:
		if(*ps != *pe)
		{
			printf("회문이 아닙니다.\n");
			return;
		}
		ps++;
		pe--;
	}
	else
	{
		pe = &str[strlen(str)-2];
Han:
		if(*ps != *pe)
		{
			printf("회문이 아닙니다.\n");
			return;
		}
		ps++;
		pe++;
		if(*ps != *pe)
		{
			printf("회문이 아닙니다.\n");
			return;
		}
		ps++;
		pe-=2;
	}
	if(*ps!=NULL)
	{
		//if(*pe>=65 && *pe<=90 && *pe>=97 && *pe<=122)	//★★서a희b희a서 에서 a를 인식하지못하고 else문(goto Han)으로 넘어감....
		if(!(*pe & 0x80)) //★★//★★//★★//★★//★★//★★//★★//★★
			goto Eng;
		else
		{
			pe--;
			goto Han;
		}
	}
	printf("회문입니다.\n");
}