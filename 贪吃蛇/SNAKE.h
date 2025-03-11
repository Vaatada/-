#define _CRT_SECURE_NO_WARNINGS 1
#include<locale.h>
#include<Windows.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<time.h>
#define fix_x 24
#define fix_y 5
#define KEY_PRESS(VK) ((GetAsyncKeyState(VK)&0x1) ? 1 : 0)
#define wall L'□'
#define body L'●'
#define food L'◆'
enum DIRECTION
{
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};
enum GAME_STATUS
{
	OK,
	KILL_BY_WALL,
	KILL_BY_YOURSELF,
	END
};
typedef struct NoodSlink
{
	int x;
	int y;
	struct NoodSlink* Next;
}NoodSlink, * NeedSlink;
typedef struct Snake
{
	NeedSlink _psnake;//指向蛇头
	NeedSlink _pfood;//指向食物
	enum DIRECTION _dire; //蛇的方向
	enum GAME_STATUS _status;//蛇的状态
	int _food_weight;//食物的单分
	int _score;//总分
	int _speed;//速度
}Snake, * pSnake;
void GameStart(pSnake ps);
void WelcometoGame();
void SetPos(short x, short y);
void CreatMap();
void CreatSnake(pSnake ps);
void CreatFood(pSnake ps);
void GameRun(pSnake ps);
void HelpInfor();
void SnakeMove(pSnake ps);
int nextisfood(NeedSlink nextword, pSnake ps);
void EatFood(NeedSlink nextword, pSnake ps);
void pause();
void NoFood(NeedSlink nextword, pSnake ps);
void Killbywall(pSnake ps);
void Killbyself(pSnake ps);
void GameEnd(pSnake ps);
void test(); 
