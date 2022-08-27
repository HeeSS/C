#include "header.h"

void Show_MSG(char * messege);
void Print_line();
void Print_Administrator_List();
void Print_Client_List();

// Thread
HANDLE  hThread;							// �����带 �ϱ����� ���� �׳� �ϴ��� �ܿ��
DWORD   dwThreadID;							// �����带 �ϱ����� ����
UINT WINAPI ThreadFunction(void *arg);		// ������ ȣ�� �Լ�

// Winsock
WSADATA wsadata;

SOCKADDR_IN sockaddr_in;					// ���� ���� ���� ����ü (�������� ��)
int sockaddr_size = sizeof(SOCKADDR_IN);

State_A Administrator_List[ADMINISTRATOR_SIZE];	// Ŭ���̾�Ʈ ������ ����ü �迭
State_C Client_List[CLIENT_SIZE];
Temp Temp_List[HOST_SIZE];// ������ ������ ����ü �迭

int howmany_A = 0;							// �������� ������ ��
int howmany_C = 0;							// Ŭ���̾�Ʈ�� ������ ��
int howmany_T = 0;

Table table;

SOCKET Server_Socket;						// ������ �� ���� ����
SOCKET Max_Socket;							// fd_set �迭�� �˻��� �ִ� ���Ϲ�ȣ

fd_set  Socket_Arr;							// ����(���� ��ũ����)�� �����Ͽ� �˻��� ����ü(�迭)

// Global Variable
						// ������ �ȵ� ������ ��

char MY_IP[30];

char buf[BUFSIZE];							// �ӽ� ����

void main() {
	int i;
	char ch = 0;
	unsigned int option_value = 1;

	system("mode con: cols=121 lines=40");
	Print_line();
	Show_MSG("FOCUS SERVER OPEN");

	/////////////////////////////////////////////////////////
	WSAStartup(MAKEWORD(2, 0), &wsadata);

	Table_Init(&table);

	Server_Socket = socket(PF_INET, SOCK_STREAM, 0);
	//�������� ü��,��Ʈ���� ���� �ŷڼ� ���������, ��������(�⺻0���� ��������)
	//INVALID_SOKET�� ���� ���� ���и� ���ϰ� -1�� ���ǵǾ��ִ�.

	if (Server_Socket == INVALID_SOCKET) {
		Show_MSG("SOKET ���� ����");
		Sleep(10000);
	}

	Show_MSG("SOKET ���� ����");

	setsockopt(Server_Socket, SOL_SOCKET, SO_REUSEADDR, (char *)&option_value, sizeof(option_value));
	//int setsockopt( SOCKET s,int level,int optname,const char FAR* optval,int optlen);
	//SO_REUSEADDR �ɼ��� �����ϸ� Ŀ���� ������ ��Ʈ�� ���� ���� ���¿����� bind �Լ� ȣ���� ���� ->������ ��Ʈ�� ������ �ش� ��Ʈ�� bind�� ����

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	memset((char *)&sockaddr_in, 0, sizeof(sockaddr_in));
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	sockaddr_in.sin_port = htons(PORT);

	if (bind(Server_Socket, (SOCKADDR *)&sockaddr_in, sizeof(sockaddr_in)) < 0) {
		Show_MSG("SOCKET BIND ����"); 
		Sleep(10000);
	}

	Show_MSG("SOCKET BIND ����");

	if (listen(Server_Socket, CLIENT_SIZE) == -1) {
		Show_MSG("LISTEN ����");
		Sleep(10000);
	}

	Show_MSG("LISTEN ����");
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction, NULL, 0, (unsigned*)&dwThreadID);

	while (TRUE) {
		Sleep(300);
		if (rand() % 100 < 5) {
			Print_line();
		}

		switch (ch) {
		case 'l':
			Print_Administrator_List();
			Print_Client_List();
			break;
		case 'c':
			Print_Client_List();
			break;
		case 'a':
			Print_Administrator_List();
			break;
		case 'e':
			break;
		default:
			ch = getch();
			break;
		}		
	}
}

