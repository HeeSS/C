#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <Windows.h>



//*******************
// 상수 선언
//*******************
#define CONSOL_WIDTH	80
#define CONSOL_HEIGHT	24
#define EXT_KEY			0xffffffe0	//확장키 인식값 
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
//*******************
// 구조체 선언
//*******************
struct CAR{
	char name[16];
	int max_spd;
	int energy;
	int accel;
};
//*******************
//전역 변수 선언
//*******************
char player_name[20]={"NoName"};
float player_score=0;
int player_energy=99;
double player_speed=1;
int player_carnum=9;		//루프진입을 위하여 초기값을 지정함
float player_accel;
struct CAR cardata[5];
int road_index,next_index;
int player_carpos=20;				//현재 자동차의 위치
char video_buf[CONSOL_HEIGHT][CONSOL_WIDTH+1];		//프로그램에서는 이 배열에 변경할 화면을 갱신한다.
int speed_counter=0;		//부딧히지 않고 진행하는지 체크하기위함

static char road[22][2]={15,30,15,30,15,30,15,30,15,30,15,30,15,30,15,30,15,30,15,30,15,30,15,30,
15,30,15,30,15,30,15,30,15,30,15,30,15,30,15,30,15,30,15,30};	//road[?][0]이 left,  road[?][1]이 right

char car[5][5][9]={".-TTTT-.",
                   "0-++++-0",
				   "  I▦I  ",
				   "[]+--+[]",
				   "  Y--Y  ",

				   "._|__|_.",
				   "()┫┣()",
				   "  IⅩI  ",
				   "(||)(||)",
				   "  ^  ^  ",

				   "  ┳┳  ",
				   "[]╋╋[]",
				   "  [Ξ]  ",
				   "◐::::◑",
				   "  ∇∇  ",

				   "┏━━┓",
				   "◁    ▷",
				   "◁ ◎ ▷",
				   "◀    ▶",
				   "┗∩∩┛",

				   " ∞┯∞ ",
				   "▥←→▥",
				   "  [★]  ",
				   "▥§§▥",
				   "  ↙↘  ",};

//*********************
//함수 proto type 선언
//*********************
int init();
int video_refresh();
int show_logo();
int	show_car(int move);		//게임중 화면에 자동차를 표시한다. -1은 왼쪽으로 1은 오른쪽으로
int show_carxy(int carnum,int x,int y);
int show_gameframe();	//게임화면의 외곽선을 그린다.
int show_stat();	//게임화면의 점수와 속도와 에너지를 갱신할때 사용
int show_road();
int show_count();
int show_gameover();
int gotoxy(int x,int y);
int input_player_data();
int strike_check();		//자동차와 도로와 충돌했는지 검사하고 충돌시 충돌부분을 화면에 출력



