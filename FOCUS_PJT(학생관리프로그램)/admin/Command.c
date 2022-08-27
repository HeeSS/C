#include "Thread.h"
#include "header.h"
#include "UI.h"
int i, j, k, l;
char command[100];
char message[1024];
char mac[50][30];
int flag_ftp = TRUE;
int flag_ftp1 = TRUE;

void InputMessage();

//��������
void ShutDown(char time[], int n, int select[], int flag) {//time�� �ð� or Ÿ�̸�
	memset(command, NULL, 100);
	strcpy(command, time);
	j = 0;
	if (flag == 0) {
		for (i = 0; i < n; i++) {
			if (send_MY(Client_List[select[i]].Socket, command, strlen(command) + 1, ADMINISTRATOR, SHUTDOWN, 0) == -1)

			{
				memset(mac[j], NULL, 30);
				strcpy(mac[j], Client_List[select[i]].MAC_ADDR);
				closesocket(Client_List[select[i]].Socket);
				memset(&Client_List[select[i]], NULL, sizeof(State)); // ���� ���� ���� ��, �������
				memcpy(&Client_List[select[i]], &Client_List[select[i] + 1], sizeof(State)*(howmany_C - 1 - i));
				howmany_C--;
				j++;
			}
			for (k = 0; k < howmany_C; k++) {// ����� Ŭ���̾�Ʈ���� �ٽ� ������
				for (l = 0; l < n; l++) {
					if (strcmp(Client_List[k].MAC_ADDR, mac[l]) == 0) {
						send_MY(Client_List[k].Socket, command, strlen(command) + 1, ADMINISTRATOR, SHUTDOWN, 0);
					}
				}
			}
		}
	}
	else {
		for (i = 0; i < n; i++) {
			if (send_MY(Client_List[select[i]].Socket, command, strlen(command) + 1, ADMINISTRATOR, SHUTDOWN_T, 0) == -1)
			{
				memset(mac[j], NULL, 30);
				strcpy(mac[j], Client_List[select[i]].MAC_ADDR);
				closesocket(Client_List[select[i]].Socket);
				memset(&Client_List[select[i]], NULL, sizeof(State)); // ���� ���� ���� ��, �������
				memcpy(&Client_List[select[i]], &Client_List[select[i] + 1], sizeof(State)*(howmany_C - 1 - i));
				howmany_C--;
				j++;
			}
			for (k = 0; k < howmany_C; k++) {// ����� Ŭ���̾�Ʈ���� �ٽ� ������
				for (l = 0; l < n; l++) {
					if (strcmp(Client_List[k].MAC_ADDR, mac[l]) == 0) {
						send_MY(Client_List[k].Socket, command, strlen(command) + 1, ADMINISTRATOR, SHUTDOWN_T, 0);
					}
				}
			}
		}
	}
}

// ���� ���
void SleepMode(char time[], int n, int select[], int flag) {
	memset(command, NULL, 100);
	strcpy(command, time);
	j = 0;
	if (flag == 0) {
		for (i = 0; i < n; i++) {
			if (send_MY(Client_List[select[i]].Socket, command, strlen(command) + 1, ADMINISTRATOR, SLEEP_MODE, 0) == -1)
			{
				memset(mac[j], NULL, 30);
				strcpy(mac[j], Client_List[select[i]].MAC_ADDR);
				closesocket(Client_List[select[i]].Socket);
				memset(&Client_List[select[i]], NULL, sizeof(State)); // ���� ���� ���� ��, �������
				memcpy(&Client_List[select[i]], &Client_List[select[i] + 1], sizeof(State)*(howmany_C - 1 - i));
				howmany_C--;
				j++;
			}
			for (k = 0; k < howmany_C; k++) {// ����� Ŭ���̾�Ʈ���� �ٽ� ������
				for (l = 0; l < n; l++) {
					if (strcmp(Client_List[k].MAC_ADDR, mac[l]) == 0) {
						send_MY(Client_List[k].Socket, command, strlen(command) + 1, ADMINISTRATOR, SLEEP_MODE, 0);
					}
				}
			}
		}
	}
	else {
		for (i = 0; i < n; i++) {
			if (send_MY(Client_List[select[i]].Socket, command, strlen(command) + 1, ADMINISTRATOR, SLEEP_MODE_T, 0) == -1)
			{
				memset(mac[j], NULL, 30);
				strcpy(mac[j], Client_List[select[i]].MAC_ADDR);
				closesocket(Client_List[select[i]].Socket);
				memset(&Client_List[select[i]], NULL, sizeof(State)); // ���� ���� ���� ��, �������
				memcpy(&Client_List[select[i]], &Client_List[select[i] + 1], sizeof(State)*(howmany_C - 1 - i));
				howmany_C--;
				j++;
			}
			for (k = 0; k < howmany_C; k++) {// ����� Ŭ���̾�Ʈ���� �ٽ� ������
				for (l = 0; l < n; l++) {
					if (strcmp(Client_List[k].MAC_ADDR, mac[l]) == 0) {
						send_MY(Client_List[k].Socket, command, strlen(command) + 1, ADMINISTRATOR, SLEEP_MODE_T, 0);
					}
				}
			}
		}
	}
}