UINT WINAPI ThreadFunction(void *arg) {
	SOCKET Tmp_SOCK;
	TIME Now;

	int i, j, k, l;
	int *p = buf, size = 0, id = 0, datatype = 0;
	int flag;
	unsigned int addr;

	char ID[65];
	char PWD[65];
	char Buf[512];
	char tmp[30];
	char *IP = buf, *MAC = IP + 30;
	unsigned int IP1, IP2;

	struct timeval val;

	val.tv_sec = 0;
	val.tv_usec = 100;


	Show_MSG("SERVER LIST THREAD �۵�");

	Max_Socket = Server_Socket + 1;

	while (TRUE) {
		Now = time(NULL);

		FD_ZERO(&Socket_Arr);
		// �ʱ�ȭ

		FD_SET(Server_Socket, &Socket_Arr);
		// �������� ���

		for (i = 0; i < howmany_T; i++) {
			FD_SET(Temp_List[i].Socket, &Socket_Arr);
		}
		// ������ �ȵ� ���ϵ� ���

		for (i = 0; i < howmany_A; i++) {
			FD_SET(Administrator_List[i].Socket, &Socket_Arr);
		}
		// ���ӵ� �����ڵ� ���� ���

		for (i = 0; i < howmany_C; i++) {
			FD_SET(Client_List[i].Socket, &Socket_Arr);
		}
		// ���ӵ� Ŭ���̾�Ʈ�� ���� ���

		Max_Socket = Get_Max_Sock(&Socket_Arr, Server_Socket, ADMINISTRATOR_SIZE) + 1;     /* maxfdp1 �� ��� */
																						   // �˻��� ���� �ִ��ȣ ȹ��

		if (select(Max_Socket, &Socket_Arr, (fd_set *)0, (fd_set *)0, &val) < 0) {
			printf("#error here 5\n");
			Sleep(10000);
		}
		// ���ϵ鿡 ��ȭ�� �ִ��� ������ �˻��ϴ� �Լ�

		if (FD_ISSET(Server_Socket, &Socket_Arr)) {
			sockaddr_size = sizeof(SOCKADDR);
			Tmp_SOCK = accept(Server_Socket, (struct sockaddr *)&sockaddr_in, &sockaddr_size);

			if (Tmp_SOCK == -1) {
				printf("#error here 6\n");
				Sleep(10000);
			}
			else {
				Temp_List[howmany_T].Socket = Tmp_SOCK;				
				strcpy(Temp_List[howmany_T].IP_ADDR, inet_ntoa(sockaddr_in.sin_addr));
				Temp_List[howmany_T].IP_ADDR_INT = IP2INT(Temp_List[howmany_T].IP_ADDR);
				howmany_T++;
				continue;
			}
		}

		for (i = 0; i < howmany_T; i++) {
			if (FD_ISSET(Temp_List[i].Socket, &Socket_Arr)) {
				memset(buf, NULL, sizeof(buf));
				if (recv(Temp_List[i].Socket, buf, 12, 0)>0) {
					size = p[0];
					id = p[1];
					datatype = p[2];
					recv(Temp_List[i].Socket, buf, size, 0);

					switch (id) {
					case ADMINISTRATOR:
						if (datatype == ADMINISTRATOR_LOGIN) {
							Show_MSG("ADMINISTRATOR �α��� �õ�");
							memcpy(ID, buf, 64);
							memcpy(PWD, buf + 64, 64);
							ID[64] = NULL;
							PWD[64] = NULL;

							if (Login(ID, PWD)) {
								Show_MSG("ADMINISTRATOR �α��� ����");
								Administrator_List[howmany_A].Socket = Temp_List[i].Socket;								
								memcpy(Administrator_List[howmany_A].IP_ADDR, Temp_List[i].IP_ADDR, sizeof(char) * 30);
								Administrator_List[howmany_A].Time = time(NULL);
								Administrator_List[howmany_A].LOGIN = TRUE;

								memset(&Temp_List[i], NULL, sizeof(Temp));
								memcpy(&Temp_List[i], &Temp_List[i + 1], sizeof(Temp)*(HOST_SIZE - 1 - i));								

								send_MY(Administrator_List[howmany_A].Socket, "LOGINSUCCESS", 30, SERVER, 0, 0);

								howmany_A++;
								howmany_T--;
							}
							else {
								Show_MSG("ADMINISTRATOR �α��� ����");
								send_MY(Administrator_List[howmany_A].Socket, "FAIL", 30, SERVER, 0, 0);
								closesocket(Temp_List[i].Socket);
								memset(&Temp_List[i], NULL, sizeof(Temp));
								memcpy(&Temp_List[i], &Temp_List[i + 1], sizeof(Temp)*(HOST_SIZE - 1 - i));
								howmany_T--;
							}
						}
						else {
							Show_MSG("ADMINISTRATOR ���� ����");
							closesocket(Temp_List[i].Socket);
							memset(&Temp_List[i], NULL, sizeof(Temp));
							memcpy(&Temp_List[i], &Temp_List[i + 1], sizeof(Temp)*(HOST_SIZE - 1 - i));
							howmany_T--;
						}
						break;
					case CLIENT:
						flag = TRUE;

						for (j = 0; j < table.howmany; j++) {
							if (table.list[j]->ADDR_S <= Temp_List[i].IP_ADDR_INT && Temp_List[i].IP_ADDR_INT <= table.list[j]->ADDR_E) {
								//�߰�
								send_MY(Temp_List[i].Socket, table.list[j]->IP_ADDR, 30, SERVER, ADMINISTRATOR_ADDR, 0);
								flag = FALSE;
								//Show_MSG("CLIENT �߰� ����");
							}
						}

						if (flag) {
							Show_MSG("CLIENT ���� ����");
							Client_List[howmany_C].Socket = Temp_List[i].Socket;
							Client_List[howmany_C].IP_ADDR_INT = Temp_List[i].IP_ADDR_INT;
							Client_List[howmany_C].Time = time(NULL);
							memcpy(Client_List[howmany_C].IP_ADDR, Temp_List[i].IP_ADDR, 30);

							memset(&Temp_List[i], NULL, sizeof(Temp));
							memcpy(&Temp_List[i], &Temp_List[i + 1], sizeof(Temp)*(HOST_SIZE - 1 - i));							
							
							howmany_C++;
							howmany_T--;
						}
						break;
					}
				}
				else {
					Show_MSG("CLIENT ���� ����");
					closesocket(Temp_List[i].Socket);
					memset(&Temp_List[i], NULL, sizeof(Temp));
					memcpy(&Temp_List[i], &Temp_List[i + 1], sizeof(Temp)*(HOST_SIZE - 1 - i));
					howmany_T--;
				}
			}
		}

		for (i = 0; i < howmany_A; i++) {
			if (((Now - Administrator_List[i].Time) / 60)  > FREQUENT) {
				Show_MSG("ADMINISTRATOR �ֱ� �ʰ� ����");
				Table_Delete(&table, &Administrator_List[i]);
				closesocket(Administrator_List[i].Socket);
				memset(&Administrator_List[i], NULL, sizeof(State_A));
				memcpy(&Administrator_List[i], &Administrator_List[i + 1], sizeof(State_A) * (howmany_A - 1 - i));
				i--;
				howmany_A--;
				continue;
			}
			if (FD_ISSET(Administrator_List[i].Socket, &Socket_Arr)) {
				if (recv(Administrator_List[i].Socket, buf, 12, 0) > 0) {
					size = p[0];
					id = p[1];
					datatype = p[2];

					memset(buf, NULL, sizeof(buf));
					recv(Administrator_List[i].Socket, buf, size, 0);

					switch (datatype) {
					case ADMINISTRATOR_STATE:
						strcpy(Administrator_List[i].MAC_ADDR, MAC);
						Administrator_List[i].Time = time(NULL);

						send_MY(Administrator_List[j].Socket, " ", 3, SERVER, ADMINISTRATOR_ACK, 0);
						break;
					case ADMINISTRATOR_REQUEST_LIST:
						Show_MSG("ADMINISTRATOR �뿪 ��û �õ�");
						memset(tmp, NULL, sizeof(char) * 30);
						memcpy(tmp, buf, sizeof(char) * 30);
						IP1 = IP2INT(tmp);

						memset(tmp, NULL, sizeof(char) * 30);
						memcpy(tmp, buf+30, sizeof(char) * 30);
						IP2 = IP2INT(tmp);

						for (j = 0; j < howmany_C; j++) {
							if (IP1 <= Client_List[j].IP_ADDR_INT && Client_List[j].IP_ADDR_INT <= IP2) {
								//�߰�
								send_MY(Client_List[j].Socket, Administrator_List[i].IP_ADDR, 30, SERVER, ADMINISTRATOR_ADDR, 0);
								Show_MSG("ADMINISTRATOR �� CLIENT �߰� ����");
							}
						}

						send_MY(Administrator_List[i].Socket, "ACK", 4, SERVER, ADMINISTRATOR_ADDR, 0);

						Administrator_List[i].ADDR_S = IP1;
						Administrator_List[i].ADDR_E = IP2;
						Table_Add(&table, &Administrator_List[i]);
						break;
					}
				}
				else {
					Table_Delete(&table, &Administrator_List[i]);
					closesocket(Administrator_List[i].Socket);
					memset(&Administrator_List[i], NULL, sizeof(State_A));
					memcpy(&Administrator_List[i], &Administrator_List[i + 1], sizeof(State_A)*(howmany_A - 1 - i));
					howmany_A--;
				}
			}
		}

		for (i = 0; i < howmany_C; i++) {
			if (((Now - Client_List[i].Time) / 60)  > FREQUENT) {
				Show_MSG("CLIENT �ֱ� �ʰ� ����");
				closesocket(Client_List[i].Socket);
				memset(&Client_List[i], NULL, sizeof(State_C));
				memcpy(&Client_List[i], &Client_List[i + 1], sizeof(State_C) * (howmany_A - 1 - i));
				i--;
				howmany_C--;
				continue;
			}

			if (FD_ISSET(Client_List[i].Socket, &Socket_Arr)) {
				memset(buf, NULL, sizeof(buf));
				if (recv(Client_List[i].Socket, buf, 12, 0) > 0) {
					size = p[0];
					id = p[1];
					datatype = p[2];

					memset(buf, NULL, sizeof(buf));
					recv(Client_List[i].Socket, buf, size, 0);

					switch (datatype) {
					case CLIENT_STATE:
						strcpy(Client_List[i].MAC_ADDR, MAC);
						Client_List[i].Time = time(NULL);
						break;
					}
				}
				else {
					closesocket(Client_List[i].Socket);
					memset(&Client_List[i], NULL, sizeof(State_C));
					memcpy(&Client_List[i], &Client_List[i + 1], sizeof(State_C)*(howmany_C - 1 - i));
					howmany_C--;
				}
			}
		}
		
	}
}





