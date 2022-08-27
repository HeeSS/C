#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//cir_rel.c 을 참고하여
//사각형의 점의 위치에 대한 검증 할 것
//argc, argv로 받는것(명령형 인자 체크), 직접 받는 것 모두 포함 할 것

typedef struct point {
	int x;
	int y;
}Point;
typedef struct rect {
	Point pt1;
	Point pt2;
}Rect;

void main(int argc, char *argv[])
{
	Point pt;
	Rect rect;
	int res;

	printf("argc : %d\n", argc);

	if (argc == 1) {
		printf("Type the coordinates(x,y) of point : ");
		scanf("%d %d", &pt.x, &pt.y);
		printf("%d %d\n", pt.x, pt.y);
		printf("Type the coordinates(x,y) of a corner point of a rectangle : ");
		scanf("%d %d", &rect.pt1.x, &rect.pt1.y);
		printf("%d %d\n", rect.pt1.x, rect.pt1.y);
		printf("Type the coordinates(x,y) of another corner point of a rectangle : ");
		scanf("%d %d", &rect.pt2.x, &rect.pt2.y);
		printf("%d %d\n", rect.pt2.x, rect.pt2.y);
	}
	else if(argc == 7)
	{
		printf("%s %s %s %s %s %s\n", argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
		pt.x = atoi(argv[1]);
		pt.y = atoi(argv[2]);
		rect.pt1.x = atoi(argv[3]);
		rect.pt1.y = atoi(argv[4]);
		rect.pt2.x = atoi(argv[5]);
		rect.pt2.y = atoi(argv[6]);
	}
	else
	{
		printf("Error!\n");
		printf("\t file\n");
		printf("\t file x y x1 y1 x2 y2\n");
		return;
	}

	// please check the input whether it is valid or not
	if((rect.pt1.x == rect.pt2.x) || (rect.pt1.y == rect.pt2.y))
	{
		printf("Input Error!\n");
		return;
	}

	res = PtInRect(pt, rect);
	switch (res) {
	case 1: printf("Point is in Rectangle\n"); break;
	case 2: printf("Point is NOT in Rectangle\n"); break;
	}
}

int PtInRect(Point pt, Rect rect)
{
	int max_x, max_y, min_x, min_y;

	max_x = (rect.pt1.x >= rect.pt2.x) ? rect.pt1.x : rect.pt2.x;
	min_x = (rect.pt1.x < rect.pt2.x) ? rect.pt1.x : rect.pt2.x;
	max_y = (rect.pt1.y >= rect.pt2.y) ? rect.pt1.x : rect.pt2.x;
	min_y = (rect.pt1.y < rect.pt2.y) ? rect.pt1.x : rect.pt2.x;

	if(pt.x<=max_x && pt.x>=min_x)
		if(pt.y<=max_y && pt.y>=min_y)
			return 1;
	return 2;
}