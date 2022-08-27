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

//전원종료
void ShutDown(char time[], int n, int select[], int flag) {//time은 시간 or 타이머
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
				memset(&Client_List[select[i]], NULL, sizeof(State)); // 기존 정보 삭제 후, 덧씌우기
				memcpy(&Client_List[select[i]], &Client_List[select[i] + 1], sizeof(State)*(howmany_C - 1 - i));
				howmany_C--;
				j++;
			}
			for (k = 0; k < howmany_C; k++) {// 사라진 클라이언트에게 다시 보내기
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
				memset(&Client_List[select[i]], NULL, sizeof(State)); // 기존 정보 삭제 후, 덧씌우기
				memcpy(&Client_List[select[i]], &Client_List[select[i] + 1], sizeof(State)*(howmany_C - 1 - i));
				howmany_C--;
				j++;
			}
			for (k = 0; k < howmany_C; k++) {// 사라진 클라이언트에게 다시 보내기
				for (l = 0; l < n; l++) {
					if (strcmp(Client_List[k].MAC_ADDR, mac[l]) == 0) {
						send_MY(Client_List[k].Socket, command, strlen(command) + 1, ADMINISTRATOR, SHUTDOWN_T, 0);
					}
				}
			}
		}
	}
}

// 절전 모드
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
				memset(&Client_List[select[i]], NULL, sizeof(State)); // 기존 정보 삭제 후, 덧씌우기
				memcpy(&Client_List[select[i]], &Client_List[select[i] + 1], sizeof(State)*(howmany_C - 1 - i));
				howmany_C--;
				j++;
			}
			for (k = 0; k < howmany_C; k++) {// 사라진 클라이언트에게 다시 보내기
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
				memset(&Client_List[select[i]], NULL, sizeof(State)); // 기존 정보 삭제 후, 덧씌우기
				memcpy(&Client_List[select[i]], &Client_List[select[i] + 1], sizeof(State)*(howmany_C - 1 - i));
				howmany_C--;
				j++;
			}
			for (k = 0; k < howmany_C; k++) {// 사라진 클라이언트에게 다시 보내기
				for (l = 0; l < n; l++) {
					if (strcmp(Client_List[k].MAC_ADDR, mac[l]) == 0) {
						send_MY(Client_List[k].Socket, command, strlen(command) + 1, ADMINISTRATOR, SLEEP_MODE_T, 0);
					}
				}
			}
		}
	}
}

// 메세지 전송
void MessageSend(int n, int select[]) {
	char result[1024];
	char message[1024];
	int i = 0;
	int j = 0;
	system("cls");
	
	textcolor(YELLOW2, YELLOW2);
	gotoxy(1, 1); printf(" ");
	textcolor(WHITE, BLACK);
	gotoxy(3, 1); printf("메세지 전송\n\n");
	//getchar();// 버퍼 비우기
	//InputMessage();

	textcolor(WHITE, BLACK);
	
	//getch();
	//fflush(stdin);
	while (1) {
		memset(message, NULL, 1024);
		//gets(message);		
		scanf(" %[^\n]s",message);
		if (strcmp(message, "\\") == 0)// 이 부분이 실제로는 전송 선택
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
	//scanf("%[^`]s", message); //-> `을 입력 하면 빠져나갑니다.

	j = 0;
	for (i = 0; i < n; i++) {
		if (send_MY(Client_List[select[i]].Socket, result, strlen(result) + 1, ADMINISTRATOR, SEND_MESSAGE, 0) == -1)
		{
			memset(mac[j], NULL, 30);
			strcpy(mac[j], Client_List[select[i]].MAC_ADDR);
			closesocket(Client_List[select[i]].Socket);
			memset(&Client_List[select[i]], NULL, sizeof(State)); // 기존 정보 삭제 후, 덧씌우기
			memcpy(&Client_List[select[i]], &Client_List[select[i] + 1], sizeof(State)*(howmany_C - 1 - i));
			howmany_C--;
			j++;
		}
		for (k = 0; k < howmany_C; k++) {// 사라진 클라이언트에게 다시 보내기
			for (l = 0; l < n; l++) {
				if (strcmp(Client_List[k].MAC_ADDR, mac[l]) == 0) {
					send_MY(Client_List[select[i]].Socket, message, strlen(message) + 1, ADMINISTRATOR, SEND_MESSAGE, 0);
				}
			}
		}
	}
	system("cls");
}

// 웹 브라우저 실행
void RunWebBrowser(int n, int select[]) {
	j = 0;
	for (i = 0; i < n; i++) {
		if (send_MY(Client_List[select[i]].Socket, send_web, strlen(send_web) + 1, ADMINISTRATOR, RUN_WEBBROWSER, 0) == -1)
		{
			memset(mac[j], NULL, 30);
			strcpy(mac[j], Client_List[select[i]].MAC_ADDR);
			closesocket(Client_List[select[i]].Socket);
			memset(&Client_List[select[i]], NULL, sizeof(State)); // 기존 정보 삭제 후, 덧씌우기
			memcpy(&Client_List[select[i]], &Client_List[select[i] + 1], sizeof(State)*(howmany_C - 1 - i));
			howmany_C--;
			j++;
		}
		for (k = 0; k < howmany_C; k++) {// 사라진 클라이언트에게 다시 보내기
			for (l = 0; l < n; l++) {
				if (strcmp(Client_List[k].MAC_ADDR, mac[l]) == 0) {
					send_MY(Client_List[k].Socket, send_web, strlen(send_web) + 1, ADMINISTRATOR, RUN_WEBBROWSER, 0);
				}
			}
		}
	}
}

// 인터넷 차단
void BlockInternet(int n, int select[], int flag) {
	strcpy(message, "a");
	for (i = 0; i < n; i++) {
		if (flag == 0)
			send_MY(Client_List[select[i]].Socket, message, strlen(message) + 1, ADMINISTRATOR, BLOCK_INTERNET, 0);
		else
			send_MY(Client_List[select[i]].Socket, message, strlen(message) + 1, ADMINISTRATOR, FREE_INTBLOCK, 0);
	}
}

// 파일 전송
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
	gotoxy(3, 1); printf("파일 전송 (확인: ENTER)");
	printf("\n\n파일 경로와 파일명을 입력하거나, 전송 할 파일을 끌어오세요.\n");
	textcolor(GREEN1, BLACK);  printf(">> ");
	textcolor(WHITE, BLACK);


	scanf(" %[^\n]s", message);
	strcpy(filename, message);// '\\'두번 쓰는거 입력창에서는 한번만 받아도 들어갈때는 항상 두번으로 자동으로 입력되요. 

	
	//경로중 파일이름.확장자 얻어내기//
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

	
	//그냥 \쓰기만 하면 알아서 '\\'이렇게 들어가니까 걱정 마요.

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
			memset(&Client_List[select[i]], NULL, sizeof(State)); // 기존 정보 삭제 후, 덧씌우기
			memcpy(&Client_List[select[i]], &Client_List[select[i] + 1], sizeof(State)*(howmany_C - 1 - i));
			howmany_C--;
			j++;
		}

		for (k = 0; k < howmany_C; k++) {// 사라진 클라이언트에게 다시 보내기
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