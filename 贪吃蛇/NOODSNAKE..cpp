#include "SNAKE.h"

int main()
{
	setlocale(LC_ALL, "");//���ػ�
	NeedSlink psnake = NULL;//������
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
		//1.��ʼ����
		Snake snake = { 0 };// ��ʼ����(�ߵ�ͷ���ߵ�ʳ��ٶȣ�����״̬��ʳ��÷֣��ܵ÷�)
		//2.��ʼ��Ϸ����
		GameStart(&snake);
		//2.������Ϸ
		GameRun(&snake);
		//3.������Ϸ
		GameEnd(&snake);
		SetPos(20, 15);
		printf("������һ���� ? (Y/N)");
		ch = getchar();
		getchar();
	} while (ch == 'Y' || ch == 'y');
	SetPos(0, 27);
}