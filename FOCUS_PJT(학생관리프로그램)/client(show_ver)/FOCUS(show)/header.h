#ifndef _HEADER_
#define _HEADER_
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib") //lib 파일 불러옴

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <process.h> //스레드
#include <windows.h>
#include <time.h>
#include <locale.h>

#define TRUE 1
#define FALSE 0
#define BUFSIZE 1024
#define FTP_BUFSIZE 50000
#define FTP_BUFSIZE2 524288
#define SERVER_PORT 5454
#define ADMIN_PORT 5455
#define FTP_PORT 5456
#define FREQUENT 1
#define SECOND 1000

//ID
#define SERVER 1
#define ADMINISTRATOR 2
#define CLIENT 3

//Data Type
#define ADMINISTRATOR_STATE 1
#define ADMINISTRATOR_LOGIN 2
#define CLIENT_STATE 3
#define ADMINISTRATOR_REQUEST_LIST 4
#define ADMINISTRATOR_ADDR 5

#define ACK 100
#define CLOSE 101
#define CLOSE_TIMER 201
#define SLEEP 102
#define SLEEP_TIMER 202
#define MESSAGE 103
#define WEB 104
#define INTBLOCK 105
#define FREE_INTBLOCK 205
#define FTP 106

#define ADMINISTRATOR_STATE_SIZE 72
#define CLIENT_STATE_SIZE 72
#define DATA_INFO 12

int SrvSockaddrSize;
int AdmSockaddrSize;
int FtpSockaddrSize;
int internetBlock; //인터넷 차단 스레드 실행여부
int sleepTimerThread; //절전모드 스레드 실행여부
int sleepOrderSecond; //절전모드 전환에 줄 딜레이 시간값(초)
int is_AdmAddrRecv;
int recvServThread;
int recvAdmThread;
char my_ADM_IP[30];
char buf[BUFSIZE];
char FTP_buf[FTP_BUFSIZE+4];
char TimeData[5];

extern int connectS;
extern int connectA;

typedef time_t TIME;

typedef struct {
	int hour;
	int minute;
} Date;

typedef struct S_State {
	char IP_ADDR[30];      //30
	char MAC_ADDR[30];      //30
	SOCKET Socket;         //4
	TIME Time;
} State;

State s, a;
SOCKADDR_IN sockaddr_in_S;					// 서버 소켓 정보 담을 구조체
SOCKADDR_IN sockaddr_in_A;					// 관리자 소켓 정보 담을 구조체
SOCKADDR_IN sockaddr_in_FTP;
WSADATA wsadata;
WSADATA FTP_wsadata;
SOCKET srvSocket;
SOCKET admSocket;
SOCKET ftpSocket;

int send_MY(SOCKET s, const char *data, const int size, const int id, const int data_type, int flags);
char *getMAC();

void init_sockaddr_in_SERVER();
void init_sockaddr_in_ADMINISTRATOR();
void init_sockaddr_in_FTP();
void init_sockState(int DataType);

void my_close();
void my_close_timer();
void my_sleep();
void my_sleep_timer();
void my_message(int recvSize);
void my_web(int recvSize);
void my_ftp(int recvSize);

HANDLE  hThread;  // 스레드를 하기위한 선언 그냥 일단은 외우셈
DWORD   dwThreadID; //스레드를 하기위한 선언
UINT WINAPI RecvServ_Thread(void *arg);
UINT WINAPI RecvAdmin_Thread(void *arg);
UINT WINAPI SleepTimer_Thread(void *arg);
UINT WINAPI InternetBlock_Thread(void *arg);

#endif