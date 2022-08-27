#include "header.h"
#include "Thread.h"
#include "UI.h"

int howmany_C;
//int howmany_C = 50;
int clt_arrow = 0;
int cmd_arrow = 0;
int arrow = 0;
unsigned char ch;
char ui_flag;

int last_page;
int page;
int all;

char is_select[512] = { 0, };
// �ΰ�
char FOCUS[5][39] = {
	{ 1,1,1,1,1,1,2,0,1,1,1,1,1,1,2,0,1,1,1,1,1,1,2,0,1,1,2,0,1,1,2,0,1,1,1,1,1,1,2 },
	{ 1,1,2,0,0,0,0,0,1,1,2,0,1,1,2,0,1,1,2,0,0,0,0,0,1,1,2,0,1,1,2,0,1,1,2,0,0,0,0 },
	{ 1,1,1,1,1,1,2,0,1,1,2,0,1,1,2,0,1,1,2,0,0,0,0,0,1,1,2,0,1,1,2,0,1,1,1,1,1,1,2 },
	{ 1,1,2,0,0,0,0,0,1,1,2,0,1,1,2,0,1,1,2,0,0,0,0,0,1,1,2,0,1,1,2,0,0,0,0,0,1,1,2 },
	{ 1,1,2,0,0,0,0,0,1,1,1,1,1,1,2,0,1,1,1,1,1,1,2,0,1,1,1,1,1,1,2,0,1,1,1,1,1,1,2 }
};

void gotoxy(int x, int y) { //���� ���ϴ� ��ġ�� Ŀ�� �̵�
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void cls(int bg_color, int text_color) {
	char cmd[100];
	system("cls");
	sprintf(cmd, "COLOR %x%x", bg_color, text_color);
	system(cmd);
}
void textcolor(int fg_color, int bg_color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);

}
void removeCursor(void) { // Ŀ���� �Ⱥ��̰� �Ѵ�
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

// �ΰ� ���
void ShowFOCUS(int x, int y, char* ver) {
	int i, j;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 39; j++) {
			gotoxy(x + j, y + i);
			if (FOCUS[i][j] == 0)
				textcolor(BLACK, BLACK);
			else if (FOCUS[i][j] == 1)
				textcolor(WHITE, CYAN2);
			else
				textcolor(GRAY2, GRAY1);
			printf(" ");
		}
	}
	textcolor(WHITE, BLACK);
	gotoxy(x + 41, y); printf("v %s", ver);
}
void ShowLogin(int y, char* ver) {
	int i;
	cls(BLACK, WHITE);

	// �ΰ� ���
	ShowFOCUS(18, 0, ver);

	// �ٴ� ��
	textcolor(WHITE, BLACK);
	gotoxy(0, y);  printf("��������������������������������������������������������������������������������");

	textcolor(YELLOW2, BLACK);
	// �ĵ��� ��ü
	gotoxy(11, y - 6); printf("����������������������");
	gotoxy(11, y - 5); printf("����������������������");
	gotoxy(11, y - 4); printf("����              ����");
	gotoxy(11, y - 3); printf("����              ����");
	gotoxy(11, y - 2); printf("����              ����");
	gotoxy(11, y - 1); printf("����              ����");
	gotoxy(11, y);	   printf("����������������������");
	gotoxy(11, y + 1); printf("������������/ ��������");
	gotoxy(12, y + 2); printf(".��������/����������.");
	gotoxy(11, y + 3); printf("/                     ��");
	gotoxy(10, y + 4); printf("/                       ��");
	gotoxy(10, y + 5); printf("\"������������������������\"");

	// �ļ��� ��ü
	gotoxy(45, y - 6);
	gotoxy(45, y - 6); printf("������=/��������������");
	gotoxy(45, y - 5); printf("��|_/=����������������");
	gotoxy(45, y - 4); printf("����              ����");
	gotoxy(45, y - 3); printf("����              ����");
	gotoxy(45, y - 2); printf("����              ����");
	gotoxy(45, y - 1); printf("����              ����");
	gotoxy(45, y);	   printf("����������������������");
	gotoxy(45, y + 1); printf("����������������������");
	gotoxy(46, y + 2); printf(".��������   ��������.");
	gotoxy(45, y + 3); printf("/                     ��");
	gotoxy(44, y + 4); printf("/                       ��");
	gotoxy(44, y + 5); printf("\"������������������������\"");


	textcolor(WHITE, BLACK);
	// �ĵ��� ǥ��
	gotoxy(17, y - 3); printf("��      ��");
	gotoxy(17, y - 2); printf("    ��");
	gotoxy(17, y - 1); printf("  ������");
	gotoxy(13, y + 3); printf("*.*.*.*.*.*.*.*.*.*");
	gotoxy(12, y + 4); printf("*.*.*.*.*.*.*.*.*.*.*");

	// �ļ��� ǥ��
	gotoxy(50, y - 3); printf("\"��      ��\"");
	gotoxy(51, y - 2); printf("    ��");
	gotoxy(51, y - 1); printf("  ������");
	gotoxy(47, y + 3); printf("*.*.*.*.*.*.*.*.*.*");
	gotoxy(46, y + 4); printf("*.*.*.*.*.*.*.*.*.*.*");

	// ���� �Է¶�
	gotoxy(24, y + 8); printf("ID :");
	gotoxy(28, y + 7); printf("������������������������������");
	gotoxy(28, y + 8); printf("��                          ��");
	gotoxy(28, y + 9); printf("������������������������������");
	gotoxy(18, y + 11); printf("PASSWORD :");
	gotoxy(28, y + 10); printf("������������������������������");
	gotoxy(28, y + 11); printf("��                          ��");
	gotoxy(28, y + 12); printf("������������������������������");

	gotoxy(0, 25);
}

