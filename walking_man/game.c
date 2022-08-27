#include "head.h"

int main()
{
	FILE *fp;
	double delay;
	int frame=0;
	int i;
	int filesize;
	int n;
	char key_temp;
	struct Person data;
	
	show_walkingman();
	init();

	// 파일을 open, 새로운 파일이면 w로 생성
	if ((fp = fopen(FILENAME, "r+b"))==NULL) { // 파일이 없으면
		fp = fopen(FILENAME, "w+b"); // 새로 생성
		if (fp==NULL) {
			printf("File Maker Error.\n");
			exit(0);
		}
	}

	//파일사이즈=n
	fseek(fp, 0, SEEK_END); // 끝으로 이동
	filesize = ftell(fp); // 파일 크기가 return 됨
	n = filesize / sizeof(struct Person);

	//파일에서배열로 이름가져오기
	fseek(fp, 0, SEEK_SET); // 처음으로 이동
	for (i=0;i<n;i++) {
		fread(&data, sizeof(data), 1, fp);
		Person_arr[i] = data;
	}

	//배열크기조절
	//Person_count구하기
	Person_count = n%10;

	select_shoes();

	//player_name과같은이름 있는지 확인, 있으면 Person_count수정
	fseek(fp, 0, SEEK_SET); // 처음으로 이동
	for (i=0;i<n;i++) {
		fread(&data, sizeof(data), 1, fp);
		if (strcmp(data.name, player_name)==0)
		{
			Person_count = i;
			break;
		}
	}
	//없으면 Person_count 그대로;

	system("cls");
	show_count();
	player_wearability = shoedata[player_shoenum].power;
	show_gameframe();
	show_stat();
	player_flexibility = (float) shoedata[player_shoenum].flexibility/10;
	
	for(i=0;i<=200000;i++)
	{
		gotoxy(0,23);	printf("  ");
		gotoxy(59,17);	printf("---Time: %d---", 200000-i);
		gotoxy(0,24);
		if(kbhit())
		{
			key_temp = getche();
			gotoxy(0,24);	printf("**");
			if(key_temp == EXT_KEY)		//입력이 확장키인 경우(<-, ->)
			{
				key_temp = getche();
				switch(key_temp)
				{
				case LEFT:
					show_shoe(-1);	//move=-1 : 왼쪽으로 한칸이동
					player_speed -=1;	//이동하는 순간에는 속도를 줄인다
					strike_check();		//길 이탈 체크
					break;
				case RIGHT:
					show_shoe(1);		//move=1 : 오른쪽으로 한칸이동
					player_speed -=1;	//이동하는 순간에는 속도를 줄인다
					strike_check();		//길 이탈 체크
					break;
				}
			}
			strike_check();
		}
		//게임의 속도를 계속해서 일정 수준까지 증가
		if(player_speed < 100)
			player_speed += 2.7;
		//플레이어가 길 이탈 없이 잘 걷는 경우 flexibility를 이용하여 추가 속도 증가
		//기존 speed가 빠를 수록 속도 증가 폭은 작게 설정
		if(speed_counter > 6)
		{
			if(player_speed < 100)
			{
				player_speed = player_speed + (7.6 * player_flexibility);
			}else if(player_speed < 200)
			{
				player_speed = player_speed + (1.2 * player_flexibility );
			}else if(player_speed < 300)
			{
				player_speed = player_speed + ( 0.3 * player_flexibility );
			}else if(player_speed < 315)
			{
				player_speed = player_speed + ( 0.1 * player_flexibility );
			}else
			{
				player_speed = player_speed + ( 0.06 * player_flexibility );
			}
			//최대치 속도를 넘으면 다시 최대 속도로 바꿔준다
			if(player_speed>shoedata[player_shoenum].max_spd)
				player_speed = shoedata[player_shoenum].max_spd;
		}
		//게임에 delay 주기 - 점점감소하다가 길 이탈 시 증가
		//exp() - 거듭제곱
		delay = 350 - (351 * (1-exp(-player_speed/70)));		
		if(delay<0)
			delay=0.01;
		//i=0~200000까지 5의 배수마다 게임 데이터 갱신(checking)
		if(i%5==0)
		{
			player_score = (float)((player_score + player_speed/50)* 1.0003);
			data.score = player_score;
			show_stat();
			show_shoe(0);
			show_road();
			strike_check();
			speed_counter++;
		}
		show_stat();
		if(player_wearability <=0)
		{
			show_gameover();
			fflush(stdin);
			gotoxy(0,24);
			scanf("%d",&i);
			break;
		}
		gotoxy(0,24);
		Sleep((unsigned int)delay);
	}
	fseek(fp, Person_count*sizeof(data), SEEK_SET);
	fwrite(&data, sizeof(data), 1, fp);
	fclose(fp);
	return 0;
}