int main(int argc, char* argv[])
{
	
	double delay;
	int frame=0;
	int i;
	
	char key_temp;
	

	init();
	show_logo();
	input_player_data();
	system("cls");
	
	player_energy = cardata[player_carnum].energy;
	show_gameframe();
	show_stat();
	show_count();

	player_accel = (float) cardata[player_carnum].accel/10;
	for(i=0;i<=200000;i++)	//게임시작
	{
		if(kbhit())
		{
			
			key_temp = getche();

			if(key_temp == EXT_KEY)
			{
				key_temp = getche();
				
				gotoxy(0,24);
				putchar(' ');
				switch(key_temp)
				{
				case KEY_LEFT:
					show_car(-1);
					player_speed -=1;
					strike_check();
					break;
				case KEY_RIGHT:
					show_car(1);
					player_speed -=1;
					strike_check();
					break;
				}
			}
			strike_check();
		}
		
		if(player_speed < 100)
			player_speed += 2.7;
		if(speed_counter > 6)
		{
			if(player_speed < 100)
			{
				player_speed = player_speed + (7.6 * player_accel);
			}else if(player_speed < 200)
			{
				player_speed = player_speed + (1.2 * player_accel );
			}else if(player_speed < 300)
			{
				player_speed = player_speed + ( 0.3 * player_accel );
			}else if(player_speed < 315)
			{
				player_speed = player_speed + ( 0.1 * player_accel );
			}else
			{
				player_speed = player_speed + ( 0.06 * player_accel );
			}
			if(player_speed>cardata[player_carnum].max_spd)
				player_speed = cardata[player_carnum].max_spd;
		}
		

		delay = 350 - (351 * (1-exp(-player_speed/70)));
		if(delay<0)
			delay=0.01;
		
		

		if(i%5==0)
		{
			player_score = (float)((player_score + player_speed/50)* 1.0003);
			show_stat();
			
			show_car(0);
			show_road();
			strike_check();
			speed_counter++;
		}
		show_stat();
		if(player_energy <=0)
		{
			show_gameover();
			fflush(stdin);
			scanf("%d",&i);
			break;
		}
		gotoxy(10,24);
		printf("delay: %10.2f",(float)delay);
		gotoxy(0,24);
		Sleep((unsigned int)delay);
		
	}
	
	gotoxy(2,2);	//테스트용
	return 0;
}
int show_logo()
{
	int i;
	int logo_delay=5;
	system("cls");
	gotoxy(4,2);
	for(i=4;i<76;i++)
	{
		printf("*");
		Sleep(logo_delay);
	}
	for(i=3;i<8;i++)
	{
		gotoxy(75,i);printf("*");
		Sleep(logo_delay);
	}

	for(i=75;i>=4;i--)
	{
		gotoxy(i,7);
		printf("*");
		Sleep(logo_delay);
	}

	for(i=7;i>=3;i--)
	{
		gotoxy(4,i);printf("*");
		Sleep(logo_delay);
	}

	Sleep(80);
	gotoxy(32,4);
	printf("☆  Simple Race  ☆");
	Sleep(80);
	gotoxy(8,6);
	printf("Ver 0.1");
	Sleep(80);
	gotoxy(56,6);
	printf("Made By Jae-Dong");


	show_carxy(0,13,15);
	Sleep(200);
	show_carxy(1,27,15);
	Sleep(200);
	show_carxy(2,41,15);
	Sleep(200);
	show_carxy(3,55,15);
	
	Sleep(1000);
	gotoxy(28,21);
	printf("Please Press Any Key!");
	getchar();
	return 0;
}

int show_gameframe()
{
	int i;
	gotoxy(0,0);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━┓");
	for(i=1;i<CONSOL_HEIGHT-1;i++)
	{
		gotoxy(0,i);
		printf("┃");
		gotoxy(56,i);
		printf("┃");
		gotoxy(78,i);
		printf("┃");
	}
	gotoxy(0,CONSOL_HEIGHT-1);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━┛");
	gotoxy(58,1);
	printf("    Simple Racing");
	gotoxy(58,2);
	printf("       Ver 0.1");
	gotoxy(58,3);
	printf("━━━━━━━━━━");
	gotoxy(58,4);
	printf(" Name:");
	gotoxy(58,5);
	printf(" %17s",player_name);
	gotoxy(58,6);
	printf("━━━━━━━━━━");
	gotoxy(58,7);
	printf(" Score:");
	gotoxy(58,9);
	printf("━━━━━━━━━━");
	gotoxy(58,10);
	printf(" Energy:");
	gotoxy(58,12);
	printf("━━━━━━━━━━");
	gotoxy(58,13);
	printf(" Speed:");
	gotoxy(58,14);
	printf("              km/h  ");
	gotoxy(58,15);
	printf(" RPM:");
	gotoxy(58,17);
	printf("━━━━━━━━━━");

	gotoxy(61,18);
	printf("--Car Info--");
	gotoxy(59,19);
	printf("Model  :%s",cardata[player_carnum].name);
	gotoxy(59,20);
	printf("Max Spd: %d Km/h",cardata[player_carnum].max_spd);
	gotoxy(59,21);
	printf("Energy :  %d",cardata[player_carnum].energy);
	gotoxy(59,22);
	printf("Accel  :   %d",cardata[player_carnum].accel);

	return 0;
}