// �޼��� ����
void MessageSend(int n, int select[]) {
	char result[1024];
	char message[1024];
	int i = 0;
	int j = 0;
	system("cls");
	
	textcolor(YELLOW2, YELLOW2);
	gotoxy(1, 1); printf(" ");
	textcolor(WHITE, BLACK);
	gotoxy(3, 1); printf("�޼��� ����\n\n");
	//getchar();// ���� ����
	//InputMessage();

	textcolor(WHITE, BLACK);
	
	//getch();
	//fflush(stdin);
	while (1) {
		memset(message, NULL, 1024);
		//gets(message);		
		scanf(" %[^\n]s",message);
		if (strcmp(message, "\\") == 0)// �� �κ��� �����δ� ���� ����
			break;
		i = strlen(message);
		message[i] = '\n';
		message[i + 1] = '\0';
		memcpy(result+j,message,i+2);
		j += i + 1;
		/*if (j == 0)
			strcpy(result, message);
		else
			strcat(result, message);*/
		//j++;
	}
	//scanf("%[^`]s", message); //-> `�� �Է� �ϸ� ���������ϴ�.

	j = 0;
	for (i = 0; i < n; i++) {
		if (send_MY(Client_List[select[i]].Socket, result, strlen(result) + 1, ADMINISTRATOR, SEND_MESSAGE, 0) == -1)
		{
			memset(mac[j], NULL, 30);
			strcpy(mac[j], Client_List[select[i]].MAC_ADDR);
			closesocket(Client_List[select[i]].Socket);
			memset(&Client_List[select[i]], NULL, sizeof(State)); // ���� ���� ���� ��, �������
			memcpy(&Client_List[select[i]], &Client_List[select[i] + 1], sizeof(State)*(howmany_C - 1 - i));
			howmany_C--;
			j++;
		}
		for (k = 0; k < howmany_C; k++) {// ����� Ŭ���̾�Ʈ���� �ٽ� ������
			for (l = 0; l < n; l++) {
				if (strcmp(Client_List[k].MAC_ADDR, mac[l]) == 0) {
					send_MY(Client_List[select[i]].Socket, message, strlen(message) + 1, ADMINISTRATOR, SEND_MESSAGE, 0);
				}
			}
		}
	}
	system("cls");
}

// �� ������ ����
void RunWebBrowser(int n, int select[]) {
	j = 0;
	for (i = 0; i < n; i++) {
		if (send_MY(Client_List[select[i]].Socket, send_web, strlen(send_web) + 1, ADMINISTRATOR, RUN_WEBBROWSER, 0) == -1)
		{
			memset(mac[j], NULL, 30);
			strcpy(mac[j], Client_List[select[i]].MAC_ADDR);
			closesocket(Client_List[select[i]].Socket);
			memset(&Client_List[select[i]], NULL, sizeof(State)); // ���� ���� ���� ��, �������
			memcpy(&Client_List[select[i]], &Client_List[select[i] + 1], sizeof(State)*(howmany_C - 1 - i));
			howmany_C--;
			j++;
		}
		for (k = 0; k < howmany_C; k++) {// ����� Ŭ���̾�Ʈ���� �ٽ� ������
			for (l = 0; l < n; l++) {
				if (strcmp(Client_List[k].MAC_ADDR, mac[l]) == 0) {
					send_MY(Client_List[k].Socket, send_web, strlen(send_web) + 1, ADMINISTRATOR, RUN_WEBBROWSER, 0);
				}
			}
		}
	}
}

