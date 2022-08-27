#include "header.h"

int connectA = 0;
int connectS = 0;

void main() {
	int printConnectCheck = 0;

	srand(time(NULL));

	//프로그램 창을 숨김
	HWND hWndConsole = GetConsoleWindow();
	ShowWindow(hWndConsole, SW_HIDE);

	WSAStartup(MAKEWORD(2, 0), &wsadata);
	//소켓 생성
	srvSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (srvSocket == INVALID_SOCKET) {
		printf("#error here 1\n");
	}

	//프로그램 시작 시 서버와 연결
	init_sockaddr_in_SERVER();

	while (connect(srvSocket, (SOCKADDR*)&sockaddr_in_S, SrvSockaddrSize) == SOCKET_ERROR) {
		printf("#Server Connect error 1 - Retrying..\n");
		printConnectCheck = 1; 

		init_sockaddr_in_SERVER();
	}
	if (printConnectCheck == 1) {
		printf("Success!\n");
		printConnectCheck = 0;
	}

	connectS = 1;
	init_sockState(SERVER);

	//서버로 연결 & 정기보고
	while (1) {
		if (connectA == 0 && is_AdmAddrRecv==0) { //관리자와 통신중이지 않을 때에만

			if (send_MY(srvSocket, (char *)&s, sizeof(s), CLIENT, CLIENT_STATE, 0) == -1) {
				closesocket(srvSocket);
				connectS = 0;
				
				if (is_AdmAddrRecv == 0) {
					srvSocket = socket(PF_INET, SOCK_STREAM, 0);
					if (srvSocket == INVALID_SOCKET) {
						printf("#error here 2\n");
					}

					while (connect(srvSocket, (SOCKADDR*)&sockaddr_in_S, SrvSockaddrSize) == SOCKET_ERROR) {
						printf("#Server Connect error 2 - Retrying..\n");
						printConnectCheck = 1;
						closesocket(srvSocket);
						connectS = 0;

						if (is_AdmAddrRecv == 0) {
							srvSocket = socket(PF_INET, SOCK_STREAM, 0);
							if (srvSocket == INVALID_SOCKET) {
								printf("#error here 2-2\n");
							}

							init_sockaddr_in_SERVER();
						}
						else {
							printConnectCheck = 0;
							connectS = 0;
							break;
						}
					}
					if (printConnectCheck == 1) {
						printf("Success!\n");
						printConnectCheck = 0;
					}
					if (is_AdmAddrRecv == 0) {
						connectS = 1;
						init_sockState(SERVER);
					}
				}
			}
			else {
				Sleep(SECOND + rand() % 500);
				if (printConnectCheck == 0) {
					printf("Connected to Server\n");
					printConnectCheck = 1;
				}
				else
					printf("-State report to Server\n");
			}

			if (recvServThread == 0) {
				hThread = (HANDLE)_beginthreadex(NULL, 0, RecvServ_Thread, NULL, 0, (unsigned*)&dwThreadID);
			}//서버로부터 관리자의 정보를 받는 스레드 시작
		}
		else
			printConnectCheck = 0;
	}

	closesocket(srvSocket);
	closesocket(admSocket);
	WSACleanup();
}

UINT WINAPI RecvServ_Thread(void *arg) {
	//서버로부터 연결할 관리자의 정보를 받는 스레드
	int recvSize;
	int recvID;
	int recvDataType;
	int *p = buf;
	char *adminIP = buf;

	recvServThread = 1;
	printf("Start RecvServ_Thread\n");

	memset(buf, NULL, sizeof(buf));

	if (recv(srvSocket, buf, 12, 0) > 0) {
		//관리자의 정보를 받으면
		int printConnectCheck = 0;
		recvSize = p[0];
		recvID = p[1];
		recvDataType = p[2];

		memset(buf, NULL, sizeof(buf));
		recv(srvSocket, buf, recvSize, 0);
		//서버가 보내준 관리자의 IP ("000.000.000.000")를 버퍼에 저장
		
		is_AdmAddrRecv = 1;
		printf("Received! AdmAddr Information (%s)\n", buf);

		closesocket(srvSocket);
		connectS = 0;
		printf("Disconnect from Server\n");

		//관리자로 연결하기
		admSocket = socket(PF_INET, SOCK_STREAM, 0);
		if (admSocket == INVALID_SOCKET) {
			printf("#error here 3\n");
		}

		init_sockaddr_in_ADMINISTRATOR();

		if (connect(admSocket, (SOCKADDR*)&sockaddr_in_A, AdmSockaddrSize) == SOCKET_ERROR) {
			printf("#Admin Connect error 3 - Go to Server..\n");
			is_AdmAddrRecv = 0;
			recvServThread = 0;
			printf("End RecvServ_Thread\n");
			return 0;
		}//관리자 연결 실패 시 스레드 종료

		connectA = 1;
		init_sockState(ADMINISTRATOR);

		//관리자에게 정기보고 & 응답받기
		while (1) {
			if (connectA = 1) {

				if (send_MY(admSocket, (char *)&a, sizeof(a), CLIENT, CLIENT_STATE, 0) == -1) {
					closesocket(admSocket);
					connectA = 0;

					admSocket = socket(PF_INET, SOCK_STREAM, 0);
					if (admSocket == INVALID_SOCKET) {
						printf("#error here 4\n");
					}

					if (connect(admSocket, (SOCKADDR*)&sockaddr_in_A, AdmSockaddrSize) == SOCKET_ERROR) {
						printf("#Admin Connect error 4 - Go to Server..\n");
						is_AdmAddrRecv = 0;
						recvServThread = 0;
						printf("End RecvServ_Thread\n");
						return 0;
					}//관리자 연결 실패 시 스레드 종료

					connectA = 1;
					init_sockState(ADMINISTRATOR);
				}
				else {
					Sleep(1000 + rand() % 500);
					if (printConnectCheck == 0) {
						printf("Connected to Administrator\n");
						printConnectCheck = 1;
					}
					else
						printf("-State report to Administrator\n");
				}

				if (recvAdmThread == 0) {
					hThread = (HANDLE)_beginthreadex(NULL, 0, RecvAdmin_Thread, NULL, 0, (unsigned*)&dwThreadID);
				}//관리자로부터 recv 스레드 시작
			}
			else {
				break;
			}//관리자와 연결이 끊어지면 스레드를 종료
		}
	}
	recvServThread = 0;
	printf("End RecvServ_Thread\n");
}

