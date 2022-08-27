#include "header.h"

int connectA = 0;
int connectS = 0;

void main() {
	int printConnectCheck = 0;

	srand(time(NULL));

	//���α׷� â�� ����
	HWND hWndConsole = GetConsoleWindow();
	ShowWindow(hWndConsole, SW_HIDE);

	WSAStartup(MAKEWORD(2, 0), &wsadata);
	//���� ����
	srvSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (srvSocket == INVALID_SOCKET) {
		printf("#error here 1\n");
	}

	//���α׷� ���� �� ������ ����
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

	//������ ���� & ���⺸��
	while (1) {
		if (connectA == 0 && is_AdmAddrRecv==0) { //�����ڿ� ��������� ���� ������

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
			}//�����κ��� �������� ������ �޴� ������ ����
		}
		else
			printConnectCheck = 0;
	}

	closesocket(srvSocket);
	closesocket(admSocket);
	WSACleanup();
}

UINT WINAPI RecvServ_Thread(void *arg) {
	//�����κ��� ������ �������� ������ �޴� ������
	int recvSize;
	int recvID;
	int recvDataType;
	int *p = buf;
	char *adminIP = buf;

	recvServThread = 1;
	printf("Start RecvServ_Thread\n");

	memset(buf, NULL, sizeof(buf));

	if (recv(srvSocket, buf, 12, 0) > 0) {
		//�������� ������ ������
		int printConnectCheck = 0;
		recvSize = p[0];
		recvID = p[1];
		recvDataType = p[2];

		memset(buf, NULL, sizeof(buf));
		recv(srvSocket, buf, recvSize, 0);
		//������ ������ �������� IP ("000.000.000.000")�� ���ۿ� ����
		
		is_AdmAddrRecv = 1;
		printf("Received! AdmAddr Information (%s)\n", buf);

		closesocket(srvSocket);
		connectS = 0;
		printf("Disconnect from Server\n");

		//�����ڷ� �����ϱ�
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
		}//������ ���� ���� �� ������ ����

		connectA = 1;
		init_sockState(ADMINISTRATOR);

		//�����ڿ��� ���⺸�� & ����ޱ�
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
					}//������ ���� ���� �� ������ ����

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
				}//�����ڷκ��� recv ������ ����
			}
			else {
				break;
			}//�����ڿ� ������ �������� �����带 ����
		}
	}
	recvServThread = 0;
	printf("End RecvServ_Thread\n");
}

UINT WINAPI RecvAdmin_Thread(void *arg) {
	//�����ڷκ��� ack�� ��������� �޴� ������
	int recvSize;
	int recvID;
	int recvDataType;
	int *p = buf;
	TIME Now;

	recvAdmThread = 1;
	printf("Start RecvAdmin_Thread\n");

	//���ͳ� ���� ���� ������ (RecvAdmin �����尡 ����Ǹ� ���� ���� �� (=�����ڿ� ������ ����� �ڵ� ����))
	internetBlock = 0;
	hThread = (HANDLE)_beginthreadex(NULL, 0, InternetBlock_Thread, NULL, 0, (unsigned*)&dwThreadID);

	memset(buf, NULL, sizeof(buf));

	while (recv(admSocket, buf, 12, 0) > 0) {
		int printConnectCheck = 0;
		
		recvSize =p[0];
		recvID = p[1];
		recvDataType = p[2];

		//�ϴ� ���� data�� buf�� ��Ƶ� (buf�� ��������)
		memset(buf, NULL, sizeof(buf));
		recv(admSocket, buf, recvSize, 0);

		if (recvDataType != ACK)
			printf("ORDER RECEIVE!!!!!\n");

		//ACK�� ���� a.Time ���� ����
		if (recvDataType == ACK)
			a.Time = time(NULL);

		Now = time(NULL);
		//ACK �ð� �ʰ�
		if (((Now - a.Time) / 60) > FREQUENT) {
			printf("((Now - a.Time) / 60) > FREQUENT\n");
			//�����ڿ��� ������ ����
			closesocket(admSocket);
			connectA = 0;
			printf("Disconnect from Administrator\n");

			//���� ���� �����尡 ������̸� ������ ������ �� �� �ֵ��� ��ٷ��ش�
			//(RecvAdmin�����尡 ������ ���������嵵 �������� �Ǳ� ����)
			if (sleepTimerThread == 1) {
				Sleep(sleepOrderSecond * SECOND);
			}

			//������ ������
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

			//������ ������
			break;
		}

		//��� ó��
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
			printf("���ͳ� ����\n"); 
			internetBlock = 1; 
			break;
		case FREE_INTBLOCK: 
			printf("���ͳ� ���� ����\n"); 
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