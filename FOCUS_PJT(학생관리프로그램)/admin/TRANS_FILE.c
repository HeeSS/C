#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "header.h"
#include "Thread.h"

#pragma comment (lib, "ws2_32.lib")

#define FTP_BUFSIZE 1024
#define FTP_PORT 5456 //FTP ��Ʈ 5456���� ���� �ȰԿ�~! (from ��)
#define CLIENT_SIZE 256

extern int flag_ftp;
extern int flag_ftp1;
extern long FILE_SIZE;

typedef struct Clnt {
	SOCKET socket;
	int flag;
	long seek;
	long seek_tmp;
}Clnt;

Clnt FTPCLNT[CLIENT_SIZE];

WSADATA FTP_wsaData;
SOCKET ListenSocket;

int maxfd1;
int Client_num = 0;

SOCKADDR_IN SockAdr_in;
int SockAdr_in_size = sizeof(SOCKADDR_IN);

char FTP_buf[FTP_BUFSIZE + 4];

int getmax(int k) {
	int max = k;
	int r;
	for (r = 0; r < Client_num; r++) {
		if (FTPCLNT[r].socket > max) max = FTPCLNT[r].socket;
	}
	return max;
}

//��! ���α׷� ���� ������ ����� ��ġ�� �־�� �Ѵ�.

UINT WINAPI TRANS_FILE(void *arg) {
	int i, j, k;
	int count = 0;
	int delay_count = 0;
	unsigned int length;
	unsigned int length_recv;
	unsigned int *p;
	long end;
	unsigned int option_value = 1;
	fd_set read_fds;
	SOCKET MAX;

	FILE *FilePointer;
	struct timeval val;

	val.tv_sec = 0;
	val.tv_usec = 100;

	Client_num = 0;
	memset(FTPCLNT, NULL, sizeof(Clnt)*CLIENT_SIZE);

	FilePointer = fopen(filename, "rb"); //������ ������ �б� ���� fp

	if (FilePointer == NULL) {
		printf("FTP: FILE OPEN ERROR\n");
		flag_ftp = TRUE;
		flag_ftp1 = FALSE;
		return;
	}

	fseek(FilePointer, 0, SEEK_END);
	end = ftell(FilePointer);

	if (WSAStartup(MAKEWORD(2, 2), &FTP_wsaData) != 0) {
		printf("FTP: WSASTARTUP ERROR\n");
		fclose(FilePointer);
		flag_ftp = TRUE;
		return;
	}

	ListenSocket = socket(PF_INET, SOCK_STREAM, 0);

	setsockopt(ListenSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&option_value, sizeof(option_value));

	memset(&SockAdr_in, 0, sizeof(SockAdr_in));
	SockAdr_in.sin_family = AF_INET;
	SockAdr_in.sin_addr.s_addr = htonl(INADDR_ANY);
	SockAdr_in.sin_port = htons(FTP_PORT);

	if (bind(ListenSocket, (SOCKADDR*)&SockAdr_in, sizeof(SockAdr_in)) == SOCKET_ERROR) {
		printf("FTP: BIND ERROR\n");
		Sleep(3000);
		WSACleanup();
		return 0;
	}

	if (listen(ListenSocket, CLIENT_SIZE) == SOCKET_ERROR) {
		printf("FTP: LISTEN ERROR\n");
		Sleep(3000);
		WSACleanup();
		return 0;
	}

	

	flag_ftp1 = FALSE; // ���� ������ ����

	MAX = ListenSocket + 1;

	while (1) {
		FD_ZERO(&read_fds);

		FD_SET(ListenSocket, &read_fds);

		for (i = 0; i < Client_num; i++) {
			FD_SET(FTPCLNT[i].socket, &read_fds);
		}

		MAX = getmax(ListenSocket) + 1;

		if (select(MAX, &read_fds, 0, 0, &val) < 0) {
			printf("select error \n");
		}

		if (FD_ISSET(ListenSocket, &read_fds)) {
			FTPCLNT[Client_num].socket = accept(ListenSocket, (SOCKADDR*)&SockAdr_in, &SockAdr_in_size);

			if (FTPCLNT[Client_num].socket == INVALID_SOCKET) {
				printf("FTP: ACCEPT ERROR\n");
				closesocket(FTPCLNT[Client_num].socket);
				closesocket(ListenSocket);
			}

			//accept�� �����̸�

			FTPCLNT[Client_num].flag = TRUE;
			FTPCLNT[Client_num].seek = 0;
			FTPCLNT[Client_num].seek_tmp = 0;
			Client_num++;
			continue;
		}

		for (j = 0; j < Client_num; j++) {
			if (FTPCLNT[j].flag == FALSE) {
				count++;
				// ���� ����
				if (count == Client_num) {
					length = 0;
					if (send(FTPCLNT[j].socket, &length, 4, 0) == SOCKET_ERROR) {
						printf("FTP: FILE SEND ERROR\n");
						FTPCLNT[j].flag = FALSE;
						break;
					} // Ŭ���̾�Ʈ ���ú� ���ѷ��� ����

					
					for (k = 0; k < Client_num; k++) {
						closesocket(FTPCLNT[k].socket);
					}
					closesocket(ListenSocket);
					_fcloseall();
					WSACleanup();
					printf("FTP:FILE SEND COMPLETE\n");
					flag_ftp = TRUE;
					return 0;
				}
				continue;
			}
			if (FTPCLNT[j].flag) {
				memset(FTP_buf, NULL, sizeof(FTP_buf));

				fseek(FilePointer, FTPCLNT[j].seek, SEEK_SET);
				fread(FTP_buf + 4, sizeof(char), FTP_BUFSIZE, FilePointer);

				FTPCLNT[j].seek_tmp = FTPCLNT[j].seek;
				FTPCLNT[j].seek = ftell(FilePointer);

				length = FTPCLNT[j].seek - FTPCLNT[j].seek_tmp;

//				memcpy(FTP_buf, &length, sizeof(int));
				p = (unsigned int *)FTP_buf;
				*p = length;
				if (send(FTPCLNT[j].socket, FTP_buf, FTP_BUFSIZE + 4, 0) == SOCKET_ERROR) {
					printf("FTP: FILE SEND ERROR\n");
					closesocket(FTPCLNT[Client_num].socket);
					FTPCLNT[j].flag = FALSE;
					break;
				}
				
				if (feof(FilePointer)) {

					FTPCLNT[j].flag = FALSE;
				}
			}
			delay_count = 0;
		}

		if (delay_count > 10000) {
			_fcloseall();
			flag_ftp = TRUE;
			for (k = 0; k < Client_num; k++) {
				closesocket(FTPCLNT[k].socket);
			}
			closesocket(ListenSocket);
			WSACleanup();
			return 0;
		}
		delay_count++;
		count = 0;
	}

	flag_ftp = TRUE;
	closesocket(ListenSocket);
	WSACleanup();
	return 0;
}