#include "Thread.h"
#include "header.h"
#include "UI.h"
char message[256];

int Select_Clinet();
int Show_User(State *list, int howmany);

UINT WINAPI SendCommand_Thread(void *arg) {
	int i;
	char select;
	int Selected_Client[CLIENT_SIZE]; // 선택된 클라이언트의 '인덱스'
	reset = TRUE;
	first = TRUE;
	
	while (1) {
		int flag;
		ShowAdminInfo(59, 2);
		if (first == TRUE) {
			ShowMainScr(1, 1, Selected_Client);
		}
		select = ShowCommandBox(17, 5);    

		switch (select) {
			
		case SHUTDOWN:  // 임시로
			flag = ShutDownBox(21,7);
			if (flag != FALSE) {
				ShutDown(send_time, sel_clt_cnt, Selected_Client, flag);
				first = TRUE;
				reset = TRUE;				
			}
			break;

		case SLEEP_MODE:
			flag = SleepModeBox(21, 7);
			if (flag != FALSE) {
				SleepMode(send_time, sel_clt_cnt, Selected_Client, flag);
				first = TRUE;
				reset = TRUE;
			}
			break;

		case SEND_MESSAGE:
			textcolor(WHITE, BLACK);
			MessageSend(sel_clt_cnt, Selected_Client);
			first = TRUE;
			reset = TRUE;
			break;

		case RUN_WEBBROWSER:
			flag = RunWebBrowserBox(21, 7);  
			if (flag != FALSE) {
				RunWebBrowser(sel_clt_cnt, Selected_Client);
				first = TRUE;
				reset = TRUE;
			}
			break;

		case BLOCK_INTERNET:
			flag = 0;
			printf(" flag 입력 : ");
			scanf("%d", &flag);
			BlockInternet(sel_clt_cnt, Selected_Client,flag);
			first = TRUE;
			reset = TRUE;
			break;

		case FILE_TRANSE:
			FileTranse(sel_clt_cnt, Selected_Client);  
			first = TRUE;
			reset = TRUE;
			break;

		default:
			break;
		}
		PresentTime();
		ShowServerInfo(61, 21);
	}
}

int Show_User(State *list, int howmany_C) {
	int i;
	char *tmp;

	for (i = 0; i < howmany_C; i++) {
		tmp = &list[i];
		printf("CLIENT-%d\n %d	%s	%s\n", i + 1, list[i].Socket, list[i].IP_ADDR, list[i].MAC_ADDR);
	}
	return 0;
}