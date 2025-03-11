#include "SNAKE.h"

int main()
{
	setlocale(LC_ALL, "");//本地化
	NeedSlink psnake = NULL;//创建蛇
	srand((unsigned int)time(NULL));
	test();
	return 0;
}
void test()
{
	int ch = 0;
	do
	{
		system("cls");
		//1.初始化蛇
		Snake snake = { 0 };// 初始化蛇(蛇的头，蛇的食物，速度，方向，状态，食物得分，总得分)
		//2.初始游戏界面
		GameStart(&snake);
		//2.进行游戏
		GameRun(&snake);
		//3.结束游戏
		GameEnd(&snake);
		SetPos(20, 15);
		printf("想再来一局吗 ? (Y/N)");
		ch = getchar();
		getchar();
	} while (ch == 'Y' || ch == 'y');
	SetPos(0, 27);
}