int show_stat()
{
	int i,j;
	static int recent_energy = 999,recent_rpm = 999,recent_speed = 999;
	//score
	gotoxy(58,8);
	printf("%19.0f",player_score);
	gotoxy(58,11);
	if(recent_energy !=player_energy)		//값에 변화가 있을때만 화면에 갱신
	{
		for(i=0,j=player_energy;i<10;i++)
		{
			if(j>=10)
				printf("■");
			else
				printf("□");
			j-=10;
		}
	}
	if(recent_speed != player_speed)
	{
		gotoxy(58,14);
		printf("%12.0f",player_speed);
	}

	//RPM
	gotoxy(58,16);
	j= (int) ((player_speed * 10) / cardata[player_carnum].max_spd );
	if(j != recent_rpm)	//값에 변화가 있을때만 화면에 갱신
	{		
		for(i=0;i<10;i++)
		{
			if(j>i)
				printf("■");
			else
				printf("□");
		}
	}
	recent_rpm = j;
	recent_energy = player_energy;
	return 0;
}
int init()
{
	int i,j;
	

	road_index = 0;
	next_index = 0;

	for(i=0;i<CONSOL_HEIGHT;i++)
		for(j=0;j<CONSOL_WIDTH;j++)
			video_buf[i][j]=32;
		
		video_refresh();
	for(i=0;i<CONSOL_HEIGHT-1;i++)	//화면출력 마지막 칸에 new line코드 삽입
		video_buf[i][CONSOL_WIDTH]=(char)0x0d;
	video_buf[i][CONSOL_WIDTH]=NULL;

	//자동차 데이터 입력
	sprintf(cardata[0].name,"Laser");
	cardata[0].max_spd=350;
	cardata[0].energy=70;
	cardata[0].accel=7;

	sprintf(cardata[1].name,"Fire");
	cardata[1].max_spd=320;
	cardata[1].energy=90;
	cardata[1].accel=8;

	sprintf(cardata[2].name,"Shot Gun");
	cardata[2].max_spd=290;
	cardata[2].energy=70;
	cardata[2].accel=9;

	sprintf(cardata[3].name,"Monster");
	cardata[3].max_spd=295;
	cardata[3].energy=40;
	cardata[3].accel=6;

	sprintf(cardata[4].name,"K-Machine");
	cardata[4].max_spd=320;
	cardata[4].energy=100;
	cardata[4].accel=10;

	//랜덤 seed값 초기화
	srand((unsigned)time(NULL));

	return 0;
	
}
int video_refresh()
{
	system("cls");
	printf("%s",video_buf[0]);
	return 0;
}

int gotoxy(int x,int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD pos; 
	pos.Y=y;
	pos.X=x;
	SetConsoleCursorPosition(hConsole, pos); 
	return 0;
}

int show_carxy(int carnum,int x,int y)
{
	static i;
	i=y;
	for(;i<=y+4;i++)
	{	
		gotoxy(x-1,i);
		printf(" %8s ",car[carnum][i-y]);
	}
	return 0;
}

int input_player_data()
{
	int i,j,k;
	fflush(stdin);
	system("cls");
	gotoxy(3,3);
	printf("Name? :");
	gotoxy(3,7);
	printf("Select Your Car. [1-4]:");
	show_carxy(0,15,10);
	show_carxy(1,33,10);
	show_carxy(2,51,10);
	show_carxy(3,69,10);

	gotoxy(12,9);
	printf("    [ 1 ]             [ 2 ]             [ 3 ]             [ 4 ] ");

	gotoxy(2,16);
	printf("Model Name:");

	gotoxy(2,18);
	printf("MAX Speed :");

	gotoxy(2,20);
	printf("Energy    :");

	gotoxy(2,22);
	printf("Accelation:");
	
	for(i=16,j=0;j<4;i+=18,j++)
	{
		gotoxy(i,16);
		printf("%s",cardata[j].name);
	}

	for(i=16,j=0;j<4;i+=18,j++)
	{
		gotoxy(i,18);
		printf("%d Km/h",cardata[j].max_spd);
	}

	for(i=16,j=0;j<4;i+=18,j++)
	{
		gotoxy(i,20);
		for(k=cardata[j].energy/10;k>0;k--)
			printf("*");
	}

	for(i=16,j=0;j<4;i+=18,j++)
	{
		gotoxy(i,22);
		for(k=cardata[j].accel
			;k>0;k--)
			printf("*");
	}

	gotoxy(11,3);
	scanf("%s",player_name);
	while( (player_carnum < 0) || (player_carnum > 4))
	{
		gotoxy(27,7);
		scanf("%d",&player_carnum);
		player_carnum--;
	}
	return 0;
}