// ip �뿪 ����
int ShowRangeSetBox(int x, int y) {
	arrow = 0;
	char is_select = FALSE;
	char select_way;
	int num = 4;
	char room[][7] = { " ��ü ", "101 ȣ", "102 ȣ", "103 ȣ"};
	int roomNo = 0;

	textcolor(WHITE, BLACK);
	// �ؽ�Ʈ �ڽ�
	gotoxy(x, y);		printf("������ IP �뿪  ����������������������������������");
	gotoxy(x, y + 1);	printf("��                                              ��");
	gotoxy(x, y + 2);	printf("��                                              ��");
	gotoxy(x, y + 3);	printf("��                                              ��");
	gotoxy(x, y + 4);	printf("��                                              ��");
	gotoxy(x, y + 5);	printf("��                                              ��");
	gotoxy(x, y + 6);	printf("��                                              ��");
	gotoxy(x, y + 7);	printf("��������������������������������������������������");



	// ip ��ĭ 
	textcolor(WHITE, BLACK);
	gotoxy(x + 9, y + 5);  printf(".    .    .     ~");
	gotoxy(x + 31, y + 5);  printf(".    .    .    ");
	textcolor(BLACK, WHITE);
	gotoxy(x + 5, y + 5); printf("    ");
	gotoxy(x + 10, y + 5); printf("    ");
	gotoxy(x + 15, y + 5); printf("    ");
	gotoxy(x + 20, y + 5); printf("    ");
	gotoxy(x + 27, y + 5); printf("    ");
	gotoxy(x + 32, y + 5); printf("    ");
	gotoxy(x + 37, y + 5); printf("    ");
	gotoxy(x + 42, y + 5); printf("    ");

	// ���� ��
	while (login) {

		if (kbhit() == TRUE) {
			ch = getch();
			if (ch == ESC) {
				if (is_select == TRUE) {
					is_select = FALSE;
				}
				else {
				}
			}
			else if (ch == SPACE || ch == ENTER) {
				if (arrow == SET_IP) {
					return SET_IP;
				}
				else {
					if (is_select == TRUE) {
						return roomNo % num;
					}
					else {
						is_select = TRUE;
						WipeArrow(x + 2, y + 2, arrow);
					}
				}
			}
			else if (ch == SPECIAL1 || ch == SPECIAL2) {
				ch = getch();
				switch (ch) {
				case UP:
					WipeArrow(x + 2, y + 2, arrow);
					arrow = (arrow == 2 ? 0 : 2);
					break;
				case DOWN:
					WipeArrow(x + 2, y + 2, arrow);
					arrow = (arrow == 0 ? 2 : 0);
					break;
				case LEFT:
					//gotoxy(x + 1, y + 2); printf("��");
					//WipeArrow(x + 1, y + 2, arrow);
					if (is_select == TRUE) {
						roomNo++;
					}
					break;
				case RIGHT:
					
					if (is_select == TRUE) {
						roomNo++;
					}
					break;
				}
			}
		}
		if (is_select == FALSE) {
			ShowArrow(x + 2, y + 2, arrow);
		}

		// ���� �޴�
		if (arrow == 0) {
			textcolor(WHITE, BLACK);
			gotoxy(x + 5, y + 2);  printf("���ǽ�");
			textcolor(GRAY2, BLACK);
			gotoxy(x + 5, y + 4); printf("���� �Է�");
		}
		else {
			textcolor(GRAY2, BLACK);
			gotoxy(x + 5, y + 2);  printf("���ǽ�");
			textcolor(WHITE, BLACK);
			gotoxy(x + 5, y + 4); printf("���� �Է�");
		}
		if (is_select == TRUE) {
			textcolor(RED2, BLACK);
			gotoxy(x + 25, y + 2); printf("��");
			gotoxy(x + 37, y + 2); printf("��");
			textcolor(WHITE, BLACK);
			gotoxy(x + 29, y + 2); printf("%s", room[roomNo % num]);
		}
		else {
			textcolor(GRAY2, BLACK);
			gotoxy(x + 25, y + 2); printf("��");
			gotoxy(x + 37, y + 2); printf("��");
			textcolor(GRAY2, BLACK);
			gotoxy(x + 29, y + 2); printf("%s", room[roomNo % num]);
		}

		//debug(x, y, arrow, 0);

		Sleep(90);
	}
}
// ȭ��ǥ ���
void ShowArrow(int x, int y, int arrow) {
	gotoxy(x, y + arrow);
	textcolor(RED2, BLACK); printf("��");
}

