#include "header.h"
//������ ���� data�� buf�� ����Ǿ� �ִ� ����

void my_sleep() {
	TIME Now;
	struct tm *t;
	Date D_present;
	Date D_want;
	char Hour[3];
	char Minute[3];

	printf("���� ��� ��ȯ\n");

	time(&Now); //Now�� ����ð��� �ʴ����� ����
	t = localtime(&Now); // �� ������ �ð��� �и��Ͽ� ����ü t�� �ֱ�

	D_present.hour = t->tm_hour;
	D_present.minute = t->tm_min;

	//�����ڰ� �� �ð� �о����
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

	printf("���� ��� ��ȯ(Ÿ�̸�)\n");

	//�����ڰ� �� �ð� �о����
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