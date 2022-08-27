#include "header.h"
//지금은 받은 data가 buf에 저장되어 있는 상태

void my_message(int recvSize) {
	wchar_t *firstStr = NULL;
	wchar_t *secondStr = NULL;
	char *temp = NULL;
	int i;

	printf("관리자 메시지 수신\n");

	firstStr = (wchar_t*)malloc(sizeof(wchar_t) * recvSize * 2);
	memset(firstStr, NULL, recvSize);

	//buf[i]가 NULL과 한글 둘다 아닐 때 까지만 루프 진행
	for (i = 0; buf[i] != NULL && !(buf[i] & 0x80) && (buf[i] != '\n'); i++) {
		firstStr[i] = (unsigned char)buf[i];
	}
	
	//남은 메시지(한글) 처리
	if (buf[i] != NULL) {
		secondStr = (wchar_t*)malloc(sizeof(wchar_t) * recvSize);
		memset(secondStr, NULL, recvSize);
		temp = (char*)malloc(sizeof(char) * recvSize);
		memset(temp, NULL, recvSize);

		setlocale(LC_ALL, "korean");

		if ((buf[i] == '\n') || mblen(buf + i, strlen(buf + i)) == 2) {
			mbstowcs(secondStr, buf + i, strlen(buf + i)); // char -> 유니코드
		}

		// wbcs문자열을 지정한 바이트 수만큼 mbcs 문자열로 변환
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