// ȭ��ǥ �����
void WipeArrow(int x, int y, int arrow) {
	gotoxy(x, y + arrow);
	textcolor(BLACK, BLACK); printf("   ");
}
// ����Ʈ �����
void WipeList(int x, int y) {
	int i;
	for (i = 0; i < LINE; i++) {
		gotoxy(x + 3, y + 4 + i % LINE);
		textcolor(BLACK, BLACK);
		printf("         ");
	}
}

// ����Ʈ ���
void PrintList(int x, int y, int n, int arrow, int page) {
	int i;
	WipeList(x, y);
	for (i = 0; i < LINE; i++) {
		if (i + (page * LINE) >= howmany_C)
			break;

		if (sel_clt_cnt != howmany_C) {
			textcolor(GRAY2, BLACK);
		}
		else {
			textcolor(GREEN2, BLACK);
		}

		gotoxy(x + 2, y + 3);
		printf("   ALL");
		gotoxy(x + 8, y + 3);
		textcolor(GRAY2, BLACK);
		printf("(A)");

		if (is_select[i + (page * LINE)] == FALSE) {
			if (i % LINE == arrow) {
				gotoxy(x + 3, y + 4 + i % LINE);
				textcolor(GRAY2, BLACK);
				printf("   CLT");
				textcolor(WHITE, BLACK);
				printf("%.3d", (i + 1) + (page * LINE));
			}
			else {
				gotoxy(x + 3, y + 4 + i % LINE);
				textcolor(GRAY2, BLACK);
				printf("- CLT");
				textcolor(WHITE, BLACK);
				printf("%.3d ", (i + 1) + (page * LINE));
			}
		}
		else {
			gotoxy(x + 3, y + 4 + i % LINE);
			textcolor(BLACK, WHITE);
			if (i % LINE == arrow) {
				printf(" - CLT%.3d", (i + 1) + (page * LINE));
			}
			else {
				printf("- CLT%.3d", (i + 1) + (page * LINE));
			}
		}
	}
}

void debug(int page, int last, int arrow, int select[]) {
	int i;
	gotoxy(70, 21);	printf("page: %2d", page);
	gotoxy(70, 22); printf("last: %2d", last);
	gotoxy(70, 20); printf("arrow: %2d", arrow);
	//gotoxy(70, 23); printf("%d", arrow + (page * LINE));

	//gotoxy(60, 10);
	//for (i = 0; i < 10; i++) {
	//	printf("%d", select[i]);
	//}
}

// ����Ʈ �ڽ� ��� (���� ����)
int ShowMainScr(int x, int y, int select[]) {
	int i;
	howmany_C = 50; // �����
	ShowFOCUS(18, 0, VER);

	if (reset == TRUE) {
		clt_arrow = 0;
		cmd_arrow = 0;
		sel_clt_cnt = 0;
		memset(select, NULL, 256);
		memset(is_select, FALSE, 512);
		page = 0;
		all = FALSE;
	}

	last_page = (howmany_C - 1) / LINE;

	// Ŭ���̾�Ʈ ����Ʈ �ڽ�
	textcolor(WHITE, BLACK);
	gotoxy(x, y + 2); printf("����������������");
	for (i = 3; i < 23; i++) {
		gotoxy(x, y + i);	printf("��            ��");
	}
	gotoxy(x, y + 23); printf("����������������");
	gotoxy(x + 12, y + 3); printf("��");
	gotoxy(x + 12, y + 22); printf("��");

	// ��� â (��¸�)
	CommandBox(17, 5);
	ShowCommandMenu(21, 7, -1);

	// ���� ��
	while (login) {
		if (kbhit() == TRUE) {
			ch = getch();
			if (howmany_C == 0) {
				AnyClient(27, 12);
				ShowCommandMenu(21, 7, -1);
			}
			else if (ch == ESC) {
				if (sel_clt_cnt != 0) {
					memset(is_select, 0, 512);
					sel_clt_cnt = 0;
					all = FALSE;
				}
				else {
					// "�����Ͻðڽ��ϱ�?
				}
			}
			else if (ch == SPACE) {
				if (is_select[clt_arrow + (page * LINE)] == FALSE) {
					select[sel_clt_cnt++] = clt_arrow + (page * LINE);
					is_select[clt_arrow + (page * LINE)] = TRUE;
				}
				else {
					select[sel_clt_cnt--] = NULL; // ���� ��¼��
					is_select[clt_arrow + (page * LINE)] = FALSE;
				}
				if (sel_clt_cnt != howmany_C) {
					all = FALSE;
				}
				// Ŭ���̾�Ʈ ����
			}
			else if (ch == ENTER) {
				WipeArrow(x + 2, y + 4, clt_arrow);
				PrintList(x, y + 1, LINE, -1, page);
				if (sel_clt_cnt != 0) {
					return; // ��� while ȣ��
				}
				else {
					select[sel_clt_cnt++] = clt_arrow + (page * LINE);
					is_select[clt_arrow + (page * LINE)] = TRUE;
					return;
				}
				// "������ Ŭ���̾�Ʈ �����ϴ�"
			}
			else if (ch == 'a') {
				memset(is_select, 0, 512);
				sel_clt_cnt = 0;
				if (all == FALSE) {
					WipeArrow(x + 2, y + 4, clt_arrow);
					PrintList(x, y + 1, LINE, -1, page);
					sel_clt_cnt = howmany_C;
					for (i = 0; i < sel_clt_cnt; i++) {
						select[i] = i;
						is_select[i + (page * LINE)] = TRUE;
					}
					all = TRUE;
				}
				else {
					sel_clt_cnt = 0;
					all = FALSE;
				}

			}
			else if (ch == SPECIAL1 || ch == SPECIAL2) {
				ch = getch();
				switch (ch) {
				case UP:
					if (page == last_page && clt_arrow == 0) {
						clt_arrow = (howmany_C % LINE) - 1;
					}
					else if (clt_arrow > 0) {
						clt_arrow--;
					}
					else {
						clt_arrow = 16;
					}
					WipeArrow(x + 2, y + 4, clt_arrow);
					break;
				case DOWN:
					if (page == last_page && clt_arrow >= (howmany_C % LINE) - 1) {
						clt_arrow = 0;
					}
					else if (clt_arrow < 16) {
						clt_arrow++;
					}
					else {
						clt_arrow = 0;
					}
					WipeArrow(x + 2, y + 4, clt_arrow);
					break;

				case LEFT:
					if (page > 0) {
						page--;
						clt_arrow = 0;
					}
					break;
				case RIGHT:
					if (page < last_page) {
						clt_arrow = 0;
						page++;
					}
					break;
				}
			}
		}
		// ��� ��
		PrintList(x, y + 1, LINE, clt_arrow, page);	// ����Ʈ ���
		ShowServerInfo(61, 21);
		PresentTime();
		removeCursor();

		if (howmany_C != 0) {
			ShowArrow(x + 2, y + 5, clt_arrow);
			ShowCltInfo(20, 19, clt_arrow + (page * LINE));				// ���� ���
			//ShowCommandMenu(21, 7, -1);
			ScrollCursor(x, y, clt_arrow + (page * LINE));
		}

		// ���� �ο� ���
		textcolor(WHITE, BLACK);
		gotoxy(x + 2, y); printf("���� ��");
		gotoxy(x + 12, y);
		if (howmany_C != 0) {
			gotoxy(x + 10, y);	printf("    ");
			gotoxy(x + 12, y);
			textcolor(GREEN2, BLACK); printf("%d", howmany_C);
		}
		else {
			gotoxy(x + 10, y);
			textcolor(RED2, BLACK); printf("����");
		}

		Sleep(90);
	}
}

