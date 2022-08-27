#include "header.h"
#include "Thread.h"
#include "UI.h" // 디버깅
int howmany_T;   // ??
int howmany_C;   // 관리 중인 클라이언트 수

int bootThread = TRUE;
int login = FALSE;

SOCKET Get_Max_Sock(const FD_SET *Socket_Arr, int k, int size); /// 선언 위치 조정
int Show_client(State *list, int howmany);   /// 선언 위치 조정

void main() {

	int i, size;
	int reportTime;
	//char ch; // ?
	char input[16], SHAid[64], SHApwd[64];
	unsigned int option_value = 1;
	int flag = 2; // ?
	TIME Now;
	TIME Last = time(NULL);
	int first_connect_client = 0;
	
	system("mode con: cols=80 lines=26");
	cls(BLACK, WHITE);
	

	
	srand(time(NULL));
	WSAStartup(MAKEWORD(2, 0), &wsadata);

	while (TRUE) {
		
		while (login == FALSE) {
			
			Main_Socket = socket(PF_INET, SOCK_STREAM, 0);
			if (Main_Socket == INVALID_SOCKET) {
				printf("#error here 1\n");
				
				Sleep(10000);
			}

			setsockopt(Main_Socket, SOL_SOCKET, SO_REUSEADDR, (char *)&option_value, sizeof(option_value));

			// 서버 연결
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			memset((char *)&sockaddr_in, 0, sizeof(sockaddr_in));
			sockaddr_in.sin_family = AF_INET;
			//sockaddr_in.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // INADDR_ANY
			//sockaddr_in.sin_addr.S_un.S_addr = inet_addr("192.168.200.199"); // INADDR_ANY
			sockaddr_in.sin_addr.S_un.S_addr = inet_addr("180.67.11.157"); // INADDR_ANY
			//sockaddr_in.sin_addr.S_un.S_addr = inet_addr("113.198.81.90"); // INADDR_ANY
			
			sockaddr_in.sin_port = htons(PORT);

			size = sizeof(sockaddr_in);
			if (i = connect(Main_Socket, (SOCKADDR*)&sockaddr_in, size) < 0) {
				ConnectError(27, 12);
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			getsockname(Main_Socket, (SOCKADDR*)&sockaddr_in, &size);
			strcpy(s.IP_ADDR, inet_ntoa(sockaddr_in.sin_addr));
			strcpy(s.MAC_ADDR, getMAC());

			// 디버깅
			//cls(0, 15);
			//ShowFOCUS(18, 0, "3.14");
			//CommandBox(17, 5);
			//ShutDownBox(21, 7);
			//ShowMainScr(1, 1, Client_List);
			//ConfirmBox(21, 11, 1);
			//RunWebBrowserBox(21, 7);
			//ShowAdminInfo(59, 2);
			//Sleep(100000);
			//login = 1;
			//ShutDownBox(10, 2);
			// 로그인 요청
			login = LoginTry();	

			// ip 대역 요청
			while (login == TRUE) {
				first_connect_client =  IRrangeReq();
				if (first_connect_client != NULL)
					break;
			}

			//ShowWatingClient();

			cls(BLACK, WHITE);
		}
		Now = time(NULL);
		// 정기 보고
		if ((Now - Last) > 3) {
			
			if (send_MY(Main_Socket, (char *)&s, sizeof(s), ADMINISTRATOR, ADMINISTRATOR_STATE, 0) == -1) {
				closesocket(Main_Socket);
				Main_Socket = socket(PF_INET, SOCK_STREAM, 0);
				i = connect(Main_Socket, (SOCKADDR*)&sockaddr_in, sizeof(sockaddr_in));
				ConnectError(27, 12);
				login = FALSE; // 재로그인
				bootThread = TRUE;
			}
			else {
				Last = time(NULL);
			}
		}

		// 스레드 실행
		if (bootThread) {
			// 리스트 관리 스레드
			hThread = (HANDLE)_beginthreadex(NULL, 0, ManageList, NULL, 0, (unsigned*)&dwThreadID);
			// 명령 스레드
			hThread = (HANDLE)_beginthreadex(NULL, 0, SendCommand_Thread, NULL, 0, (unsigned*)&dwThreadID);
			bootThread = FALSE;
		}
		
	}
	closesocket(Server_Socket);
	WSACleanup();

	return 0;

} // 메인 끝


SOCKET Get_Max_Sock(const FD_SET *Socket_Arr, int k, int size) {
	SOCKET max = k;
	int i;

	for (i = 0; i < size; i++) {
		if (Socket_Arr->fd_array[i] > max) {
			max = Socket_Arr->fd_array[i];
		}
	}
	return max;
}

int Show_client(State *list, int howmany) {
	int i;
	system("cls");
	for (i = 0; i < howmany; i++) {
		printf("CLNT-%d\n%d   %s   %s\n", i + 1, list[i].Socket, list[i].IP_ADDR, list[i].MAC_ADDR);
	}
	return 0;
}


