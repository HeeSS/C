#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#ifndef _HEADER_
#define _HEADER_

#pragma comment(lib,"ws2_32.lib") //lib 파일 불러옴
#pragma comment(lib, "iphlpapi.lib" )
#include <winsock2.h>
#include <IPHlpApi.h> 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <windows.h> //스레드
#include <process.h> //스레드

#include <signal.h> // 스트림 관련 file디스크립터
#include <time.h>

//#include "pcap.h"

#define TRUE 1
#define FALSE 0
#define BUFSIZE 1024
#define CLIENT_SIZE 256
#define ADMINISTRATOR_SIZE 10
#define HOST_SIZE 266

#define SERVER_IP "127.0.0.1"
#define PORT 5454

//ID
#define SERVER 1
#define ADMINISTRATOR 2
#define CLIENT 3

//Data Type
#define ADMINISTRATOR_STATE 1
#define ADMINISTRATOR_LOGIN 2
#define CLIENT_STATE 3
#define ADMINISTRATOR_REQUEST_LIST 4
//#define ADMINISTRATOR_ADDR 5

#define ADMINISTRATOR_STATE_SIZE 72
#define CLIENT_STATE_SIZE 72
#define DATA_INFO sizeof(int)*3 // 12

#define ID_LENGTH 16

#define FREQUENT 1000
WSADATA wsadata;

SOCKADDR_IN sockaddr_in;
int sockaddr_size;

SOCKET Main_Socket;
SOCKET Server_Socket; // 보류

SOCKET Max_Socket;

HANDLE  hThread;
DWORD   dwThreadID;

fd_set  Socket_Arr;

typedef time_t TIME;

typedef struct S_State {
	char IP_ADDR[30];      //30
	char MAC_ADDR[30];      //30
	SOCKET Socket;         //4
	TIME Time;
} State;

State Client_List[CLIENT_SIZE];		// 현재 제어 중인 클라이언트 리스트

State s;

typedef struct arp {
	SOCKET Socket;
	struct eth_h {
		unsigned char Dest_H_Addr[6];
		unsigned char Send_H_Addr[6];
		unsigned short TYPE;
	}ethh;
	struct arp_h {
		unsigned short Hardware_Type;
		unsigned short Protocol_Type;
		unsigned char Hardware_Addr_Length;
		unsigned char Protocol_Length;
		unsigned short Operation;
		unsigned char Sender_H_Addr[6];
		unsigned char Sender_IP_Addr[4];
		unsigned char Target_H_Addr[6];
		unsigned char Target_IP_Addr[4];
	}arph;
}arp_t;

typedef struct arp_list {
	arp_t *list;
	int size;
	int howmany;
}ARP_List;

extern int howmany_T;   // ??
extern int howmany_C;   // 관리 중인 클라이언트 수
extern int login; // 로그인 재시도
extern int bootThread;
char adminID[16];
int send_MY(SOCKET s, const char *data, const int size, const int id, const int data_type, int flags);
int LoginReq(SOCKET Socket, char *ID_SHA, char *PWD_SHA);
int LoginTry();
char *getMAC();



#endif