void ShowCltInfo(int x, int y, int clt) {
	textcolor(WHITE, BLACK);
	gotoxy(x, y); printf("�� �� Ŭ���̾�Ʈ ���� ��������������");
	gotoxy(x, y + 1); printf("��                                ��");
	gotoxy(x, y + 2); printf("��                                ��");
	gotoxy(x, y + 3); printf("��                                ��");
	gotoxy(x, y + 4); printf("������������������������������������");

	if (howmany_C == 0) {
		gotoxy(x + 2, y + 1); printf("                          ");
		gotoxy(x + 4, y + 2); printf("                          ");
		gotoxy(x + 2, y + 3); printf("                          ");
	}

	else if (clt == -1) {
		gotoxy(x + 2, y + 1); printf("                          ");
		gotoxy(x + 4, y + 2); printf("                          ");
		gotoxy(x + 4, y + 2); printf("%d���� Ŭ���̾�Ʈ", sel_clt_cnt);
		gotoxy(x + 2, y + 3); printf("                          ");
	}
	else {
		textcolor(YELLOW2, BLACK);
		gotoxy(x + 25, y); printf("%2d", sel_clt_cnt);
		textcolor(WHITE, BLACK);
		gotoxy(x + 27, y); printf("�� ����", sel_clt_cnt);
		gotoxy(x + 4, y + 1); printf("CLT%.3d", clt + 1);
		gotoxy(x + 4, y + 2); printf("IP         %s", Client_List[clt].IP_ADDR);
		gotoxy(x + 4, y + 3); printf("MAC        %s", Client_List[clt].MAC_ADDR);
	}
}

int ShowCommandMenu(int x, int y, int arrow) {

	int i;
	char menu[6][32] = { "���� ����", "���� ���", "�޽��� ����", "�������� ����", "���ͳ� ���� ����/����","���� ����" };
	ClrBox();
	for (i = 0; i < 6; i++) {
		gotoxy(x, y + 2 * i);
		if (i == arrow) {
			textcolor(BLACK, BLACK); printf(" ");
			textcolor(BLACK, YELLOW2); printf(" ");
			textcolor(WHITE, BLACK); printf(" %s", menu[i]);
		}
		else {
			textcolor(BLACK, GRAY2); printf(" ");
			textcolor(GRAY2, BLACK); printf(" %s", menu[i]);
		}
	}
}

void CommandBox(int x, int y) {
	int i;
	textcolor(WHITE, BLACK);
	gotoxy(x, y); printf("������������������������������������������");
	for (i = 0; i < 18; i++) {
		gotoxy(x, y + 1 + i); printf("��                                      ��");
	}
	gotoxy(x, y + 19); printf("������������������������������������������");
}


