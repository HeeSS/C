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

	// ������ open, ���ο� �����̸� w�� ����
	if ((fp = fopen(FILENAME, "r+b"))==NULL) { // ������ ������
		fp = fopen(FILENAME, "w+b"); // ���� ����
		if (fp==NULL) {
			printf("File Maker Error.\n");
			exit(0);
		}
	}

	//���ϻ�����=n
	fseek(fp, 0, SEEK_END); // ������ �̵�
	filesize = ftell(fp); // ���� ũ�Ⱑ return ��
	n = filesize / sizeof(struct Person);

	//���Ͽ����迭�� �̸���������
	fseek(fp, 0, SEEK_SET); // ó������ �̵�
	for (i=0;i<n;i++) {
		fread(&data, sizeof(data), 1, fp);
		Person_arr[i] = data;
	}

	//�迭ũ������
	//Person_count���ϱ�
	Person_count = n%10;

	select_shoes();

	//player_name�������̸� �ִ��� Ȯ��, ������ Person_count����
	fseek(fp, 0, SEEK_SET); // ó������ �̵�
	for (i=0;i<n;i++) {
		fread(&data, sizeof(data), 1, fp);
		if (strcmp(data.name, player_name)==0)
		{
			Person_count = i;
			break;
		}
	}
	//������ Person_count �״��;

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
			if(key_temp == EXT_KEY)		//�Է��� Ȯ��Ű�� ���(<-, ->)
			{
				key_temp = getche();
				switch(key_temp)
				{
				case LEFT:
					show_shoe(-1);	//move=-1 : �������� ��ĭ�̵�
					player_speed -=1;	//�̵��ϴ� �������� �ӵ��� ���δ�
					strike_check();		//�� ��Ż üũ
					break;
				case RIGHT:
					show_shoe(1);		//move=1 : ���������� ��ĭ�̵�
					player_speed -=1;	//�̵��ϴ� �������� �ӵ��� ���δ�
					strike_check();		//�� ��Ż üũ
					break;
				}
			}
			strike_check();
		}
		//������ �ӵ��� ����ؼ� ���� ���ر��� ����
		if(player_speed < 100)
			player_speed += 2.7;
		//�÷��̾ �� ��Ż ���� �� �ȴ� ��� flexibility�� �̿��Ͽ� �߰� �ӵ� ����
		//���� speed�� ���� ���� �ӵ� ���� ���� �۰� ����
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
			//�ִ�ġ �ӵ��� ������ �ٽ� �ִ� �ӵ��� �ٲ��ش�
			if(player_speed>shoedata[player_shoenum].max_spd)
				player_speed = shoedata[player_shoenum].max_spd;
		}
		//���ӿ� delay �ֱ� - ���������ϴٰ� �� ��Ż �� ����
		//exp() - �ŵ�����
		delay = 350 - (351 * (1-exp(-player_speed/70)));		
		if(delay<0)
			delay=0.01;
		//i=0~200000���� 5�� ������� ���� ������ ����(checking)
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

	//score ǥ��
	gotoxy(66,5);
	printf("%.0f",player_score);

	//speed ǥ��
	if(recent_speed != player_speed)
	{
		gotoxy(66,6);
		printf("%.0f",player_speed);
	}
	
	//powerǥ��(wearability�� �������� power ��������)
	gotoxy(58,8);
	if(recent_wearability !=player_wearability)
	{
		for(i=0,j=player_wearability;i<10;i++)
		{
			if(j>=10)
				printf("��");
			else
				printf("��");
			j-=10;
		}
	}

	//accuracy(��Ȯ��)ǥ��(�� ��Ż�� ������ �����ϴ� ��(�浹�Լ����� ����) - wearability�� ����)
	gotoxy(58,10);
	j= (int) ((player_speed * 10) / shoedata[player_shoenum].max_spd );
	if(j != recent_accu)
	{		
		for(i=0;i<10;i++)
		{
			if(j>i)
				printf("��");
			else
				printf("��");
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

	srand((unsigned)time(NULL));	///�� �������� �����ϱ� ����

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

	mancnt = mancnt%2;		//mancnt�� ��� �����ϴ� ���� ����
	//mancnt�� ���� �� ��� ������ ���
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

	//ȭ�� �� �� �����
	gotoxy(road[(road_index+1)%22][0],1);
	printf(" ");
	gotoxy(road[(road_index+1)%22][1],1);
	printf(" ");

	//���� �����Ǵ� ���� ǥ���ϱ� ��, ���� �� �����
	for(j=2,i=road_index+1;j<23;i++,j++)
	{
		i =i%22;
		if(road[(i+1)%22][0] != road[i][0]) 	//���ο� ���� ��ġ�� ������ �ٸ� ����
		{
			gotoxy(road[(i+1)%22][0],j);
			printf(" ");
			gotoxy(road[(i+1)%22][1],j);
			printf(" ");
		}
	}

	//�� ���� ����
	rand_num=rand()%8;
	rand_num++;
	switch(rand_num)
	{
	case 0:
		if(road[(road_index+1)%22][0] <=4 )	//���� ���� x��ǥ 4�����϶� ����
		{
			road[next_index][0] = road[(road_index+1)%22][0];
			road[next_index][1] = road[(road_index+1)%22][1];
			break;
		}
		//�ƴϸ� �������� ��ĭ�̵�
		road[next_index][0] =road[(road_index+1)%22][0]-2;
		road[next_index][1] =road[(road_index+1)%22][1]-2;
		break;
	case 1:case 2:
		if(road[(road_index+1)%22][0] <=3 )	//���� ���� x��ǥ 3�����϶� ����
		{
			road[next_index][0] = road[(road_index+1)%22][0];
			road[next_index][1] = road[(road_index+1)%22][1];
			break;
		}
		//�ƴϸ� �������� ��ĭ�̵�
		road[next_index][0] =road[(road_index+1)%22][0]-1;
		road[next_index][1] =road[(road_index+1)%22][1]-1;
		break;
	case 7:case 8:
		if(road[(road_index+1)%22][1] >=55 )	//������ ���� x��ǥ 55�����϶� ����
		{
			road[next_index][0] = road[(road_index+1)%22][0];
			road[next_index][1] = road[(road_index+1)%22][1];
			break;
		}
		//�ƴϸ� ���������� ��ĭ�̵�
		road[next_index][0] =road[(road_index+1)%22][0]+1;
		road[next_index][1] =road[(road_index+1)%22][1]+1;
		break;
	case 9:
		if(road[(road_index+1)%22][1] >=54 )	//������ ���� x��ǥ 55�����϶� ����
		{
			road[next_index][0] = road[(road_index+1)%22][0];
			road[next_index][1] = road[(road_index+1)%22][1];
			break;
		}
		//�ƴϸ� �������� ��ĭ�̵�
		road[next_index][0] =road[(road_index+1)%22][0]+2;
		road[next_index][1] =road[(road_index+1)%22][1]+2;
		break;
	default: //����
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
		//road[i][0]: �� ���� �𷡾� ä���
		gotoxy(road[i][0],j);
		printf(".");
		for(sand=0; sand<road[i][0]; sand++)
		{
			gotoxy(sand,j);		printf(".");
		}
		//road[i][1]: �� ������ �𷡾� ä���
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

	//���� ȭ�� ������ ������ ���ϰ� ��ǥ ����
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
		//�Ź��� ���� �� ��Ż
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

			speed_counter = 0;		//speed_counter����(main - �ӵ� ���� ����)

			gotoxy(road[road_index][0],i);
			printf("�ڡ�\a\a");
			gotoxy(58,12+(crash++%4));
			printf("�ء�Be careful!�ء�");
			break;
		}
		//�Ź��� ������ �� ��Ż
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

			speed_counter = 0;		//speed_counter����(main - �ӵ� ���� ����)

			gotoxy(road[road_index][1],i);
			printf("�ڡ�\a\a");
			gotoxy(58,12+(crash++%4));
			printf("�ء�Be careful!�ء�");
			break;
		}
	}

	return 0;
}

