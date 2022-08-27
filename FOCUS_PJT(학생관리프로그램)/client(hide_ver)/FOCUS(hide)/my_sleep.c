#include "header.h"
//지금은 받은 data가 buf에 저장되어 있는 상태

void my_sleep() {
	TIME Now;
	struct tm *t;
	Date D_present;
	Date D_want;
	char Hour[3];
	char Minute[3];

	printf("절전 모드 전환\n");

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
		sleepOrderSecond = 0;
		return;
	}

	sleepOrderSecond = 0;
	sleepOrderSecond += (D_want.hour - D_present.hour) * 3600;
	sleepOrderSecond += (D_want.minute - D_present.minute) * 60;
}
void my_sleep_timer() {
	Date D_want;
	char Hour[3];
	char Minute[3];

	printf("절전 모드 전환(타이머)\n");

	//관리자가 준 시간 읽어오기
	memset(Hour, NULL, 3);
	memcpy(Hour, buf, 2);
	memset(Minute, NULL, 3);
	memcpy(Minute, buf + 2, 2);

	D_want.hour = atoi(Hour);
	D_want.minute = atoi(Minute);

	sleepOrderSecond = 0;
	sleepOrderSecond += (D_want.hour) * 3600;
	sleepOrderSecond += (D_want.minute) * 60;
}
UINT WINAPI SleepTimer_Thread(void *arg) {
	Sleep(sleepOrderSecond * SECOND);
	sleepTimerThread = 0;
	system("shutdown -h");
}