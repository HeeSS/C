#include "header.h"
//������ ���� data�� buf�� ����Ǿ� �ִ� ����

void my_message(int recvSize) {
	wchar_t *firstStr = NULL;
	wchar_t *secondStr = NULL;
	char *temp = NULL;
	int i;

	printf("������ �޽��� ����\n");

	firstStr = (wchar_t*)malloc(sizeof(wchar_t) * recvSize * 2);
	memset(firstStr, NULL, recvSize);

	//buf[i]�� NULL�� �ѱ� �Ѵ� �ƴ� �� ������ ���� ����
	for (i = 0; buf[i] != NULL && !(buf[i] & 0x80) && (buf[i] != '\n'); i++) {
		firstStr[i] = (unsigned char)buf[i];
	}
	
	//���� �޽���(�ѱ�) ó��
	if (buf[i] != NULL) {
		secondStr = (wchar_t*)malloc(sizeof(wchar_t) * recvSize);
		memset(secondStr, NULL, recvSize);
		temp = (char*)malloc(sizeof(char) * recvSize);
		memset(temp, NULL, recvSize);

		setlocale(LC_ALL, "korean");

		if ((buf[i] == '\n') || mblen(buf + i, strlen(buf + i)) == 2) {
			mbstowcs(secondStr, buf + i, strlen(buf + i)); // char -> �����ڵ�
		}

		// wbcs���ڿ��� ������ ����Ʈ ����ŭ mbcs ���ڿ��� ��ȯ
		wcstombs(temp, secondStr, sizeof(secondStr));

		wcscat(firstStr, secondStr);

		MessageBox(NULL, firstStr, TEXT("FOCUS: Message by Administrator"), MB_OK);

		free(firstStr);
		free(secondStr);
		free(temp);
	}
	else {
		MessageBox(NULL, firstStr, TEXT("FOCUS: Message by Administrator"), MB_OK);

		free(firstStr);
		free(secondStr);
		free(temp);
	}
}