int show_gameover()
{
	gotoxy(12,8);
	printf("������������������������������������");
	gotoxy(12,9);
	printf("��        G A M E  O V E R        ��");
	gotoxy(12,10);
	printf("�� Name : %s                         ", player_name);
	gotoxy(45,10);	printf(" ��");
	gotoxy(12,11);
	printf("�� Score : %.0f                        ", player_score);
	gotoxy(45,11);	printf(" ��");
	gotoxy(12,12);
	printf("������������������������������������");
	return 0;
}

int show_count()
{
	int i,j,k;

	gotoxy(28,6);
	printf("         ����         ");
	gotoxy(28,7);
	printf("       ��      ��       ");
	gotoxy(28,8);
	printf("               ��       ");
	gotoxy(28,9);
	printf("               ��       ");
	gotoxy(28,10);
	printf("           ���         ");
	gotoxy(28,11);
	printf("               ��       ");
	gotoxy(28,12);
	printf("      ��        ��      ");
	gotoxy(28,13);
	printf("       ��      ��       ");
	gotoxy(28,14);
	printf("         ����         ");

	gotoxy(28,16);
	printf("      �� : Left      ");
	gotoxy(28,17);
	printf("      �� : Right     ");

	gotoxy(0,23);
	Sleep(1000);

	gotoxy(28,6);
	printf("         ����         ");
	gotoxy(28,7);
	printf("       ��      ��       ");
	gotoxy(28,8);
	printf("               ��       ");
	gotoxy(28,9);
	printf("              ��        ");
	gotoxy(28,10);
	printf("            ��          ");
	gotoxy(28,11);
	printf("          ��            ");
	gotoxy(28,12);
	printf("        ��              ");
	gotoxy(28,13);
	printf("      ��                ");
	gotoxy(28,14);
	printf("      �������      ");

	gotoxy(0,23);
	Sleep(1000);

	gotoxy(28,6);
	printf("           ��           ");
	gotoxy(28,7);
	printf("         ���           ");
	gotoxy(28,8);
	printf("           ��           ");
	gotoxy(28,9);
	printf("           ��           ");
	gotoxy(28,10);
	printf("           ��           ");
	gotoxy(28,11);
	printf("           ��           ");
	gotoxy(28,12);
	printf("           ��           ");
	gotoxy(28,13);
	printf("           ��           ");
	gotoxy(28,14);
	printf("         ����         ");

	gotoxy(0,23);
	Sleep(1000);

	gotoxy(28,6);
	printf("         ����         ");
	gotoxy(28,7);
	printf("       ��      ��       ");
	gotoxy(28,8);
	printf("       ��      ��       ");
	gotoxy(28,9);
	printf("       ��    ���       ");
	gotoxy(28,10);
	printf("       ��  ��  ��       ");
	gotoxy(28,11);
	printf("       ���    ��       ");
	gotoxy(28,12);
	printf("       ��      ��       ");
	gotoxy(28,13);
	printf("       ��      ��       ");
	gotoxy(28,14);
	printf("         ����         ");

	for(i=0;i<25;i++)
	{
		for(j=0;j<80;j+=2)
		{
			gotoxy(j,i);
			printf("��");
		}
		for(j=1;j<80;j+=2)
		{
			gotoxy(j,i);
			printf("��");
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

		gotoxy(40,5);	printf("����   ��   ��  �� ����");
		gotoxy(40,6);	printf("  ��    ���  ���   ����");
		gotoxy(40,7);	printf("  ��   ��  �� ��  �� ����");

		gotoxy(40,9);	printf("            ��");
		gotoxy(40,10);	printf("           ���");
		gotoxy(40,11);	printf("          ��  ��");

		gotoxy(40,13);	printf("��  ��   ��   ��     ��  ��");
		gotoxy(40,14);	printf("����  ���  ��     ���");
		gotoxy(40,15);	printf(" ���  ��  �� ���� ��  ��");
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

		gotoxy(40,5);	printf("����   ��   ��  �� ����");
		gotoxy(40,6);	printf("  ��    ���  ���   ����");
		gotoxy(40,7);	printf("  ��   ��  �� ��  �� ����");

		gotoxy(40,9);	printf("            ��");
		gotoxy(40,10);	printf("           ���");
		gotoxy(40,11);	printf("          ��  ��");

		gotoxy(40,13);	printf("��  ��   ��   ��     ��  ��");
		gotoxy(40,14);	printf("����  ���  ��     ���");
		gotoxy(40,15);	printf(" ���  ��  �� ���� ��  ��");
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

		gotoxy(40,5);	printf("����   ��   ��  �� ����");
		gotoxy(40,6);	printf("  ��    ���  ���   ����");
		gotoxy(40,7);	printf("  ��   ��  �� ��  �� ����");

		gotoxy(40,9);	printf("            ��");
		gotoxy(40,10);	printf("           ���");
		gotoxy(40,11);	printf("          ��  ��");

		gotoxy(40,13);	printf("��  ��   ��   ��     ��  ��");
		gotoxy(40,14);	printf("����  ���  ��     ���");
		gotoxy(40,15);	printf(" ���  ��  �� ���� ��  ��");
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