int show_road()
{
	int i,j;
	int rand_num;
	
	static int road_left=15,road_right=32;
	
	//화면 밑의 줄의 도로 표시는 무조건 지움
	gotoxy(road[(road_index+1)%22][0],1);
	printf(" ");
	gotoxy(road[(road_index+1)%22][1],1);
	printf(" ");

	for(j=2,i=road_index+1;j<23;i++,j++)
	{
		i =i%22;
		if(road[(i+1)%22][0] != road[i][0]) 	//윗줄과 아랫줄의 도로의 위치가 같을때는 화면에 도로를 지우지 않음
		{
			gotoxy(road[(i+1)%22][0],j);
			printf(" ");
			gotoxy(road[(i+1)%22][1],j);
			printf(" ");
		}
		
	}
	
	//랜덤으로 도로 생성 0:왼쪽두칸 1,2:왼쪽한칸 3,4,5,6:직진 7,8:오른쪽한칸 9:오른쪽두칸
	//rand_num=rand()%10;
	rand_num=rand()%8;
	rand_num++;
	switch(rand_num)
	{
	case 0:
		if(road[(road_index+1)%22][0] <=4 )
		{
			road[next_index][0] = road[(road_index+1)%22][0];
			road[next_index][1] = road[(road_index+1)%22][1];
			break;
		}
		road[next_index][0] =road[(road_index+1)%22][0]-2;
		road[next_index][1] =road[(road_index+1)%22][1]-2;
		break;
	case 1:
	case 2:
		if(road[(road_index+1)%22][0] <=3 )
		{
			road[next_index][0] = road[(road_index+1)%22][0];
			road[next_index][1] = road[(road_index+1)%22][1];
			break;
		}
		road[next_index][0] =road[(road_index+1)%22][0]-1;
		road[next_index][1] =road[(road_index+1)%22][1]-1;
		break;
	case 7:
	case 8:
		if(road[(road_index+1)%22][1] >=55 )
		{
			road[next_index][0] = road[(road_index+1)%22][0];
			road[next_index][1] = road[(road_index+1)%22][1];
			break;
		}
		road[next_index][0] =road[(road_index+1)%22][0]+1;
		road[next_index][1] =road[(road_index+1)%22][1]+1;
		break;
	case 9:
		if(road[(road_index+1)%22][1] >=54 )
		{
			road[next_index][0] = road[(road_index+1)%22][0];
			road[next_index][1] = road[(road_index+1)%22][1];
			break;
		}
		road[next_index][0] =road[(road_index+1)%22][0]+2;
		road[next_index][1] =road[(road_index+1)%22][1]+2;
		break;
	default:
		road[next_index][0] = road[(road_index+1)%22][0];
		road[next_index][1] = road[(road_index+1)%22][1];
		break;
		
	}
	road_index=next_index;
	
	
	if( road_index == 0)
		next_index = 21;
	else
		next_index = road_index-1;
	
	
	
	
	
	for(j=1,i=road_index;j<23;i++,j++)
	{
		i = i%22;
		gotoxy(road[i][0],j);
		printf("[");
		gotoxy(road[i][1],j);
		printf("]");
	}
	road_index=next_index;
	

	return 0;
}

int	show_car(int move)
{
	player_carpos = player_carpos + move;

	//자동차가 화면 밖으로 삐져나가지 못하게 좌표 수정
	if( player_carpos <2)
		player_carpos = 2;
	if( player_carpos >48)
		player_carpos = 48;

	show_carxy(player_carnum,player_carpos,18);
	return 0;
}

int strike_check()	//자동차와 도로와 충돌했는지 검사하고 충돌시 충돌부분을 화면에 출력
{
	int i;
	for(i=18;i<=19;i++)
	{
		if( road[road_index][0]>=player_carpos)
		{
			show_car(1);
			player_carpos++;
			
			player_speed -= 7+(player_speed/50);
			if(player_speed <0)
				player_speed = 0;

			player_energy -= 5;
			if(player_energy <0)
				player_energy = 0;

			speed_counter = 0;

			gotoxy(road[road_index][0],i);
			printf("*");
			break;
		}
		if( road[road_index][1]<=player_carpos+7)
		{
			show_car(-1);
			player_carpos--;

			player_speed -= 7+(player_speed/50);
			if(player_speed <0)
				player_speed = 0;

			player_energy -= 5;
			if(player_energy <0)
				player_energy = 0;

			
			speed_counter = 0;

			gotoxy(road[road_index][1],i);
			printf("*");
			break;
		}
	}
	return 0;
}