int select_shoes()
{
	int i;
	int logo_delay=1;

	system("cls");

	for(i=0;i<=79;i++)
	{
		gotoxy(i,0);printf("*");
		Sleep(logo_delay);
	}
	for(i=1;i<=23;i++)
	{
		gotoxy(79,i);printf("*");
		Sleep(logo_delay);
	}
	for(i=78;i>=0;i--)
	{
		gotoxy(i,24);
		printf("*");
		Sleep(logo_delay);
	}
	for(i=23;i>=1;i--)
	{
		gotoxy(0,i);printf("*");
		Sleep(logo_delay);
	}

	Sleep(80);
	gotoxy(3,1);	printf("Programming Lab Term Project");		Sleep(80);
	gotoxy(59,1);	printf("1492018 SeoHeeSeon");				Sleep(80);

	gotoxy(6,5);	printf("[Shoes1: %s]", shoedata[0].name);
	show_shoexy(0,9,6);
	gotoxy(25,7);	printf("speed: %d", shoedata[0].max_spd);
	gotoxy(25,8);	printf("power: %d", shoedata[0].power);
	gotoxy(25,9);	printf("flexible: %d", shoedata[0].flexibility);

	Sleep(300);
	gotoxy(43,5);	printf("[Shoes2: %s]", shoedata[1].name);
	show_shoexy(1,46,6);
	gotoxy(62,7);	printf("speed: %d", shoedata[1].max_spd);
	gotoxy(62,8);	printf("power: %d", shoedata[1].power);
	gotoxy(62,9);	printf("flexible: %d", shoedata[1].flexibility);

	Sleep(300);
	gotoxy(6,13);	printf("[Shoes3: %s]", shoedata[2].name);
	show_shoexy(2,9,14);
	gotoxy(25,15);	printf("speed: %d", shoedata[2].max_spd);
	gotoxy(25,16);	printf("power: %d", shoedata[2].power);
	gotoxy(25,17);	printf("flexible: %d", shoedata[2].flexibility);

	Sleep(300);
	gotoxy(43,13);	printf("[Shoes4: %s]", shoedata[3].name);
	show_shoexy(3,46,14);
	gotoxy(62,15);	printf("speed: %d", shoedata[3].max_spd);
	gotoxy(62,16);	printf("power: %d", shoedata[3].power);
	gotoxy(62,17);	printf("flexible: %d", shoedata[3].flexibility);

	gotoxy(40,22);	printf("Name:");
	gotoxy(40,23);	printf("Choose shoes number from 1 to 4:");
	getchar();
	fflush(stdin);
	gotoxy(47,22);
	scanf("%s",player_name);

GetShoeNum:

	fflush(stdin);
	gotoxy(74,23);
	scanf("%d",&player_shoenum);

	if((player_shoenum < 1) || (player_shoenum > 4))
	{
		gotoxy(5,22);	printf("Wrong number error!");
		gotoxy(5,23);	printf("Please re-enter.");
		gotoxy(74,23);	printf("  ");
		goto GetShoeNum;
	}
	player_shoenum--;

	return 0;
}

int show_gameframe()
{
	int i;

	frame();
	gotoxy(3,1);	printf("							");		
	gotoxy(59,1);	printf("Programming Lab   ");		
	gotoxy(59,2);	printf("1492018 SeoHeeSeon");	

	gotoxy(58,4);
	printf(" Name: ");
	printf("%s",player_name);

	gotoxy(58,5);
	printf(" Score:");
	gotoxy(58,7);
	printf(" Power:");
	gotoxy(58,6);
	printf(" Speed:");
	gotoxy(58,9);
	printf(" Accuracy:");

	gotoxy(59,18);
	printf("<Shoe Info>");
	gotoxy(59,19);
	printf("Model    : %s",shoedata[player_shoenum].name);
	gotoxy(59,20);
	printf("Max Speed: %d",shoedata[player_shoenum].max_spd);
	gotoxy(59,21);
	printf("Power    : %d",shoedata[player_shoenum].power);
	gotoxy(59,22);
	printf("Flexible : %d",shoedata[player_shoenum].flexibility);

	return 0;
}

