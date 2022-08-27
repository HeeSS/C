#include "header.h"
#include "UI.h"

char* inputIP();

char* InputID();
char* InputPwd();

int LoginTry() {
	int i;
	char input_ip[15] = { 0, };
	char input[16], SHAid[64], SHApwd[64];
	char *p;
	//int debugcnt = 0;
	//int debuglist[512] = { 0, };
	
	// 로그인 화면
	ShowLogin(12, VER);

	// 입력
	while (1) {
		memset(input, NULL, 16);
		memcpy(input, InputID(), 16);
		SHA256_Encrpyt(input, 16, SHAid);
		memset(input, NULL, 16);
		p = InputPwd();
		if (p != NULL) {
			break;
		}
		SHA256_Encrpyt(input, 16, SHApwd);
	}
	

	// 로그인 요청
	if (LoginReq(Main_Socket, SHAid, SHApwd)) {
		while (1) {
			if (send_MY(Main_Socket, (char *)&s, sizeof(s), ADMINISTRATOR, ADMINISTRATOR_STATE, 0) == -1) {
				closesocket(Main_Socket);
				Main_Socket = socket(PF_INET, SOCK_STREAM, 0);
				i = connect(Main_Socket, (SOCKADDR*)&sockaddr_in, sizeof(sockaddr_in));
				send_MY(Main_Socket, (char *)&s, sizeof(s), ADMINISTRATOR, ADMINISTRATOR_STATE, 0);
			}
			else {
				return TRUE;
			}
		}
	}
}

int LoginReq(SOCKET Socket, char *ID_SHA, char *PWD_SHA) {
	char SHAstr[128];
	char buf[512] = { 0, };
	int *p = buf;
	int size = 0;

	struct timeval val;
	val.tv_sec = 0;
	val.tv_usec = 100;

	memcpy(&SHAstr[0], ID_SHA, 64);
	memcpy(&SHAstr[64], PWD_SHA, 64);

	/* 로그인 정보를 송신 */
	

	if (send_MY(Socket, SHAstr, 128, ADMINISTRATOR, ADMINISTRATOR_LOGIN, 0) == -1) {
		return FALSE;
	}
	else {
		if (recv(Socket, buf, 12, 0) == -1) {
			return FALSE;
		}
		else {
			size = p[0];
			recv(Socket, buf, size, 0);
			if (strcmp(buf, "LOGINSUCCESS") == 0) {
				return TRUE;
			}
			else {
				return FALSE;
			}
		}
	}
	return TRUE;
}

//ip 대역 요청
int IRrangeReq() {
	char recvdata[60] = { 0, };
	char* addr;
	char result;
	int num;
	int *p = recvdata;

	result = ShowRangeSetBox(15, 18);

	if (result == SET_IP) {
		textcolor(BLACK, WHITE);
		gotoxy(20, 23);
		addr = inputIP();
		if (addr == NULL)
			return NULL;
		memcpy(recvdata, addr, 60);
	}
	else if (result == 0) {
		
		strcpy(recvdata, "0.0.0.0");
		strcpy(recvdata + 30, "255.255.255.255");
	}

	if(send_MY(Main_Socket, recvdata, sizeof(recvdata), ADMINISTRATOR, ADMINISTRATOR_REQUEST_LIST, 0 ) == -1) {
		// # 요청 실패 창
		closesocket(Main_Socket);
		Main_Socket = socket(PF_INET, SOCK_STREAM, 0);
		connect(Main_Socket, (SOCKADDR*)&sockaddr_in, sizeof(sockaddr_in));
		login = FALSE;
		bootThread = TRUE;
	}
	else {
		if (recv(Main_Socket, recvdata, 12, 0) == -1) {
			// # 요청 실패 창
			closesocket(Main_Socket);
			Main_Socket = socket(PF_INET, SOCK_STREAM, 0);
			connect(Main_Socket, (SOCKADDR*)&sockaddr_in, sizeof(sockaddr_in));
			login = FALSE;
			bootThread = TRUE;
		}
		else {
			memset(recvdata, NULL, sizeof(recvdata));
			recv(Main_Socket, recvdata, 4, 0);
			num = p[0];
			return num;
		}
	}
	system("cls");
	return;
}

