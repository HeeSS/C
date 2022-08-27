#ifndef _THREAD_
#define _THREAD_

#include "header.h"
//#include <process.h> //������
//#include <windows.h> //������

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

UINT WINAPI SendCommand_Thread(void *arg);	// ��� ������ ������
UINT WINAPI ManageList(void *arg);	//  �������� �۽� (������->����)
UINT WINAPI ARP(void *arg);
UINT WINAPI TRANS_FILE(void *arg); // FTP �����.

char filename[1024]; //(�����带 ȣ���ϱ� �� �����ڰ� �˷�����ϴ� �������̸��� Ȯ����� "test2.png")
char snedMessage[100000];
char first;
char reset;


void ShutDown(char time[], int n, int select[], int flag);
void SleepMode(char time[], int n, int select[], int flag);
void MessageSend(int n, int select[]);
void RunWebBrowser(int n, int select[]);
void BlockInternet(int n, int select[], int flag);	// ���ͳ� ����
void FileTranse(int n, int select[]);		// ���� ����

#endif