///////////////////////////////////////

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Print_line() {
	int i, j, k, l;

	for (i = 0; i < 40; i++) {
		gotoxy(39, i);
		printf("��");
		gotoxy(80, i);
		printf("��");
	}
}

void Print_Administrator_List() {
	int i;
	int line = 2;
	for (i = 0; i < 39; i++) {
		gotoxy(0, i + 1);
		printf("                                  ");
	}

	for (i = 0; i < howmany_A;i++) {
		gotoxy(1, line++);
		printf("ADMINISTRATOR %d	", i + 1);
		gotoxy(1, line++);
		printf("  SOCKET_NUM -> %d", Administrator_List[i].Socket);
		gotoxy(1, line++);
		printf("  IP_ADDR -> %s", Administrator_List[i].IP_ADDR);
	}
}

void Print_Client_List() {
	int i;
	int line = 2;
	for (i = 0; i < 39; i++) {
		gotoxy(41, i + 1);
		printf("                              ");
	}

	for (i = 0; i < howmany_C ; i ++) {
		gotoxy(41, line++);
		printf("CLIENT %d	",i+1);
		gotoxy(41, line++);
		printf("  SOCKET_NUM -> %d", Client_List[i].Socket);	
		gotoxy(41, line++);
		printf("  IP_ADDR -> %s", Client_List[i].IP_ADDR);
	}
}

void Show_MSG(char * messege) {
	static int line = 1;
	int i;
	gotoxy(82, line);
	printf("%s\n", messege);
	line++;
	if (line == 39) {
		line = 1;
		for (i = 0; i < 39; i++) {
			gotoxy(81, i + 1);
			printf("                                ");
		}
	}
}
