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
		printf("Enter 누르세요\n");
		getchar();
		system("cls");
	}while(choice!=5);
}

void Menu(){
	for(;;)
	{
		printf("1. 파일 암호화\n");
		printf("2. 파일 복호화\n");
		printf("5. 종료\n");

		printf("선택 >> ");
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
	printf("**확장자까지 입력\n");
	getchar();

	for(;;)
	{
		printf("암호화 할 파일을 입력: ");
		gets(Type);

		FileCreat = fopen(Type, "rb");

		if (FileCreat == NULL)
		{
			printf("파일이 존재하지 않음!\n\n");
			continue;
		}

		else
		{
			FILE *CreatFile;
			char NameType[27];

			printf("생성될 파일명: ");
			gets(NameType);

			CreatFile = fopen(NameType, "wb");

			while ((File = fgetc(FileCreat)) != EOF)
			{
				File^=13;
				printf(".");
				fputc(File, CreatFile);
			}
			fclose(CreatFile);

			printf("\n\n암호화 완료!\n프로그램 종료\n");
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
	printf("**확장자까지 입력\n");
	getchar();

	for(;;)
	{
		printf("복호화 할 파일을 입력: ");
		gets(DeType);

		DecodFileCreat = fopen(DeType, "rb");

		if (DecodFileCreat == NULL)
		{
			printf("파일이 존재하지 않음!\n\n");
			continue;
		}
		else
		{
			FILE *DecodCreatFile;
			char DecodNameType[27];

			printf("생성될 파일명: ");
			gets(DecodNameType);

			DecodCreatFile = fopen(DecodNameType, "wb");

			while ((File = fgetc(DecodFileCreat)) != EOF)
			{
				File^=13;
				printf(".");
				fputc(File, DecodCreatFile);
			}
			fclose(DecodCreatFile);

			printf("\n\n복호화 완료!\n프로그램 종료\n");
			break;
		}
	}
	fclose(DecodFileCreat);
}