int ShowCommandBox(int x, int y) {
	int i;
	// â
	CommandBox(x, y);

	// ���ۺ�
	while (login) {

		if (kbhit() == TRUE) {
			ch = getch();
			if (ch == ESC) {
				first = TRUE;
				reset = FALSE;
				break;
			}
			else if (ch == ENTER || ch == SPACE) {
				switch (cmd_arrow) {
				case 0:
					return SHUTDOWN;
					break;
				case 1:
					return SLEEP_MODE;
					break;
				case 2:
					return SEND_MESSAGE;
					break;
				case 3:
					return RUN_WEBBROWSER;
					break;
				case 4:
					return BLOCK_INTERNET;
					break;
				case 5:
					return FILE_TRANSE;
					break;
				}
			}
			else if (ch == SPECIAL1 || ch == SPECIAL2) {
				ch = getch();
				switch (ch) {
				case UP:
					if (cmd_arrow > 0) {
						cmd_arrow--;
					}
					else {
						cmd_arrow = 5;
					}
					break;
				case DOWN:
					if (cmd_arrow < 5) {
						cmd_arrow++;
					}
					else {
						cmd_arrow = 0;
					}
					break;
				case LEFT:
					break;
				case RIGHT:
					break;
				}
			}
		}
		// ���
		ShowCommandMenu(x + 4, y + 2, cmd_arrow);
		ShowCltInfo(20, 19, -1);
		Sleep(90);
		PresentTime();
		ShowServerInfo(61, 21);
		//debug(0, 0, cmd_arrow, 0);
	}
	ShowCommandMenu(x + 4, y + 2, -1); // Ȱ��ȭ ���	
}

void ClrBox() {
	int i;
	for (i = 0; i < 18; i++) {
		gotoxy(20, 6 + i); printf("                                     ");
	}
}

int ShutDownBox(int x, int y) {

	int i;
	int confirm;
	char* time_p;
	arrow = 0;

	ClrBox();
	gotoxy(x, y);
	textcolor(BLACK, YELLOW2); printf(" ");
	textcolor(WHITE, BLACK); printf(" ���� ����");
	gotoxy(x + 2, y + 2); printf("�ð� ����");

	while (login) {

		if (kbhit() == TRUE) {
			ch = getch();
			if (ch == ESC) {
				first = FALSE;
				return FALSE;
			}
			else if (ch == ENTER || ch == SPACE) {
				memset(send_time, NULL, 5);
				if (arrow == 0) {
					int flag = 0;
					textcolor(WHITE, BLACK);
					gotoxy(x + 6, y + 4);  printf("__ �� __ �п� ����");

					time_p = InputTime(x, y, SHUTDOWN);
					if (time_p == NULL) {
						continue;
					}
					else {
						memcpy(send_time, time_p, 5);
						if (strcmp(time_p, "9999") == 0) {
							flag = 2;
						}
					}

					confirm = ConfirmBox(21, 11, flag);
					ClrBox();
					gotoxy(x, y);
					textcolor(BLACK, YELLOW2); printf(" ");
					textcolor(WHITE, BLACK); printf(" ���� ����");
					gotoxy(x + 2, y + 2); printf("�ð� ����");

					if (confirm == TRUE) {
						return SHUTDOWN;
					}
					arrow = 0;
				}
				else {
					int flag = 1;
					textcolor(WHITE, BLACK);
					gotoxy(x + 6, y + 6);  printf("__ �ð� __ �� �Ŀ� ����");

					time_p = InputTime(x, y, SHUTDOWN_T);
					if (time_p == NULL) {
						continue;
					}
					else {
						memcpy(send_time, time_p, 5);
						if (strcmp(time_p, "0000") == 0) {
							flag = 2;
						}
					}

					confirm = ConfirmBox(21, 11, flag);
					ClrBox();
					gotoxy(x, y);
					textcolor(BLACK, YELLOW2); printf(" ");
					textcolor(WHITE, BLACK); printf(" ���� ����");
					gotoxy(x + 2, y + 2); printf("�ð� ����");

					if (confirm == TRUE) {
						return SHUTDOWN_T;
					}
					arrow = 2;
				}
			}
			else if (ch == SPECIAL1 || ch == SPECIAL2) {
				ch = getch();
				switch (ch) {
				case UP:
					WipeArrow(x + 3, y + 4, arrow);
					arrow = (arrow == 2 ? 0 : 2);
					break;
				case DOWN:
					WipeArrow(x + 3, y + 4, arrow);
					arrow = (arrow == 0 ? 2 : 0);
					break;
				}
			}
		}

		textcolor(GRAY2, BLACK);
		gotoxy(x + 6, y + 4);  printf("__ �� __ �п� ����");
		gotoxy(x + 6, y + 6);  printf("__ �ð� __ �� �Ŀ� ����");

		ShowArrow(x + 3, y + 4, arrow);
		Sleep(90);
	}
}

