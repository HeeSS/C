#include "header.h"
//������ ���� data(�� �ּ�)�� buf�� ����Ǿ� �ִ� ����

void my_web(int recvSize) {
	char *ordermessage;

	printf("�� ������ ����\n");

	ordermessage = (char*)malloc(sizeof(char) * 20 * recvSize);

	memset(ordermessage, NULL, 20 * recvSize);
	strcpy(ordermessage, "start ");
	strcat(ordermessage, buf);

	system(ordermessage);
	free(ordermessage);
}