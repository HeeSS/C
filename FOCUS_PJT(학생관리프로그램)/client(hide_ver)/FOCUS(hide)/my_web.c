#include "header.h"
//지금은 받은 data(웹 주소)가 buf에 저장되어 있는 상태

void my_web(int recvSize) {
	char *ordermessage;

	printf("웹 브라우저 실행\n");

	ordermessage = (char*)malloc(sizeof(char) * 20 * recvSize);

	memset(ordermessage, NULL, 20 * recvSize);
	strcpy(ordermessage, "start ");
	strcat(ordermessage, buf);

	system(ordermessage);
	free(ordermessage);
}