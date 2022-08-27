#ifndef _UI_H_
#define _UI_H_
#pragma warning(disable:4996)
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#define BLACK 0
#define BLUE1 1
#define GREEN1 2
#define CYAN1 3
#define RED1 4
#define MAGENTA1 5
#define YELLOW1 6
#define GRAY1 7
#define GRAY2 8
#define BLUE2 9
#define GREEN2 10
#define CYAN2 11
#define RED2 12
#define MAGENTA2 13
#define YELLOW2 14
#define WHITE 15

#define ESC 0x1b //  ESC 누르면 종료
#define SPACE	0x20
#define ENTER	0x0D
#define TAB 0x09
#define BACKSPACE 0x08

#define SPECIAL1 0xe0 // 특수키는 0xe0 + key 값으로 구성된다.
#define SPECIAL2 0x00 // keypad 경우 0x00 + key 로 구성된다.

#define UP		0x48 // Up key는 0xe0 + 0x48 두개의 값이 들어온다.
#define DOWN	0x50
#define LEFT	0x4b
#define RIGHT	0x4d

#define ACK_			100
#define SHUTDOWN		101
#define SHUTDOWN_T		201
#define SLEEP_MODE		102
#define SLEEP_MODE_T	202
#define SEND_MESSAGE	103
#define RUN_WEBBROWSER	104
#define BLOCK_INTERNET	105
#define FILE_TRANSE		106

#define LINE 17

#define SET_ROOM 0
#define SET_IP 99

#define VER "3.14"
int sel_clt_cnt;
char send_time[5];
char send_web[128];
char login_error_window;

time_t time_now;
struct tm *timeinfo;

void removeCursor(void);
void gotoxy(int x, int y);
void putstar(int x, int y, char ch);
void erasestar(int x, int y);
void textcolor(int fg_color, int bg_color);
void cls(int bg_color, int text_color);

void CommandBox(int x, int y);
void ShowLogin(int y, char* ver);
void ShowFOCUS(int x, int y, char* ver);
int ShowMainScr(int x, int y, int select[]);
int ShowRangeSetBox(int x, int y);
void ShowArrow(int x, int y, int arrow);
void WipeArrow(int x, int y, int arrow);
int ShowCommandMenu(int x, int y, int arrow);
int ShowCommandBox(int x, int y);
void ShowCltInfo(int x, int y, int clt);
int ShutDownBox(int x, int y);
void debug(int a, int b, int c, int d);
int ConfirmBox(int x, int y, int time);
int RunWebBrowserBox(int x, int y);
void ShowAdminInfo(int x, int y);
void ShowServerInfo(int x, int y);
char* InputTime(int x, int y, int flag);
void PresentTime();
void SendComplete(int x, int y);
void ShowWatingClient();
void AnyClient(int x, int y);
void ClrBox();
void ScrollCursor(int x, int y, int arrow);
#endif _UI_H_ 