#include "header.h"
//������ ���� data�� buf�� ����Ǿ� �ִ� ����

void my_close() {
	TIME Now;
	struct tm *t;
	Date D_present;
	Date D_want;
	char Hour[3];
	char Minute[3];
	int orderSecond = 0; //shutdown ������ڿ� �� ��(�� ����)
	char ordermessage[50];
	char catmessage[10];

	printf("��������\n");

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
	int orderSecond = 0; //shutdown ������ڿ� �� ��(�� ����)
	char ordermessage[50];
	char catmessage[10];

	printf("��������(Ÿ�̸�)\n");

	//�����ڰ� �� �ð� �о����
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