// ���ͳ� ����
void BlockInternet(int n, int select[], int flag) {
	strcpy(message, "a");
	for (i = 0; i < n; i++) {
		if (flag == 0)
			send_MY(Client_List[select[i]].Socket, message, strlen(message) + 1, ADMINISTRATOR, BLOCK_INTERNET, 0);
		else
			send_MY(Client_List[select[i]].Socket, message, strlen(message) + 1, ADMINISTRATOR, FREE_INTBLOCK, 0);
	}
}

// ���� ����
void FileTranse(int n, int select[]) {
	char message[1024] = { 0, };
	char tmp[4];
	char result[64];
	int i, k;
	char *tok1;
	char *tok2;
	system("cls");
	textcolor(YELLOW2, YELLOW2);
	gotoxy(1, 1); printf(" ");
	textcolor(WHITE, BLACK);
	gotoxy(3, 1); printf("���� ���� (Ȯ��: ENTER)");
	printf("\n\n���� ��ο� ���ϸ��� �Է��ϰų�, ���� �� ������ ���������.\n");
	textcolor(GREEN1, BLACK);  printf(">> ");
	textcolor(WHITE, BLACK);


	scanf(" %[^\n]s", message);
	strcpy(filename, message);// '\\'�ι� ���°� �Է�â������ �ѹ��� �޾Ƶ� ������ �׻� �ι����� �ڵ����� �Էµǿ�. 

	
	//����� �����̸�.Ȯ���� ����//
	tok1 = strtok(message,"\\");
	while (TRUE) {
		if (tok1 != NULL) {
			tok2 = tok1;
			tok1 = strtok(NULL, "\\");
		}
		else {
			break;
		}
	}
	
	memcpy(result, tok2,sizeof(char)*strlen(tok2)+1);

	/*for (i = 0; i < 512; i++) {
		if (message[k] == '\\')
			break;
		tmp[i] = message[--k];
	}
	tmp[i - 1] = '\0';
	k = strlen(tmp);

	for (i = 0; i < 512; i++) {
		if (k == 0)
			break;
		result[i] = tmp[--k];
	}
	result[i] = '\0';*/

	
	//�׳� \���⸸ �ϸ� �˾Ƽ� '\\'�̷��� ���ϱ� ���� ����.

	if (flag_ftp) {
		hThread = (HANDLE)_beginthreadex(NULL, 0, TRANS_FILE, NULL, 0, (unsigned*)&dwThreadID);
		flag_ftp = FALSE;
	}

	while (flag_ftp1) {
		Sleep(300);
	}

	for (i = 0; i < n; i++) {
		if (send_MY(Client_List[select[i]].Socket, result, strlen(result) + sizeof(long) + 1, ADMINISTRATOR, FTP, 0) == -1)
		{
			memset(mac[j], NULL, 30);
			strcpy(mac[j], Client_List[select[i]].MAC_ADDR);
			closesocket(Client_List[select[i]].Socket);
			memset(&Client_List[select[i]], NULL, sizeof(State)); // ���� ���� ���� ��, �������
			memcpy(&Client_List[select[i]], &Client_List[select[i] + 1], sizeof(State)*(howmany_C - 1 - i));
			howmany_C--;
			j++;
		}

		for (k = 0; k < howmany_C; k++) {// ����� Ŭ���̾�Ʈ���� �ٽ� ������
			for (l = 0; l < n; l++) {
				if (strcmp(Client_List[k].MAC_ADDR, mac[l]) == 0) {
					send_MY(Client_List[k].Socket, result, strlen(result) + 1, ADMINISTRATOR, FTP, 0);
				}
			}
		}
	}

	flag_ftp1 = TRUE;
}


void InputMessage() {
	unsigned char ch;
	char buff[1024] = { '\0', };
	char result[1024] = { '\0', };
	int cursor = 0;
	int cnt = 0;
	int line = 0;

	gotoxy(1, 4);
	while (1) {
		gotoxy(3 + cnt, 4 + line);
		if (kbhit() == 1) {
			ch = getch();
			if (ch == ESC) {

			}
			else if (ch == SPACE) {
				result[cursor++] = ' ';
				cnt++;
			}
			else if (ch == ENTER) {
				result[cursor++] = '\n';
				line++;
				cnt = 0;
			}
			else {
				buff[cnt++] = ch;
				gotoxy(3 + cnt, 4 + line);
				printf("%c", ch);
			}
		}
	}
}