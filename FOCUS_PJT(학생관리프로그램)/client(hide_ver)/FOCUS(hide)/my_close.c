#include "header.h"
//지금은 받은 data가 buf에 저장되어 있는 상태

void my_close() {
	TIME Now;
	struct tm *t;
	Date D_present;
	Date D_want;
	char Hour[3];
	char Minute[3];
	int orderSecond = 0; //shutdown 명령인자에 줄 값(초 단위)
	char ordermessage[50];
	char catmessage[10];

	printf("전원종료\n");

	time(&Now); //Now에 현재시각이 초단위로 저장
	t = localtime(&Now); // 초 단위의 시간을 분리하여 구조체 t에 넣기

	D_present.hour = t->tm_hour;
	D_present.minute = t->tm_min;

	//관리자가 준 시간 읽어오기
	memset(Hour, NULL, 3);
	memcpy(Hour, buf, 2);
	memset(Minute, NULL, 3);
	memcpy(Minute, buf + 2, 2);

	D_want.hour = atoi(Hour);
	D_want.minute = atoi(Minute);

	if (D_want.hour == 99 & D_want.minute == 99) {
		system("shutdown -s");
	}

	orderSecond += (D_want.hour - D_present.hour) * 3600;
	orderSecond += (D_want.minute - D_present.minute) * 60;
	_itoa(orderSecond, catmessage, 10);

	memset(ordermessage, NULL, sizeof(ordermessage));
	strcat(ordermessage, "shutdown -s -t ");
	strcat(ordermessage, catmessage);

	system(ordermessage);
}
void my_close_timer() {
	Date D_want;
	char Hour[3];
	char Minute[3];
	int orderSecond = 0; //shutdown 명령인자에 줄 값(초 단위)
	char ordermessage[50];
	char catmessage[10];

	printf("전원종료(타이머)\n");

	//관리자가 준 시간 읽어오기
	memset(Hour, NULL, 3);
	memcpy(Hour, buf, 2);
	memset(Minute, NULL, 3);
	memcpy(Minute, buf + 2, 2);

	D_want.hour = atoi(Hour);
	D_want.minute = atoi(Minute);

	orderSecond += (D_want.hour) * 3600;
	orderSecond += (D_want.minute) * 60;
	_itoa(orderSecond, catmessage, 10);

	memset(ordermessage, NULL, sizeof(ordermessage));
	strcat(ordermessage, "shutdown -s -t ");
	strcat(ordermessage, catmessage);

	system(ordermessage);
}