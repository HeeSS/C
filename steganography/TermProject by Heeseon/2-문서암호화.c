#include <stdio.h>
#include <string.h>
#include <Windows.h>

void Menu();
void FileEncoding();
void FileDecoding();

int choice;

void main(){
	do{
		Menu();
		printf("Enter ��������\n");
		getchar();
		system("cls");
	}while(choice!=5);
}

void Menu(){
	for(;;)
	{
		printf("1. ���� ��ȣȭ\n");
		printf("2. ���� ��ȣȭ\n");
		printf("5. ����\n");

		printf("���� >> ");
		scanf("%d", &choice);

		if (choice<3)
			break;
		else
			continue;
	}

	switch(choice)
	{
	case 1:
		FileEncoding();
		break;
	case 2:
		FileDecoding();
		break;
	case 0:
		exit(1);
	}
}

void FileEncoding()
{
	FILE *FileCreat=NULL;
	int File;
	char Type[27];

	system("cls");
	printf("**Ȯ���ڱ��� �Է�\n");
	getchar();

	for(;;)
	{
		printf("��ȣȭ �� ������ �Է�: ");
		gets(Type);

		FileCreat = fopen(Type, "rb");

		if (FileCreat == NULL)
		{
			printf("������ �������� ����!\n\n");
			continue;
		}

		else
		{
			FILE *CreatFile;
			char NameType[27];

			printf("������ ���ϸ�: ");
			gets(NameType);

			CreatFile = fopen(NameType, "wb");

			while ((File = fgetc(FileCreat)) != EOF)
			{
				File^=13;
				printf(".");
				fputc(File, CreatFile);
			}
			fclose(CreatFile);

			printf("\n\n��ȣȭ �Ϸ�!\n���α׷� ����\n");
			break;
		}
	}
	fclose(FileCreat);
}

void FileDecoding()
{
	FILE *DecodFileCreat = NULL;
	int File;
	char DeType[27];

	system("cls");
	printf("**Ȯ���ڱ��� �Է�\n");
	getchar();

	for(;;)
	{
		printf("��ȣȭ �� ������ �Է�: ");
		gets(DeType);

		DecodFileCreat = fopen(DeType, "rb");

		if (DecodFileCreat == NULL)
		{
			printf("������ �������� ����!\n\n");
			continue;
		}
		else
		{
			FILE *DecodCreatFile;
			char DecodNameType[27];

			printf("������ ���ϸ�: ");
			gets(DecodNameType);

			DecodCreatFile = fopen(DecodNameType, "wb");

			while ((File = fgetc(DecodFileCreat)) != EOF)
			{
				File^=13;
				printf(".");
				fputc(File, DecodCreatFile);
			}
			fclose(DecodCreatFile);

			printf("\n\n��ȣȭ �Ϸ�!\n���α׷� ����\n");
			break;
		}
	}
	fclose(DecodFileCreat);
}

