#ifndef _THREAD_
#define _THREAD_

#include "header.h"
//#include <process.h> //스레드
//#include <windows.h> //스레드

#define ACK_			100
#define SHUTDOWN		101
#define SHUTDOWN_T		201
#define SLEEP_MODE		102
#define SLEEP_MODE_T	202
#define SEND_MESSAGE	103
#define RUN_WEBBROWSER	104
#define BLOCK_INTERNET	105
#define FILE_TRANSE		106
#define FREE_INTBLOCK   205
#define FTP				106

UINT WINAPI SendCommand_Thread(void *arg);	// 명령 보내기 스레드
UINT WINAPI ManageList(void *arg);	//  상태정보 송신 (관리자->서버)
UINT WINAPI ARP(void *arg);
UINT WINAPI TRANS_FILE(void *arg); // FTP 만들기.

char filename[1024]; //(스레드를 호출하기 전 관리자가 알려줘야하는 파일의이름과 확장명은 "test2.png")
char snedMessage[100000];
char first;
char reset;


void ShutDown(char time[], int n, int select[], int flag);
void SleepMode(char time[], int n, int select[], int flag);
void MessageSend(int n, int select[]);
void RunWebBrowser(int n, int select[]);
void BlockInternet(int n, int select[], int flag);	// 인터넷 차단
void FileTranse(int n, int select[]);		// 파일 전송

#endif
