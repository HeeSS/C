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
			printf("ȸ���� �ƴմϴ�.\n");
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
			printf("ȸ���� �ƴմϴ�.\n");
			return;
		}
		ps++;
		pe++;
		if(*ps != *pe)
		{
			printf("ȸ���� �ƴմϴ�.\n");
			return;
		}
		ps++;
		pe-=2;
	}
	if(*ps!=NULL)
	{
		//if(*pe>=65 && *pe<=90 && *pe>=97 && *pe<=122)	//�ڡڼ�a��b��a�� ���� a�� �ν��������ϰ� else��(goto Han)���� �Ѿ....
		if(!(*pe & 0x80)) //�ڡ�//�ڡ�//�ڡ�//�ڡ�//�ڡ�//�ڡ�//�ڡ�//�ڡ�
			goto Eng;
		else
		{
			pe--;
			goto Han;
		}
	}
	printf("ȸ���Դϴ�.\n");
}