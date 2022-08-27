#include <stdio.h>
#include <string.h>

int mystrlen(char *);
int mystrcmp(char *, char *);
void mystrcpy(char *, char *);
void mystrcat(char *, char *);

void main(int argc, char *argv[])
{
	char str1[80], str2[80], str3[80];

	printf("argc : %d\n", argc);

	if (argc == 1) {
		printf("Type first string : "); gets(str1);
		printf("Type second string : "); gets(str2);
	}
	else if(argc == 3)
	{
		printf("str1:%s\n", argv[1]);
		printf("str2:%s\n", argv[2]);
		mystrcpy(str1, argv[1]);
		mystrcpy(str2, argv[2]);
	}
	else
	{
		printf("Error!\n");
		printf("\t file\n");
		printf("\t file str1 str2\n");
		return;
	}

	// 4.
	printf("Length of two strings : %d(%s), %d(%s)\n", mystrlen(str1),
		str1, mystrlen(str2), str2);

	// 5.
	if (mystrcmp(str1, str2) == 1)
		printf("Larger string: %s\n", str1);
	else if (mystrcmp(str1, str2) == -1)
		printf("Larger string: %s\n", str2);
	else printf("Same string.\n");

	// 6.
	mystrcpy(str3, str1);
	printf("Copied string : %s from %s\n", str3, str1);

	// 7.
	//넘을 경우 error 메시지 출력
	if(mystrlen(str1)+mystrlen(str2) >= 80)
		printf("Overflow!\n");
	else
	{
		mystrcat(str1, str2);
		printf("Concatenated string : %s with %s\n", str1, str2);
	}
}

int mystrlen(char *str)
{
	int len = 0;
	char *pc;

	pc = str;
	while (*pc != '\0') {
		len++;
		pc++;
	}
	return len;
}

int mystrcmp(char *str1, char *str2)
{
	int res = 0;
	char *pc1, *pc2;

	pc1 = str1;
	pc2 = str2;

	while(*pc1 == *pc2)
	{
		pc1++;
		pc2++;
	}

	if(*pc1>*pc2)
		res = 1;
	else if(*pc1<*pc2)
		res = -1;

	return res;
}

void mystrcpy(char *str1, char *str2)
{
	while(*str2)
		*str1++ = *str2++;
	*str1 = '\0';
}

void mystrcat(char *str1, char *str2)
{
	while(*str1)
		str1++;
	while(*str2)
		*str1++ = *str2++;
	*str1 = '\0';
}