int show_gameover()
{
	gotoxy(12,8);
	printf("┏━━━━━━━━━━━━━━━━┓");
	gotoxy(12,9);
	printf("┃********************************┃");
	gotoxy(12,10);
	printf("┃*           GAME OVER          *┃");
	gotoxy(12,11);
	printf("┃********************************┃");
	gotoxy(12,12);
	printf("┗━━━━━━━━━━━━━━━━┛");
	return 0;
}

int show_count()
{
	int i,j,k;
	gotoxy(16,5);
	printf("┏━━━━━━━━━━┓");
	gotoxy(16,6);
	printf("┃       ■■■       ┃");
	gotoxy(16,7);
	printf("┃     ■      ■     ┃");
	gotoxy(16,8);
	printf("┃             ■     ┃");
	gotoxy(16,9);
	printf("┃             ■     ┃");
	gotoxy(16,10);
	printf("┃         ■■       ┃");
	gotoxy(16,11);
	printf("┃             ■     ┃");
	gotoxy(16,12);
	printf("┃    ■        ■    ┃");
	gotoxy(16,13);
	printf("┃     ■      ■     ┃");
	gotoxy(16,14);
	printf("┃       ■■■       ┃");
	gotoxy(16,15);
	printf("┣━━━━━━━━━━┫");
	gotoxy(16,16);
	printf("┃  ← : Move Left    ┃");
	gotoxy(16,17);
	printf("┃  → : Move Right   ┃");
	gotoxy(16,18);
	printf("┗━━━━━━━━━━┛");

	gotoxy(0,23);
	Sleep(1000);

	gotoxy(16,5);
	printf("┏━━━━━━━━━━┓");
	gotoxy(16,6);
	printf("┃       ■■■       ┃");
	gotoxy(16,7);
	printf("┃     ■      ■     ┃");
	gotoxy(16,8);
	printf("┃             ■     ┃");
	gotoxy(16,9);
	printf("┃            ■      ┃");
	gotoxy(16,10);
	printf("┃          ■        ┃");
	gotoxy(16,11);
	printf("┃        ■          ┃");
	gotoxy(16,12);
	printf("┃      ■            ┃");
	gotoxy(16,13);
	printf("┃    ■              ┃");
	gotoxy(16,14);
	printf("┃    ■■■■■■    ┃");
	

	gotoxy(0,23);
	Sleep(1000);

	gotoxy(16,5);
	printf("┏━━━━━━━━━━┓");
	gotoxy(16,6);
	printf("┃         ■         ┃");
	gotoxy(16,7);
	printf("┃       ■■         ┃");
	gotoxy(16,8);
	printf("┃         ■         ┃");
	gotoxy(16,9);
	printf("┃         ■         ┃");
	gotoxy(16,10);
	printf("┃         ■         ┃");
	gotoxy(16,11);
	printf("┃         ■         ┃");
	gotoxy(16,12);
	printf("┃         ■         ┃");
	gotoxy(16,13);
	printf("┃         ■         ┃");
	gotoxy(16,14);
	printf("┃       ■■■       ┃");
	
	gotoxy(0,23);
	Sleep(1000);

	gotoxy(16,5);
	printf("┏━━━━━━━━━━┓");
	gotoxy(16,6);
	printf("┃       ■■■       ┃");
	gotoxy(16,7);
	printf("┃     ■      ■     ┃");
	gotoxy(16,8);
	printf("┃     ■      ■     ┃");
	gotoxy(16,9);
	printf("┃     ■    ■■     ┃");
	gotoxy(16,10);
	printf("┃     ■  ■  ■     ┃");
	gotoxy(16,11);
	printf("┃     ■■    ■     ┃");
	gotoxy(16,12);
	printf("┃     ■      ■     ┃");
	gotoxy(16,13);
	printf("┃     ■      ■     ┃");
	gotoxy(16,14);
	printf("┃       ■■■       ┃");

	
		for(j=16,k=40;j<=41;j++,k--)
		{
			for(i=5;i<18;i+=2)
			{
				gotoxy(j-1,i);
				printf(" ");
				if(j!=41)
				{
					
					printf("*");
				}
				gotoxy(k,i+1);
				if(k!=13)
				{
					printf("*");
				}
				printf(" ");
				
			}
			Sleep(80);
		}
	
	
	return 0;
	
}


