#include "header.h"

void init_sockaddr_in_SERVER() {
	memset((char*)&sockaddr_in_S, 0, sizeof(sockaddr_in_S));
	sockaddr_in_S.sin_family = AF_INET;
	//sockaddr_in_S.sin_addr.S_un.S_addr = inet_addr("113.198.81.82");
	sockaddr_in_S.sin_addr.S_un.S_addr = inet_addr("180.67.11.157");
	sockaddr_in_S.sin_port = htons(SERVER_PORT);
	SrvSockaddrSize = sizeof(sockaddr_in_S);
}
void init_sockaddr_in_ADMINISTRATOR() {
	//지금은 버퍼에 관리자의 아이피 주소가 "000.000.000.000"로 들어가 있는 상태
	memset(my_ADM_IP, NULL, sizeof(my_ADM_IP));
	memcpy(my_ADM_IP, buf, sizeof(my_ADM_IP));

	memset((char*)&sockaddr_in_A, 0, sizeof(sockaddr_in_A));
	sockaddr_in_A.sin_family = AF_INET;
	sockaddr_in_A.sin_addr.S_un.S_addr = inet_addr(my_ADM_IP);
	//sockaddr_in_A.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	sockaddr_in_A.sin_port = htons(ADMIN_PORT);
	AdmSockaddrSize = sizeof(sockaddr_in_A);
}
void init_sockaddr_in_FTP() {
	memset(&sockaddr_in_FTP, 0, sizeof(sockaddr_in_FTP));
	sockaddr_in_FTP.sin_family = AF_INET;
	sockaddr_in_FTP.sin_addr.s_addr = inet_addr(my_ADM_IP);
	sockaddr_in_FTP.sin_port = htons(FTP_PORT);
	FtpSockaddrSize = sizeof(sockaddr_in_FTP);
}