int SleepModeBox(int x, int y) {

	int i;
	int confirm;
	char* time_p;
	arrow = 0;

	ClrBox();
	gotoxy(x, y);
	textcolor(BLACK, YELLOW2); printf(" ");
	textcolor(WHITE, BLACK); printf(" ���� ���");
	gotoxy(x + 2, y + 2); printf("�ð� ����");

	while (login) {

		if (kbhit() == TRUE) {
			ch = getch();
			if (ch == ESC) {
				first = FALSE;
				return FALSE;
			}
			else if (ch == ENTER || ch == SPACE) {

				memset(send_time, NULL, 5);
				if (arrow == 0) {
					int flag = 0;
					textcolor(WHITE, BLACK);
					gotoxy(x + 6, y + 4);  printf("__ �� __ �п� �������");

					time_p = InputTime(x, y, SLEEP_MODE);
					if (time_p == NULL) {
						continue;
					}
					else {
						memcpy(send_time, time_p, 5);
						if (strcmp(time_p, "9999") == 0) {
							flag = 2;
						}
					}
					confirm = ConfirmBox(21, 11, flag);

					ClrBox();
					gotoxy(x, y);
					textcolor(BLACK, YELLOW2); printf(" ");
					textcolor(WHITE, BLACK); printf(" ���� ����");
					gotoxy(x + 2, y + 2); printf("�ð� ����");

					if (confirm == TRUE) {
						return SLEEP_MODE;
					}
					arrow = 0;
				}
				else {
					int flag = 1;
					textcolor(WHITE, BLACK);
					gotoxy(x + 6, y + 6);  printf("__ �ð� __ �� �Ŀ� �������");
					time_p = InputTime(x, y, SLEEP_MODE_T);
					if (time_p == NULL) {
						continue;
					}
					else {
						memcpy(send_time, time_p, 5);
						if (strcmp(time_p, "0000") == 0) {
							flag = 2;
						}
					}
					confirm = ConfirmBox(21, 11, flag);;

					ClrBox();
					gotoxy(x, y);
					textcolor(BLACK, YELLOW2); printf(" ");
					textcolor(WHITE, BLACK); printf(" ���� ����");
					gotoxy(x + 2, y + 2); printf("�ð� ����");

					if (confirm == TRUE) {
						return SLEEP_MODE_T;
					}
					arrow = 2;
				}
			}
			else if (ch == SPECIAL1 || ch == SPECIAL2) {
				ch = getch();
				switch (ch) {
				case UP:
					WipeArrow(x + 3, y + 4, arrow);
					arrow = (arrow == 2 ? 0 : 2);
					break;
				case DOWN:
					WipeArrow(x + 3, y + 4, arrow);
					arrow = (arrow == 0 ? 2 : 0);
					break;
				}
			}
		}

		textcolor(GRAY2, BLACK);
		gotoxy(x + 6, y + 4);  printf("__ �� __ �п� �������");
		gotoxy(x + 6, y + 6);  printf("__ �ð� __ �� �Ŀ� �������");

		ShowArrow(x + 3, y + 4, arrow);
		Sleep(90);
	}
}

int ConfirmBox(int x, int y, int flag) {

	arrow = 0;
	char h[3] = { '\0', };
	char m[3] = { '\0', };

	//strcpy(send_time, "1234");

	memcpy(h, send_time, 2);
	memcpy(m, send_time + 2, 2);

	// â
	gotoxy(x, y); printf("����������������������������������");
	gotoxy(x, y + 1); printf("��                              ��");
	gotoxy(x, y + 2); printf("��                              ��");
	gotoxy(x, y + 3); printf("��                              ��");
	gotoxy(x, y + 4); printf("����������������������������������");


	if (flag == 0) {
		gotoxy(x + 2, y + 1); printf("%s�� %s�п� �����մϴ�.", h, m);
	}
	else if (flag == 1) {
		gotoxy(x + 2, y + 1); printf("%s�ð� %s�� �Ŀ� �����մϴ�.", h, m);
	}
	else {
		gotoxy(x + 2, y + 1); printf("���� �����մϴ�.");
	}

	while (TRUE) {


		if (kbhit() == TRUE) {
			ch = getch();
			if (ch == ESC) {
				return FALSE;
			}
			else if (ch == ENTER) {
				if (arrow == 0)
					return TRUE;
				else
					return FALSE;
			}
			else if (ch == SPECIAL1 || ch == SPECIAL2) {
				ch = getch();
				switch (ch) {
				case LEFT:
					arrow = arrow == 1 ? 0 : 1;
					break;
				case RIGHT:
					arrow = arrow == 1 ? 0 : 1;
					break;
				}
			}
		}
		if (arrow == 0) {
			textcolor(GREEN2, BLACK);
			gotoxy(x + 8, y + 3); printf("Ȯ��");
			textcolor(GRAY2, BLACK);
			gotoxy(x + 21, y + 3); printf("���");
		}
		else {
			textcolor(GRAY2, BLACK);
			gotoxy(x + 8, y + 3); printf("Ȯ��");
			textcolor(GREEN2, BLACK);
			gotoxy(x + 21, y + 3); printf("���");
		}
		//debug(0, 0, arrow, 0);
		Sleep(90);
	}

}


