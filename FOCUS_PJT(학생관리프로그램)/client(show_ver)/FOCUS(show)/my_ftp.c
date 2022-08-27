#include "header.h"
//지금은 받은 data("파일이름.확장자")가 buf에 저장되어 있는 상태

void my_ftp(int recvSize) {
	FILE *fp;
	char *filename;
	char *recvstr;
	char filepath[] = "c:\\FOCUS 받은 파일\\";
	int recvERROR = 941124;
	int *p;
	unsigned int length;
	long *lp;
	long fileSize;
	int flag = FALSE;
	int ref = 0;
	struct timeval val;

	val.tv_sec = 5;
	val.tv_usec = 0;
	
	printf("파일 수신\n");
	system("if not exist \"c:\\FOCUS 받은 파일\" MD \"c:\\FOCUS 받은 파일\"");

	//"파일이름.확장자" --> recvstr
	recvstr = (char*)malloc(sizeof(char) * recvSize);
	memset(recvstr, NULL, sizeof(recvstr));
	memcpy(recvstr, buf, recvSize);

	//fp가 쓸 파일 위치와 이름과 확장명 -->filename
	filename = (char*)malloc(sizeof(char) * sizeof(filepath) * recvSize);
	memset(filename, NULL, sizeof(filename));
	memcpy(filename, filepath, sizeof(filepath));
	strcat(filename, recvstr);

	//FTP 시작
	fopen_s(&fp, filename, "wb"); //수신한 파일을 쓰기 위한 fp
	if (fp == NULL) {
		printf("FTP: FILE OPEN ERROR\n");
		free(recvstr);
		free(filename);
		return;
	}

	//FTP용 소켓 생성 & 연결
	if (WSAStartup(MAKEWORD(2, 2), &FTP_wsadata) != 0) {
		printf("FTP: WSASTARTUP ERROR\n");
		free(recvstr);
		free(filename);
		fclose(fp);
		return;
	}

	ftpSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (ftpSocket == INVALID_SOCKET) {
		printf("FTP: SOCKET OPEN ERROR\n");
		free(recvstr);
		free(filename);
		fclose(fp);
		return;
	}

	setsockopt(ftpSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&val, sizeof(val));

	init_sockaddr_in_FTP();

	if (connect(ftpSocket, (SOCKADDR*)&sockaddr_in_FTP, FtpSockaddrSize) == SOCKET_ERROR) {
		printf("FTP: CONNECTION ERROR\n");
		free(recvstr);
		free(filename);
		fclose(fp);
		closesocket(ftpSocket);
		return;
	}

	printf("FTP: START DATA WRITING..\n");
	printf("FTP: FILE RECV WAITING..\n");

	//파일 수신 & 쓰기 루프
	while (1) {
		memset(FTP_buf, NULL, FTP_BUFSIZE);
		if (recvERROR = recv(ftpSocket, FTP_buf, sizeof(int)+ FTP_BUFSIZE, 0)<0) {
			printf("FTP: RECEIVE ERROR\n");

			free(recvstr);
			free(filename);
			fclose(fp);
			closesocket(ftpSocket);
			WSACleanup();
			return;
		}
		p = (int *)FTP_buf;
		length = *p;	

		flag = TRUE;

		printf("FTP: FILE RECEIVE..\n");
		printf("%d\n", length);		
		
		fwrite(FTP_buf+4, sizeof(char), length, fp);	
		Sleep(180);

		if (flag && length < FTP_BUFSIZE) {
			break;
		}
	}

	free(recvstr);
	free(filename);
	fclose(fp);
	closesocket(ftpSocket);
	WSACleanup();
	return;
}