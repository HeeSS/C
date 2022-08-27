#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <Windows.h>
#include <string.h>

#define CONSOL_WIDTH 80
#define CONSOL_HEIGHT 24
#define EXT_KEY 0xffffffe0
#define LEFT 0x4b
#define RIGHT 0x4d
#define FILENAME "player.txt"

struct SHOE{
	char name[16];
	int max_spd;
	int power;
	int flexibility;
};

typedef struct Person{
	char name[20];
	int score;
};

struct SHOE shoedata[5];
struct Person Person_arr[10];
double player_speed=1;
float player_score=0;
float player_flexibility;
int player_wearability=99;
int player_shoenum;
int road_index,next_index;
int player_shoepos=5;	//플레이어 위치 초기값
int speed_counter=0;
int Person_count=0;
int crash=0;
int mancnt=0;
char player_name[20]={"NoName"};
char road[22][2]={3,17,3,17,3,17,3,17,3,17,3,17,3,17,3,17,3,17,3,17,3,17,3,17,3,17,3,17,3,17,3,17,3,17,3,17,3,17,3,17,3,17,3,17};
char shoe[4][5][13]={
	"oOOo    ",
	"(OO     ",
	"    oOOo",
	"     OO)",
	"",

	"     Ooo",
	"     (00",
	"ooO  0)",
	" 00)    ",
	" (0     ",

	"eeQ     ",
	"88)     ",
	"(8   Qee",
	"     (88",
	"      8)",

	"    △△",
	"    □00",
	"△△ 0□",
	"00□    ",
	"□0     "
};
char shoe2[4][5][13]={
	"    oOOo",
	"     OO)",
	" oOOo   ",
	"(OO    ",
	"",

	"ooO     ",
	"00)     ",
	"(0   Ooo",
	"     (00",
	"      0)",

	"     Qee",
	"     (88",
	"eeQ  8)",
	" 88)    ",
	" (8     ",

	"△△    ",
	"00□    ",
	"□0 △△ ",
	"    □00",
	"     0□"
};

int init();
int select_shoes();
int	show_shoe(int move);
int show_shoexy(int shoenum,int x,int y);
int show_gameframe();
int show_stat();
int show_road();
int show_count();
int show_gameover();
int gotoxy(int x,int y);
int strike_check();
int show_walkingman();
int frame();