int show_stat()
{
	int i,j;
	int recent_wearability = 999, recent_accu = 999, recent_speed = 999;

	//score 표시
	gotoxy(66,5);
	printf("%.0f",player_score);

	//speed 표시
	if(recent_speed != player_speed)
	{
		gotoxy(66,6);
		printf("%.0f",player_speed);
	}
	
	//power표시(wearability가 높을수록 power 높아진다)
	gotoxy(58,8);
	if(recent_wearability !=player_wearability)
	{
		for(i=0,j=player_wearability;i<10;i++)
		{
			if(j>=10)
				printf("■");
			else
				printf("□");
			j-=10;
		}
	}

	//accuracy(정확도)표시(길 이탈이 잦으면 감소하는 값(충돌함수에서 구현) - wearability와 관련)
	gotoxy(58,10);
	j= (int) ((player_speed * 10) / shoedata[player_shoenum].max_spd );
	if(j != recent_accu)
	{		
		for(i=0;i<10;i++)
		{
			if(j>i)
				printf("■");
			else
				printf("□");
		}
	}

	recent_accu = j;
	recent_wearability = player_wearability;

	return 0;
}

int init()
{
	int i,j;

	road_index = 0;
	next_index = 0;

	sprintf(shoedata[0].name,"Dog");
	shoedata[0].max_spd=250;
	shoedata[0].power=60;
	shoedata[0].flexibility=10;

	sprintf(shoedata[1].name,"Normal");
	shoedata[1].max_spd=300;
	shoedata[1].power=70;
	shoedata[1].flexibility=8;

	sprintf(shoedata[2].name,"Woman");
	shoedata[2].max_spd=270;
	shoedata[2].power=80;
	shoedata[2].flexibility=7;

	sprintf(shoedata[3].name,"Bear");
	shoedata[3].max_spd=350;
	shoedata[3].power=90;
	shoedata[3].flexibility=5;

	srand((unsigned)time(NULL));	///더 랜덤으로 생성하기 위해

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

int show_shoexy(int shoenum,int x,int y)
{
	int i;
	int seo;

	mancnt = mancnt%2;		//mancnt가 계속 증가하는 것을 막음
	//mancnt에 따라 발 모양 번갈아 찍기
	if(mancnt%2){
		for(i=y; i<=y+4; i++)
		{	
			gotoxy(x-1,i);
			printf(" %8s ",shoe[shoenum][i-y]);
		}
	}
	else{
		for(i=y; i<=y+4; i++)
		{	
			gotoxy(x-1,i);
			printf(" %8s ",shoe2[shoenum][i-y]);
		}
	}

	mancnt++;
	return 0;
}

int show_road()
{
	int i,j;
	int sand;
	int rand_num;

	//화면 밖 길 지우기
	gotoxy(road[(road_index+1)%22][0],1);
	printf(" ");
	gotoxy(road[(road_index+1)%22][1],1);
	printf(" ");

	//새로 생성되는 길을 표시하기 전, 이전 길 지우기
	for(j=2,i=road_index+1;j<23;i++,j++)
	{
		i =i%22;
		if(road[(i+1)%22][0] != road[i][0]) 	//새로운 길의 위치가 이전과 다를 때만
		{
			gotoxy(road[(i+1)%22][0],j);
			printf(" ");
			gotoxy(road[(i+1)%22][1],j);
			printf(" ");
		}
	}

	//길 랜덤 생성
	rand_num=rand()%8;
	rand_num++;
	switch(rand_num)
	{
	case 0:
		if(road[(road_index+1)%22][0] <=4 )	//왼쪽 길이 x좌표 4이전일때 직진
		{
			road[next_index][0] = road[(road_index+1)%22][0];
			road[next_index][1] = road[(road_index+1)%22][1];
			break;
		}
		//아니면 왼쪽으로 두칸이동
		road[next_index][0] =road[(road_index+1)%22][0]-2;
		road[next_index][1] =road[(road_index+1)%22][1]-2;
		break;
	case 1:case 2:
		if(road[(road_index+1)%22][0] <=3 )	//왼쪽 길이 x좌표 3이전일때 직진
		{
			road[next_index][0] = road[(road_index+1)%22][0];
			road[next_index][1] = road[(road_index+1)%22][1];
			break;
		}
		//아니면 왼쪽으로 한칸이동
		road[next_index][0] =road[(road_index+1)%22][0]-1;
		road[next_index][1] =road[(road_index+1)%22][1]-1;
		break;
	case 7:case 8:
		if(road[(road_index+1)%22][1] >=55 )	//오른쪽 길이 x좌표 55이후일때 직진
		{
			road[next_index][0] = road[(road_index+1)%22][0];
			road[next_index][1] = road[(road_index+1)%22][1];
			break;
		}
		//아니면 오른쪽으로 한칸이동
		road[next_index][0] =road[(road_index+1)%22][0]+1;
		road[next_index][1] =road[(road_index+1)%22][1]+1;
		break;
	case 9:
		if(road[(road_index+1)%22][1] >=54 )	//오른쪽 길이 x좌표 55이후일때 직진
		{
			road[next_index][0] = road[(road_index+1)%22][0];
			road[next_index][1] = road[(road_index+1)%22][1];
			break;
		}
		//아니면 왼쪽으로 두칸이동
		road[next_index][0] =road[(road_index+1)%22][0]+2;
		road[next_index][1] =road[(road_index+1)%22][1]+2;
		break;
	default: //직진
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
		//road[i][0]: 길 왼쪽 모래알 채우기
		gotoxy(road[i][0],j);
		printf(".");
		for(sand=0; sand<road[i][0]; sand++)
		{
			gotoxy(sand,j);		printf(".");
		}
		//road[i][1]: 길 오른쪽 모래알 채우기
		gotoxy(road[i][1],j);
		printf(".");
		for(sand=road[i][1]+1; sand<57; sand++)
		{
			gotoxy(sand,j);		printf(".");
		}
	}
	road_index=next_index;

	return 0;
}

int	show_shoe(int move)
{
	player_shoepos = player_shoepos + move;

	//발이 화면 밖으로 나가지 못하게 좌표 수정
	if( player_shoepos <2)
		player_shoepos = 2;
	if( player_shoepos >48)
		player_shoepos = 48;

	show_shoexy(player_shoenum,player_shoepos,18);
	return 0;
}

int strike_check()
{
	int i;

	for(i=18;i<=19;i++)
	{
		//신발이 왼쪽 길 이탈
		if( road[road_index][0]>=player_shoepos) 
		{
			show_shoe(1);
			player_shoepos++;

			player_speed -= 7+(player_speed/50);
			if(player_speed <0)
				player_speed = 0;

			player_wearability -= 5;
			if(player_wearability <0)
				player_wearability = 0;

			speed_counter = 0;		//speed_counter리셋(main - 속도 증가 리셋)

			gotoxy(road[road_index][0],i);
			printf("★★\a\a");
			gotoxy(58,12+(crash++%4));
			printf("※※Be careful!※※");
			break;
		}
		//신발이 오른쪽 길 이탈
		if( road[road_index][1]<=player_shoepos+7) 
		{
			show_shoe(-1);
			player_shoepos--;

			player_speed -= 7+(player_speed/50);
			if(player_speed <0)
				player_speed = 0;

			player_wearability -= 5;
			if(player_wearability <0)
				player_wearability = 0;

			speed_counter = 0;		//speed_counter리셋(main - 속도 증가 리셋)

			gotoxy(road[road_index][1],i);
			printf("★★\a\a");
			gotoxy(58,12+(crash++%4));
			printf("※※Be careful!※※");
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
	printf("┃        G A M E  O V E R        ┃");
	gotoxy(12,10);
	printf("┃ Name : %s                         ", player_name);
	gotoxy(45,10);	printf(" ┃");
	gotoxy(12,11);
	printf("┃ Score : %.0f                        ", player_score);
	gotoxy(45,11);	printf(" ┃");
	gotoxy(12,12);
	printf("┗━━━━━━━━━━━━━━━━┛");
	return 0;
}

int show_count()
{
	int i,j,k;

	gotoxy(28,6);
	printf("         ■■■         ");
	gotoxy(28,7);
	printf("       ■      ■       ");
	gotoxy(28,8);
	printf("               ■       ");
	gotoxy(28,9);
	printf("               ■       ");
	gotoxy(28,10);
	printf("           ■■         ");
	gotoxy(28,11);
	printf("               ■       ");
	gotoxy(28,12);
	printf("      ■        ■      ");
	gotoxy(28,13);
	printf("       ■      ■       ");
	gotoxy(28,14);
	printf("         ■■■         ");

	gotoxy(28,16);
	printf("      ← : Left      ");
	gotoxy(28,17);
	printf("      → : Right     ");

	gotoxy(0,23);
	Sleep(1000);

	gotoxy(28,6);
	printf("         ■■■         ");
	gotoxy(28,7);
	printf("       ■      ■       ");
	gotoxy(28,8);
	printf("               ■       ");
	gotoxy(28,9);
	printf("              ■        ");
	gotoxy(28,10);
	printf("            ■          ");
	gotoxy(28,11);
	printf("          ■            ");
	gotoxy(28,12);
	printf("        ■              ");
	gotoxy(28,13);
	printf("      ■                ");
	gotoxy(28,14);
	printf("      ■■■■■■      ");

	gotoxy(0,23);
	Sleep(1000);

	gotoxy(28,6);
	printf("           ■           ");
	gotoxy(28,7);
	printf("         ■■           ");
	gotoxy(28,8);
	printf("           ■           ");
	gotoxy(28,9);
	printf("           ■           ");
	gotoxy(28,10);
	printf("           ■           ");
	gotoxy(28,11);
	printf("           ■           ");
	gotoxy(28,12);
	printf("           ■           ");
	gotoxy(28,13);
	printf("           ■           ");
	gotoxy(28,14);
	printf("         ■■■         ");

	gotoxy(0,23);
	Sleep(1000);

	gotoxy(28,6);
	printf("         ■■■         ");
	gotoxy(28,7);
	printf("       ■      ■       ");
	gotoxy(28,8);
	printf("       ■      ■       ");
	gotoxy(28,9);
	printf("       ■    ■■       ");
	gotoxy(28,10);
	printf("       ■  ■  ■       ");
	gotoxy(28,11);
	printf("       ■■    ■       ");
	gotoxy(28,12);
	printf("       ■      ■       ");
	gotoxy(28,13);
	printf("       ■      ■       ");
	gotoxy(28,14);
	printf("         ■■■         ");

	for(i=0;i<25;i++)
	{
		for(j=0;j<80;j+=2)
		{
			gotoxy(j,i);
			printf("◈");
		}
		for(j=1;j<80;j+=2)
		{
			gotoxy(j,i);
			printf("◈");
		}
		Sleep(10);
	}
	system("cls");

	return 0;
}

int show_walkingman()
{
	while(!kbhit())
	{
		printf("\n               `;~.`\n");
		printf("               Z$An..\n");
		printf("               qBRRa^\n");
		printf("              .uaBA=\n");
		printf("             :<.`.`\n");
		printf("            .0q;Xv'`\n");
		printf("            `A==ZN=`\n");
		printf("             nu1u:-`\n");
		printf("             |0=RXr.\n");
		printf("             '0cRnX|\n");
		printf("             U$aa:sa^\n");
		printf("             O@NFN<0Zl\n");
		printf("             `AUc@Rluv\n");
		printf("               @@@$U~^\n");
		printf("               B$HRBO^`\n");
		printf("               AOA.a$s^\n");
		printf("               0RZcFsF~\n");
		printf("              .UaA0Ha.\n");
		printf("              nUX0BU`\n");
		printf("              Z0BBc\n");
		printf("              q00:\n");
		printf("             .$s:.'\n");
		printf("             lXXrr~.`\n");

		gotoxy(40,5);	printf("■■■   ■   ■  ■ ■■■");
		gotoxy(40,6);	printf("  ■    ■■  ■■   ■■■");
		gotoxy(40,7);	printf("  ■   ■  ■ ■  ■ ■■■");

		gotoxy(40,9);	printf("            ■");
		gotoxy(40,10);	printf("           ■■");
		gotoxy(40,11);	printf("          ■  ■");

		gotoxy(40,13);	printf("■  ■   ■   ■     ■  ■");
		gotoxy(40,14);	printf("■■■  ■■  ■     ■■");
		gotoxy(40,15);	printf(" ■■  ■  ■ ■■■ ■  ■");
		gotoxy(40,17);	printf("     Press Enter Key.");

		gotoxy(60,22);	printf("Term project 2-1");
		gotoxy(60,23);	printf("Made by HeeSeon");

		Sleep(400);	system("cls");

		printf("\n               .`'\n");
		printf("              nBa1 `\n");
		printf("              n00Ur.\n");
		printf("             .FR$$s\n");
		printf("            '`  l s\n");
		printf("           `si`^`\n");
		printf("           ~c~lAz.`\n");
		printf("           :=`<;<.`\n");
		printf("           la~Hci.`\n");
		printf("           iaiRFi-.\n");
		printf("           'N.N;'=0a.\n");
		printf("            N^0R; ^^'AX`\n");
		printf("           'c'B$0z`   `\n");
		printf("           -BB@@BRn`\n");
		printf("            ^B$NzRqz``\n");
		printf("            vBB:`^RRi.\n");
		printf("            AUa~  .0.~\n");
		printf("           :cXu   rn.'\n");
		printf("           u1`    =Rc`\n");
		printf("          ia1`    ^R1'\n");
		printf("          =R<      H<.\n");
		printf("          N0n      Ui  ``\n");
		printf("         `:rr^``   -..`\n");

		gotoxy(40,5);	printf("■■■   ■   ■  ■ ■■■");
		gotoxy(40,6);	printf("  ■    ■■  ■■   ■■■");
		gotoxy(40,7);	printf("  ■   ■  ■ ■  ■ ■■■");

		gotoxy(40,9);	printf("            ■");
		gotoxy(40,10);	printf("           ■■");
		gotoxy(40,11);	printf("          ■  ■");

		gotoxy(40,13);	printf("■  ■   ■   ■     ■  ■");
		gotoxy(40,14);	printf("■■■  ■■  ■     ■■");
		gotoxy(40,15);	printf(" ■■  ■  ■ ■■■ ■  ■");
		gotoxy(40,17);	printf("     Press Enter Key..");

		gotoxy(60,22);	printf("Term project 2-1");
		gotoxy(60,23);	printf("Made by HeeSeon");

		Sleep(400);	system("cls");

		printf("\n                ``\n");
		printf("              s0:..\n");
		printf("              $RHu~`\n");
		printf("             '$$$$r\n");
		printf("            .l';Fv\n");
		printf("           `1`\n");
		printf("           cnr=U'\n");
		printf("           u.'csc.`\n");
		printf("           0ivHl.``\n");
		printf("          .Uus$;'..`\n");
		printf("          .H<R0z^l;zs`\n");
		printf("           NiR0R:-l ^Hu`\n");
		printf("          `c-BBBR~``\n");
		printf("          cau$$$Ba-`\n");
		printf("           u00@@0qz^`\n");
		printf("           v00BH~H0F'\n");
		printf("          =AHNc   HF`\n");
		printf("        `cZRA1    nN..\n");
		printf("       .zzq:      .Rz^\n");
		printf("      ^s0s`        nq~`\n");
		printf("     <0Hz          `$u.\n");
		printf("    .u0qi           ZF^` `'\n");
		printf("       ~:~          .=l^``\n");

		gotoxy(40,5);	printf("■■■   ■   ■  ■ ■■■");
		gotoxy(40,6);	printf("  ■    ■■  ■■   ■■■");
		gotoxy(40,7);	printf("  ■   ■  ■ ■  ■ ■■■");

		gotoxy(40,9);	printf("            ■");
		gotoxy(40,10);	printf("           ■■");
		gotoxy(40,11);	printf("          ■  ■");

		gotoxy(40,13);	printf("■  ■   ■   ■     ■  ■");
		gotoxy(40,14);	printf("■■■  ■■  ■     ■■");
		gotoxy(40,15);	printf(" ■■  ■  ■ ■■■ ■  ■");
		gotoxy(40,17);	printf("     Press Enter Key...");

		gotoxy(60,22);	printf("Term project 2-1");
		gotoxy(60,23);	printf("Made by HeeSeon");

		Sleep(400);	system("cls");
	}

	return 0;
}

int frame()
{
	int i;

	for(i=0;i<=79;i++)
	{
		gotoxy(i,0);printf("*");
	}
	for(i=1;i<=23;i++)
	{
		gotoxy(79,i);printf("*");
	}
	for(i=78;i>=0;i--)
	{
		gotoxy(i,24);
		printf("*");
	}
	for(i=23;i>=1;i--)
	{
		gotoxy(0,i);printf("*");
	}

	gotoxy(3,1);	printf("Programming Lab Term Project");		
	gotoxy(59,1);	printf("1492018 SeoHeeSeon");			

	return 0;
}