char* inputIP() {
	char input_ip[2][30] = { {0,},{0,} };
	char recvdata[60] = { 0, };
	unsigned char ch;
	int cnt[2][4] = { 0, };
	int cursor[2] = { 0, };
	int box[2] = { 0, };
	int area = 0;

	while (TRUE) {
		gotoxy(21 + 5 * box[area] + cnt[area][box[area]] + area * 22, 23);
		if (kbhit() == TRUE) {
			ch = getch();
			if (ch == ESC) {
				return NULL;
			}
			else if (ch == SPACE) {

			}
			else if (ch == ENTER) {
				if (box[area] == 3 && cnt[area][box[area]] != 0) {
					if (area == 0) {
						area = 1;
						memcpy(recvdata, input_ip[0], 30);
					}
					else {
						memcpy(recvdata + 30, input_ip[1], 30);
						break;
					}
				}
				else {
					
				}
			}
			else if (ch == BACKSPACE ) {
				if (cursor[area] >= 0) {
					if (input_ip[area][cursor[area]-1] == '.') {
						input_ip[area][--cursor[area]] = NULL;
						box[area]--;
						gotoxy(21 + 5 * box[area] + cnt[area][box[area]] - 1 + area * 22, 23); printf(" ");
					}
					if (area == 1 && box[area] == 0 && cnt[area][box[area]] == 0) {
						area = 0;
					}
					gotoxy(21 + 5 * box[area] + cnt[area][box[area]]-1 + area * 22, 23); printf(" ");
					if (cursor[area] > 0)
						cursor[area]--;

					input_ip[area][cursor[area]] = NULL;
					
					if (cnt[area][box[area]] > 0)
						cnt[area][box[area]]--;
				}
			}
			else if ((ch == TAB || ch == '.') && box[area] <3) {
				if (cnt[area][box[area]] != 0) {
					input_ip[area][cursor[area]++] = '.';
					box[area]++;
					cnt[area][box[area]] = 0;
				}
			}
			else if((ch >= '0' && ch <= '9') && box[area] != 4 && cnt[area][box[area]] != 3) {
				textcolor(BLACK, WHITE);
				input_ip[area][cursor[area]++] = ch;
				printf("%c", ch);
				cnt[area][box[area]]++;
				
				if (cnt[area][box[area]] == 3 && box[area] <= 3) {
					if (box[area] == 3) {
						if (area == 0) {
							memcpy(recvdata, input_ip[area], 30);
							area = 1;
						}
					}
					else {
						input_ip[area][cursor[area]++] = '.';
						box[area]++;
						cnt[area][box[area]] = 0;
					}
				}
			}
		}
		Sleep(50);
	}
	return recvdata;
}

char* InputID() {
	unsigned char ch;
	int cursor = 0;
	char input[16] = { '\0', };
	while (1) {
		gotoxy(30 + cursor, 20);
		if (kbhit() == 1) {
			ch = getch();
			if (ch == ESC) {
				cursor = 0;
				memset(input, NULL, 16);
				gotoxy(30, 20); printf("                         ");
			}
			else if (ch == ENTER) {
				if (cursor != 0) {
					return input;
				}
			}
			else if (ch == TAB) {
				if (cursor != 0) {
					return input;
				}
			}
			else if (ch == BACKSPACE) {
				gotoxy(60, 20); printf("           ");
				if (cursor != 0) {
					gotoxy(29 + cursor, 20);
					printf(" ");
					input[cursor--] = NULL;
				}

			}
			else if
				((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z')) {
				gotoxy(60, 20); printf("           ");
				gotoxy(30 + cursor, 20);
				if (cursor < 15) {
					textcolor(WHITE, BLACK);
					input[cursor++] = ch;
					printf("%c", ch);
				}
				else {
					gotoxy(60, 20);
					textcolor(RED2, BLACK);
					printf("입력 초과");
				}
				
			}
			else {
				gotoxy(60, 20);
				textcolor(RED2, BLACK);
				printf("잘못된 입력");
			}
		}
		Sleep(50);
	}
}
char* InputPwd() {
	unsigned char ch;
	int cursor = 0;
	char input[16] = { '\0', };
	while (1) {
		gotoxy(30 + cursor, 23);
		if (kbhit() == 1) {
			ch = getch();
			if (ch == ESC) {
				if (cursor != 0) {
					cursor = 0;
					memset(input, NULL, 16);
					gotoxy(30, 20); printf("                         ");
				}
				else {
					return NULL;
				}
			}
			else if (ch == ENTER) {
				if (cursor != 0) {
					return input;
				}
			}
			else if (ch == BACKSPACE) {
				gotoxy(60, 20); printf("           ");
				if (cursor != 0) {
					gotoxy(29 + cursor, 23);
					printf(" ");
					input[cursor--] = NULL;
				}

			}
			else if
				((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z')) {
				gotoxy(60, 20); printf("           ");
				gotoxy(30 + cursor, 23);
				if (cursor < 15) {
					textcolor(WHITE, BLACK);
					input[cursor++] = ch;
					printf("*");
				}
				else {
					gotoxy(60, 23);
					textcolor(RED2, BLACK);
					printf("입력 초과");
				}
				
			}
			else {
				gotoxy(60, 23);
				textcolor(RED2, BLACK);
				printf("잘못된 입력");
			}
		}
		Sleep(50);
	}
}