int RunWebBrowserBox(int x, int y) {
	int i;
	int confirm;
	arrow = 0;

	ClrBox();
	gotoxy(x, y);
	textcolor(BLACK, YELLOW2); printf(" ");
	textcolor(WHITE, BLACK); printf(" �� ������ ����");

	textcolor(WHITE, WHITE);
	gotoxy(x + 2, y + 4); printf("                             ");
	gotoxy(x + 2, y + 5); printf("                             ");
	gotoxy(x + 2, y + 6); printf("                             ");

	memset(send_web, NULL, 128);
	while (login) {

		if (kbhit() == TRUE) {
			ch = getch();
			if (ch == ESC) {
				first = FALSE;
				return FALSE;
			}
			else if (ch == ENTER || ch == SPACE) {
				if (arrow == 0) {
					textcolor(WHITE, BLACK);
					gotoxy(x + 4, y + 2);  printf("���� �� �� ������ �ּ�");
					textcolor(BLACK, WHITE);
					gotoxy(x + 3, y + 4);
					scanf("%s", send_web);
					arrow = 1;
				}
				else {
					return TRUE;
				}
			}
			else if (ch == SPECIAL1 || ch == SPECIAL2) {
				ch = getch();
				switch (ch) {
				case UP:
					WipeArrow(x + 1, y + 2, arrow);
					arrow = arrow == 0 ? 1 : 0;
					break;
				case DOWN:
					WipeArrow(x + 1, y + 2, arrow);
					arrow = arrow == 0 ? 1 : 0;
					break;
				}
			}
		}

		if (arrow == 0) {
			textcolor(RED2, BLACK); gotoxy(x + 1, y + 2);  printf("��");
			textcolor(GRAY2, BLACK); gotoxy(x + 4, y + 2);  printf("���� �� �� ������ �ּ�");

			gotoxy(x + 23, y + 8);  printf("  ");
			gotoxy(x + 26, y + 8);  printf("Ȯ��");
		}
		else {
			textcolor(GRAY2, BLACK); gotoxy(x + 1, y + 2);  printf("  ");
			textcolor(GRAY2, BLACK); gotoxy(x + 4, y + 2);  printf("���� �� �� ������ �ּ�");

			textcolor(RED2, BLACK); gotoxy(x + 23, y + 8);  printf("��");
			textcolor(WHITE, BLACK); gotoxy(x + 26, y + 8);  printf("Ȯ��");
			gotoxy(x + 1, y + 3); printf("  ");
		}
		//debug(0, 0, arrow, 0);
		Sleep(90);
	}
}

void ShowAdminInfo(int x, int y) {
	int i;
	char info[4][7] = { "���̵�", "�̸�", "���ǽ�", "IP�ּ�" };

	// â
	textcolor(WHITE, BLACK);
	gotoxy(x, y); printf("���������� ���� ����");
	for (i = 0; i < 10; i++) {
		gotoxy(x, y + 1 + i); printf("��                ��");
	}
	gotoxy(x, y + 11);  printf("��������������������");

	// ����

	textcolor(GREEN1, CYAN1);
	for (i = 0; i < 4; i++) {
		gotoxy(x + 2, y + 2 + 2 * i); printf(" ");
	}
	textcolor(WHITE, BLACK);
	for (i = 0; i < 4; i++) {
		gotoxy(x + 4, y + 2 + 2 * i); printf("%s", info[i]);
	}
	gotoxy(x + 4, y + 3); printf("%s", adminID);
	gotoxy(x + 4, y + 5);
	gotoxy(x + 4, y + 7);
	gotoxy(x + 3, y + 9); printf("%s", s.IP_ADDR);
}

void ShowServerInfo(int x, int y) {

	textcolor(BLACK, RED1);
	gotoxy(60, 21); printf(" ");
	textcolor(WHITE, BLACK);
	gotoxy(62, 21); printf("���� IP");

	gotoxy(61, 22); printf("%s", SERVER_IP);
	gotoxy(60, 24); printf("���� �������");
	gotoxy(74, 24);

	if (login) {
		textcolor(GREEN1, BLACK);
		printf("����");
	}
	else {
		textcolor(RED2, BLACK);
		printf("����");
	}
}

void PresentTime() {

	char *weeks[] = { "��", "��", "ȭ", "��", "��", "��", "��" };

	time(&time_now);
	timeinfo = localtime(&time_now);
	textcolor(WHITE, BLACK);
	gotoxy(61, 15);
	printf("%d. %d. %d (%s)", 1900 + timeinfo->tm_year, timeinfo->tm_mon + 1, timeinfo->tm_mday, weeks[timeinfo->tm_wday]);
	gotoxy(64, 17);
	textcolor((timeinfo->tm_sec) % 16, BLACK);
	printf("[       ]");
	gotoxy(65, 17);
	textcolor(WHITE, BLACK);
	printf(" %.2d:%.2d ", timeinfo->tm_hour, timeinfo->tm_min);
	if (timeinfo->tm_sec % 2 == 0) {
		gotoxy(68, 17); printf(" ");
	}
	return 0;
}

void ConnectError(int x, int y) {
	// �α��� ���� â
	textcolor(RED1, BLACK);
	gotoxy(x, y); printf("�Ʀ���������������������");
	gotoxy(x, y + 1); printf("��                    ��");
	gotoxy(x, y + 2); printf("�Ʀ���������������������");
	textcolor(WHITE, BLACK);
	gotoxy(x + 5, y + 1); printf("���� ��ȣ ����");
	removeCursor();
	Sleep(3000);

}

