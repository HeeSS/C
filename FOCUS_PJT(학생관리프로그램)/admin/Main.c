#include "header.h"

char message[BUFSIZE];
WSADATA wsadata;

SOCKADDR_IN sockaddr_in;
int sockaddr_size;

SOCKET Main_Socket;

State Client_List[CLIENT_SIZE];

SOCKET Max_Socket;


HANDLE  hThread;  // �����带 �ϱ����� ���� �׳� �ϴ��� �ܿ��
DWORD   dwThreadID; //�����带 �ϱ����� ����

UINT WINAPI ThreadFunction(void *arg);

fd_set  Socket_Arr;

int howmany_C = 0;

State s;

int send_MY(SOCKET s, const char *data, const int size, const int id, int flags);

void main() {
	int i;
	unsigned int option_value = 1;
	char ch,ID[16],id[64], pwd[64];
	int flag = 2;

	scanf("%s",ID);
	SHA256_Encrpyt(ID, 16, id);
	memset(ID, NULL, 16);
	scanf("%s", ID);
	SHA256_Encrpyt(ID, 16, pwd);

	srand(time(NULL));

	WSAStartup(MAKEWORD(2, 0), &wsadata);

	Main_Socket = socket(PF_INET, SOCK_STREAM, 0);
	//�������� ü��,��Ʈ���� ���� �ŷڼ� ���������, ��������(�⺻0���� ��������)
	//INVALID_SOCKET�� ���� ���� ���и� ���ϰ� -1�� ���ǵǾ��ִ�.

	if (Main_Socket == INVALID_SOCKET) {
		printf("#error here 1\n");
		exit(0);
	}

	setsockopt(Main_Socket, SOL_SOCKET, SO_REUSEADDR, (char *)&option_value, sizeof(option_value));
	//int setsockopt( SOCKET s,int level,int optname,const char FAR* optval,int optlen);
	//SO_REUSEADDR �ɼ��� �����ϸ� Ŀ���� ������ ��Ʈ�� ���� ���� ���¿����� bind �Լ� ȣ���� ���� ->������ ��Ʈ�� ������ �ش� ��Ʈ�� bind�� ����

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	memset((char *)&sockaddr_in, 0, sizeof(sockaddr_in));
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	sockaddr_in.sin_port = htons(PORT);

	Sleep(1000 * 4);
	i = connect(Main_Socket, (SOCKADDR*)&sockaddr_in, sizeof(sockaddr_in));
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	strcpy(s.IP_ADDR, "127.0.0.1");
	strcpy(s.MAC_ADDR, "127.0.0.1");

	if (Login(Main_Socket, id, pwd)) {

		while (1) {
			if (send_MY(Main_Socket, (char *)&s, sizeof(s), ADMINISTRATOR,ADMINISTRATOR_STATE, 0) == -1) {
				closesocket(Main_Socket);
				Main_Socket = socket(PF_INET, SOCK_STREAM, 0);
				i = connect(Main_Socket, (SOCKADDR*)&sockaddr_in, sizeof(sockaddr_in));
				send_MY(Main_Socket, id, strlen(id), ADMINISTRATOR, ADMINISTRATOR_STATE, 0);
			}
			else {
				printf("����\n");
				Sleep(rand() % 800);
			}
		}
	}
	else {
		printf("LOGIN FAIL PLS RETRY\n");
		getch();
		exit(1);
	}
}