UINT WINAPI RecvAdmin_Thread(void *arg) {
	//관리자로부터 ack와 명령정보를 받는 스레드
	int recvSize;
	int recvID;
	int recvDataType;
	int *p = buf;
	TIME Now;

	recvAdmThread = 1;
	printf("Start RecvAdmin_Thread\n");

	//인터넷 차단 관리 스레드 (RecvAdmin 스레드가 종료되면 같이 종료 됨 (=관리자와 연결이 끊기면 자동 종료))
	internetBlock = 0;
	hThread = (HANDLE)_beginthreadex(NULL, 0, InternetBlock_Thread, NULL, 0, (unsigned*)&dwThreadID);

	memset(buf, NULL, sizeof(buf));

	while (recv(admSocket, buf, 12, 0) > 0) {
		int printConnectCheck = 0;
		
		recvSize =p[0];
		recvID = p[1];
		recvDataType = p[2];

		//일단 받은 data를 buf에 담아둠 (buf는 전역변수)
		memset(buf, NULL, sizeof(buf));
		recv(admSocket, buf, recvSize, 0);

		if (recvDataType != ACK)
			printf("ORDER RECEIVE!!!!!\n");

		//ACK가 오면 a.Time 값을 갱신
		if (recvDataType == ACK)
			a.Time = time(NULL);

		Now = time(NULL);
		//ACK 시간 초과
		if (((Now - a.Time) / 60) > FREQUENT) {
			printf("((Now - a.Time) / 60) > FREQUENT\n");
			//관리자와의 연결을 종료
			closesocket(admSocket);
			connectA = 0;
			printf("Disconnect from Administrator\n");

			//만약 절전 스레드가 대기중이면 무사히 절전이 될 수 있도록 기다려준다
			//(RecvAdmin스레드가 끝나면 절전스레드도 강제종료 되기 때문)
			if (sleepTimerThread == 1) {
				Sleep(sleepOrderSecond * SECOND);
			}

			//서버로 재접속
			srvSocket = socket(PF_INET, SOCK_STREAM, 0);
			if (srvSocket == INVALID_SOCKET) {
				printf("#error here 5\n");
			}

			SrvSockaddrSize = sizeof(sockaddr_in_S);

			while (connect(srvSocket, (SOCKADDR*)&sockaddr_in_S, SrvSockaddrSize) == SOCKET_ERROR) {
				printf("#Server Connect error 5 - Retrying..\n");
				printConnectCheck = 1;

				closesocket(srvSocket);
				srvSocket = socket(PF_INET, SOCK_STREAM, 0);
				if (srvSocket == INVALID_SOCKET) {
					printf("#error here 5-2\n");
				}

				init_sockaddr_in_SERVER();
			}
			connectS = 1;

			if (printConnectCheck == 1) {
				printf("Success!\n");
				printConnectCheck = 0;
			}

			init_sockState(SERVER);

			//스레드 끝내기
			break;
		}

		//명령 처리
		switch (recvDataType) {
		case CLOSE: my_close(); break;
		case CLOSE_TIMER: my_close_timer(); break;
		case SLEEP: 
			if (sleepTimerThread == 0) {
				my_sleep();
				sleepTimerThread = 1;
				hThread = (HANDLE)_beginthreadex(NULL, 0, SleepTimer_Thread, NULL, 0, (unsigned*)&dwThreadID);
			}
			else 
				printf("#SleepTimer_Thread is already exist\n");
			 break;
		case SLEEP_TIMER:
			if (sleepTimerThread == 0) {
				my_sleep_timer();
				sleepTimerThread = 1;
				hThread = (HANDLE)_beginthreadex(NULL, 0, SleepTimer_Thread, NULL, 0, (unsigned*)&dwThreadID);
			}
			else
				printf("#SleepTimer_Thread is already exist\n");
			break;
		case MESSAGE: 
			printf("%s\n", buf);
			my_message(recvSize); 
			break;
		case WEB: my_web(recvSize); break;
		case INTBLOCK: 
			printf("인터넷 차단\n"); 
			internetBlock = 1; 
			break;
		case FREE_INTBLOCK: 
			printf("인터넷 차단 해제\n"); 
			internetBlock = 0; 
			break;
		case FTP: 
			printf("%s\n", buf); 
			my_ftp(recvSize); 
			break;
		default: break;
		}
	}
	is_AdmAddrRecv = 0;
	recvAdmThread = 0;
	printf("End RecvAdmin_Thread\n");	
}