void SendComplete(int x, int y) {
	textcolor(GREEN2, BLACK);
	gotoxy(x, y); printf("�Ʀ���������������������");
	gotoxy(x, y + 1); printf("��                    ��");
	gotoxy(x, y + 2); printf("�Ʀ���������������������");
	textcolor(WHITE, BLACK);
	gotoxy(x + 7, y + 1); printf("���� ����");
	removeCursor();
	Sleep(1500);
}

void AnyClient(int x, int y) {
	textcolor(YELLOW1, BLACK);
	gotoxy(x, y); printf("������������������������");
	gotoxy(x, y + 1); printf("��                    ��");
	gotoxy(x, y + 2); printf("������������������������");
	textcolor(WHITE, BLACK);
	gotoxy(x + 4, y + 1); printf("Ŭ���̾�Ʈ ����");
	removeCursor();
	Sleep(500);
}

char* InputTime(int x, int y, int flag) {
	char input[5] = { '\0', };
	int cursor = 0;
	int box = 0;
	int cnt[2] = { 0, };
	int confirm = 0;

	if (flag == SHUTDOWN || flag == SLEEP_MODE) {
		while (TRUE) {
			if (kbhit() == TRUE) {
				gotoxy(x + 6 + cnt[box] + 6 * box, y + 4);
				ch = getch();
				if (ch == ESC) {
					return NULL;
				}
				else if (ch == ENTER) {
					if (cursor == 0) {
						memset(input, '9', 4);
						return input;
					}
					else if (cursor != 4) {
					}
					else {
						confirm = atoi(input);
						if (confirm / 100 <= 23 && confirm % 100 < 60)
							return input;
						else {
							// "�Է� ����!"
							continue;
						}
					}
				}
				else if (ch == BACKSPACE) {
					if (cursor >= 0) {
						if (box == 1 && cnt[box] == 0) {
							box--;
						}
						if (cursor > 0) {
							gotoxy(x + 5 + cnt[box] + 6 * box, y + 4);  printf("_");
							cursor--;
						}
						input[cursor] = NULL;
						if (cnt[box] > 0) {
							cnt[box]--;
						}
					}
				}
				else if (ch == TAB) {
				}
				else if (ch == SPECIAL1 || ch == SPECIAL2) {
				}
				else if (ch >= '0' && ch <= '9') {
					if (cursor < 4) {
						input[cursor++] = ch;
						printf("%c", ch);
						cnt[box]++;

						if (cnt[box] == 2 && box == 0) {
							box++;
							cnt[box] = 0;
						}
					}
				}
				else {
				}
			}

			Sleep(50);
		}
	}

	else if (flag == SHUTDOWN_T || flag == SLEEP_MODE_T) {
		while (TRUE) {
			if (kbhit() == TRUE) {
				gotoxy(x + 6 + cnt[box] + 8 * box, y + 6);
				ch = getch();
				if (ch == ESC) {
					return NULL;
				}
				else if (ch == ENTER) {
					if (cursor == 0) {
						memset(input, '0000', 4);
						return input;
					}
					else if (cursor != 4) {
					}
					else {
						return input;
					}
				}
				else if (ch == BACKSPACE) {
					if (cursor >= 0) {
						if (box == 1 && cnt[box] == 0) {
							box--;
						}
						if (cursor > 0) {
							gotoxy(x + 5 + cnt[box] + 8 * box, y + 6);  printf("_");
							cursor--;
						}
						input[cursor] = NULL;
						if (cnt[box] > 0) {
							cnt[box]--;
						}
					}
				}
				else if (ch == TAB) {
				}
				else if (ch == SPECIAL1 || ch == SPECIAL2) {
				}
				else if (ch >= '0' && ch <= '9') {
					if (cursor < 4) {
						input[cursor++] = ch;
						printf("%c", ch);
						cnt[box]++;

						if (cnt[box] == 2 && box == 0) {
							box++;
							cnt[box] = 0;
						}
					}
				}
				else {
				}
			}

			Sleep(50);
		}
	}
}

void ShowWatingClient() {
	while (howmany_C == 0 && login == TRUE) {
		cls(BLACK, WHITE);
		gotoxy(27, 13);  printf("Ŭ���̾�Ʈ ���� �����");

		switch ((ui_flag++) % 4) {
		case 0:
			gotoxy(49, 13); printf(".");
			break;
		case 1:
			gotoxy(49, 13); printf("..");
			break;
		case 2:
			gotoxy(49, 13); printf("...");
			break;
		case 3:
			gotoxy(49, 13); printf("   ");
			break;
			removeCursor();
		}
		Sleep(500);
	}
}

void ScrollCursor(int x, int y, int arrow) {

	int i;
	int p = ((arrow + 1) * 17) / howmany_C;
	int tmp = p;

	for (i = 0; i < 18; i++) {
		gotoxy(x + 12, y + 4 + i);
		printf("  ");
	}
	gotoxy(x + 12, y + 4 + p);
	textcolor(GRAY2, BLACK);
	printf("��");
}

//void show