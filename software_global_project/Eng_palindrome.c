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
	pe = &str[strlen(str)-1];

	while(*ps!=NULL)
	{
		if(*ps != *pe)
		{
			printf("ȸ���� �ƴմϴ�.\n");
			return;
		}
		ps++;
		pe--;
	}
	printf("ȸ���Դϴ�.\n");
}
