#define _CRT_SECURE_NO_WARNINGS 1
#include "SNAKE.h"
void GameStart(pSnake ps)
{
	//改主界面名字，大小
	system("mode con cols=100 lines=30 ");
	system("title 贪吃蛇");
	//获得句柄，隐藏光标
	HANDLE houtput = NULL;
	//获取标准输出的句柄(⽤来标识不同设备的数值) 
	houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(houtput, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标 
	SetConsoleCursorInfo(houtput, &CursorInfo);//设置控制台光标状态
	WelcometoGame();//欢迎界面
	CreatMap();//地图绘制
	CreatSnake(ps);//蛇数据创建
	CreatFood(ps);//食物创建
}
void CreatFood(pSnake ps)
{
	int x = 0;
	int y = 0;
again:
	do
	{
		x = rand() % 53 + 2;
		y = rand() % 25 + 1;
	} while (x % 2 != 0);//x是2的倍数 x:2-54 y:1-25
	NeedSlink cur = ps->_psnake;
	while (cur)
	{
		if (x == cur->x && y == cur->y)
		{
			goto again;
		}
		cur = cur->Next;
	}
	NeedSlink pFood = (NeedSlink)malloc(sizeof(NoodSlink));
	if (pFood == NULL)
	{
		perror("CreatFood()::malloc()");
		return;
	}
	pFood->x = x;
	pFood->y = y;
	pFood->Next = NULL;
	ps->_pfood = pFood;
	SetPos(x, y);
	wprintf(L"%lc", food);
}
void CreatSnake(pSnake ps)
{
	int i = 0;
	NeedSlink cur = NULL;
	for (i = 0; i < 5; i++)//创建5个链表
	{
		cur = (NeedSlink)malloc(sizeof(NoodSlink));
		if (cur == NULL)
		{
			perror("CreatSnake::malloc");
			
		}
		cur->Next = NULL;
		cur->x = fix_x + (i * 2);
		cur->y = fix_y;
		if (ps->_psnake == NULL)
		{
			ps->_psnake = cur;
		}
		else
		{
			cur->Next = ps->_psnake;
			ps->_psnake = cur;
		}
	}
	while (cur)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", body);
		cur = cur->Next;
	}
	ps->_dire = RIGHT;//右走
	ps->_score = 0;//初始得分
	ps->_food_weight = 10;//食物得分
	ps->_speed = 200;//速度参数
	ps->_status = OK;//蛇的状态
}
void WelcometoGame()
{
	SetPos(34, 10);
	printf("欢 迎 来 到 贪 吃 蛇 游 戏");
	SetPos(38, 20);
	system("pause");
	system("cls");
	SetPos(30, 10);
	printf("用↑ ↓ ← →来控制蛇的方向,F3加速，F4减速");
	SetPos(40, 12);
	printf("注意加速分数更高");
	SetPos(40, 20);
	system("pause");
	system("cls");
}
void CreatMap()
{
	int i = 0;
	for (i = 0; i < 58; i += 2)
	{
		wprintf(L"%lc", wall);
	}
	SetPos(0, 26);
	for (i = 0; i < 58; i += 2)
	{
		wprintf(L"%lc", wall);
	}
	for (i = 1; i < 26; i++)
	{
		SetPos(0, i);
		wprintf(L"%lc", wall);
	}
	for (i = 1; i < 26; i++)
	{
		SetPos(56, i);
		wprintf(L"%lc", wall);
	}
}
void SetPos(short x, short y)
{
	COORD pos = { x, y };//设置光标的坐标
	HANDLE houtput = NULL;
	//获取标准输出的句柄(⽤来标识不同设备的数值) 
	houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	//设置标准输出上光标的位置为pos 
	SetConsoleCursorPosition(houtput, pos);
}
void GameRun(pSnake ps)
{
	HelpInfor();
	do
	{
		SetPos(64, 4);
		printf("总分数:%d", ps->_score);
		SetPos(64, 8);
		printf("当前食物的分数：%2d", ps->_food_weight);
		if (KEY_PRESS(VK_UP) && ps->_dire != DOWN)
		{
			ps->_dire = UP;
		}
		else if (KEY_PRESS(VK_DOWN) && ps->_dire != UP)
		{
			ps->_dire = DOWN;
		}
		else if (KEY_PRESS(VK_LEFT) && ps->_dire != RIGHT)
		{
			ps->_dire = LEFT;
		}
		else if (KEY_PRESS(VK_RIGHT) && ps->_dire != LEFT)
		{
			ps->_dire = RIGHT;
		}
		else if (KEY_PRESS(VK_SPACE))
		{
			pause();
		}
		else if (KEY_PRESS(VK_ESCAPE))
		{
			ps->_status = END;
			break;
		}
		else if (KEY_PRESS(VK_F3))
		{
			if (ps->_speed > 80)
			{
				ps->_speed -= 30;
				ps->_food_weight += 2;
			}
		}
		else if (KEY_PRESS(VK_F4))
		{
			if (ps->_food_weight > 2)
			{
				ps->_speed += 30;
				ps->_food_weight -= 2;
			}
		}
		SnakeMove(ps);
		Sleep(ps->_speed);
	} while (ps->_status == OK);
}
void HelpInfor()
{
	SetPos(60, 13);
	printf("不能撞墙，不能咬到自己");
	SetPos(60, 14);
	printf("用↑ ↓ ← →来控制蛇的方向");
	SetPos(60, 15);
	printf("F3加速，F4减速");
	SetPos(60, 16);
	printf("ESC 退出游戏，空格 暂停游戏");

}
void pause()
{
	while (1)
	{
		Sleep(200);
		if (KEY_PRESS(VK_SPACE))
		{
			break;
		}
	}
}
void SnakeMove(pSnake ps)
{
	NeedSlink nextword = (NeedSlink)malloc(sizeof(NoodSlink));
	if (nextword == NULL)
	{
		perror("nextword:");
		return;
	}
	switch (ps->_dire)
	{
	case UP:
		nextword->x = ps->_psnake->x;
		nextword->y = ps->_psnake->y - 1;
		break;
	case DOWN:
		nextword->x = ps->_psnake->x;
		nextword->y = ps->_psnake->y + 1;
		break;
	case LEFT:
		nextword->x = ps->_psnake->x - 2;
		nextword->y = ps->_psnake->y;
		break;
	case RIGHT:
		nextword->x = ps->_psnake->x + 2;
		nextword->y = ps->_psnake->y;
		break;
	}
	//检测下一个坐标是不是食物
	if (nextisfood(nextword, ps))
	{
		EatFood(nextword, ps);
	}
	else
	{
		NoFood(nextword, ps);
	}
	//检查蛇是否撞墙 撞到自己 
	Killbywall(ps);
	Killbyself(ps);
}
int nextisfood(NeedSlink nextword, pSnake ps)
{
	if ((ps->_pfood->x == nextword->x) && (ps->_pfood->y == nextword->y))
		return 1;
	else
		return 0;
}
void EatFood(NeedSlink nextword, pSnake ps)
{
	ps->_pfood->Next = ps->_psnake;
	ps->_psnake = ps->_pfood;
	free(nextword);
	nextword = NULL;
	NeedSlink cur = ps->_psnake;
	while (cur)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", body);
		cur = cur->Next;
	}
	ps->_score += ps->_food_weight;
	CreatFood(ps);
}
void NoFood(NeedSlink nextword, pSnake ps)
{
	nextword->Next = ps->_psnake;
	ps->_psnake = nextword;
	NeedSlink cur = ps->_psnake;
	while (cur->Next->Next != NULL)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", body);
		cur = cur->Next;
	}
	SetPos(cur->Next->x, cur->Next->y);
	printf("  ");
	free(cur->Next);
	cur->Next = NULL;

}
void Killbywall(pSnake ps)
{
	if (ps->_psnake->x == 0 || ps->_psnake->x == 56
		|| ps->_psnake->y == 0 || ps->_psnake->y == 26)
	{
		ps->_status = KILL_BY_WALL;
	}
}
void Killbyself(pSnake ps)
{
	NeedSlink cur = ps->_psnake->Next;
	while (cur)
	{
		if (cur->x == ps->_psnake->x && cur->y == ps->_psnake->y)
		{
			ps->_status = KILL_BY_YOURSELF;
			break;
		}
		cur = cur->Next;
	}
}
void GameEnd(pSnake ps)
{
	SetPos(24, 12);
	switch (ps->_status)
	{
	case END:
		printf("您主动结束游戏了\n");
		break;
	case KILL_BY_WALL:
		printf("很遗憾，您撞墙了\n");
		break;
	case KILL_BY_YOURSELF:
		printf("您吃到自己辣\n");
		break;
	}
	SetPos(0, 27);
	NeedSlink cur = ps->_psnake;
	while (cur)
	{
		NeedSlink pn = cur;
		cur = cur->Next;
		free(pn);
	}
}