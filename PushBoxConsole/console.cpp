#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <Locale.h>
//推箱子的元素：空地0 墙1 目的地2 箱子3 玩家4 箱子在目的地 5 玩家在目的地 6
enum Mine
{
	SPACE,	//空地
	WALL,	//墙
	DEST,	//目的地
	BOX,	//箱子
	PLAYER	//玩家
};
//当前关卡
int level = 0;
//定义一个二维数组，用来表示退箱子的地图
int map[3][10][10] =
{
	{
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,0,0,0,0},
	{0,0,0,1,2,1,1,1,1,0},
	{0,1,1,1,3,3,0,2,1,0},
	{0,1,2,3,4,0,1,1,1,0},
	{0,1,1,1,1,3,1,0,0,0},
	{0,0,0,0,1,2,1,0,0,0},
	{0,0,0,0,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
	},
	{
	{0,0,0,0,0,0,0,0,0,0},
	{1,1,1,0,0,0,1,1,1,0},
	{1,0,0,1,0,1,0,0,1,0},
	{1,2,3,0,1,0,3,2,1,0},
	{0,1,0,0,4,0,0,1,0,0},
	{0,0,1,0,3,0,1,0,0,0},
	{0,0,0,1,2,1,0,0,0,0},
	{0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
	},
	{
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
	}
};

void gamedraw()
{
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			switch (map[level][i][k])
			{
			case SPACE:
				printf(" ");
				break;
			case WALL:
				printf("▩");
				break;
			case DEST:
				printf("☆");
				break;
			case BOX:
				printf("☐");
				break;
			case PLAYER:
				printf("큐");
				break;
			case PLAYER + DEST:
				printf("❤");
				break;
			case BOX + DEST:
				printf("★");
				break;
			}

		}
		printf("\n");
	}
}
//按键消息处理
void keyEvent()
{
	int i = 0, k = 0;
	//获取玩家位置
	for (i = 0; i < 10; i++)
	{
		for (k = 0; k < 10; k++)
		{
			if (map[level][i][k] == PLAYER || map[level][i][k] == PLAYER + DEST)
			{
				goto end;
			}
		}
	}
end:;
	//获取键盘按键消息
	char ch = _getch();
	switch (ch)
	{
	case 72:
	case 'w':
	case 'W':
		//判断移动
		if (map[level][i - 1][k] == SPACE || map[level][i - 1][k] == DEST)
		{
			map[level][i - 1][k] += PLAYER;
			map[level][i][k] -= PLAYER;
		}
		else if (map[level][i - 1][k] == BOX || map[level][i - 1][k] == BOX + DEST)
		{
			if (map[level][i - 2][k] == SPACE || map[level][i - 2][k] == DEST)
			{
				//把箱子移动到前面一个位置
				map[level][i - 2][k] += BOX;
				//让原来的箱子，减去箱子，让后加上玩家
				map[level][i - 1][k] = map[level][i - 1][k] - BOX + PLAYER;
				//让玩家在原来的位置消失
				map[level][i][k] -= PLAYER;
			}
		}
		break;
	case 80:
	case 's':
	case 'S':
		if (map[level][i + 1][k] == SPACE || map[level][i + 1][k] == DEST)
		{
			map[level][i + 1][k] += PLAYER;
			map[level][i][k] -= PLAYER;
		}
		else if (map[level][i + 1][k] == BOX || map[level][i + 1][k] == BOX + DEST)
		{
			if (map[level][i + 2][k] == SPACE || map[level][i + 2][k] == DEST)
			{
				//把箱子移动到前面一个位置
				map[level][i + 2][k] += BOX;
				//让原来的箱子，减去箱子，让后加上玩家
				map[level][i + 1][k] = map[level][i + 1][k] - BOX + PLAYER;
				//让玩家在原来的位置消失
				map[level][i][k] -= PLAYER;
			}
		}
		break;
	case 75:
	case 'a':
	case 'A':
		if (map[level][i][k - 1] == SPACE || map[level][i][k - 1] == DEST)
		{
			map[level][i][k - 1] += PLAYER;
			map[level][i][k] -= PLAYER;
		}
		else if (map[level][i][k - 1] == BOX || map[level][i][k - 1] == BOX + DEST)
		{
			if (map[level][i][k - 2] == SPACE || map[level][i][k - 2] == DEST)
			{
				//把箱子移动到前面一个位置
				map[level][i][k - 2] += BOX;
				//让原来的箱子，减去箱子，让后加上玩家
				map[level][i][k - 1] = map[level][i][k - 1] - BOX + PLAYER;
				//让玩家在原来的位置消失
				map[level][i][k] -= PLAYER;
			}
		}
		break;
	case 77:
	case 'd':
	case 'D':
		if (map[level][i][k + 1] == SPACE || map[level][i][k + 1] == DEST)
		{
			map[level][i][k + 1] += PLAYER;
			map[level][i][k] -= PLAYER;
		}
		else if (map[level][i][k + 1] == BOX || map[level][i][k + 1] == BOX + DEST)
		{
			if (map[level][i][k + 2] == SPACE || map[level][i][k + 2] == DEST)
			{
				//把箱子移动到前面一个位置
				map[level][i][k + 2] += BOX;
				//让原来的箱子，减去箱子，让后加上玩家
				map[level][i][k + 1] = map[level][i][k + 1] - BOX + PLAYER;
				//让玩家在原来的位置消失
				map[level][i][k] -= PLAYER;
			}
		}
		break;
	}

}
//判断是否过关
bool jude()
{
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			if (map[level][i][k] == BOX)
			{
				return	false;
			}
		}
	}
	return true;
}
int main()
{
	//setlocale(LC_ALL, NULL); // c语言函数,本地化语言设置为中文，否则中文乱码
	//调整窗口大小
	system("mode con lines=10 cols=25");
	for (;;)
	{
		system("cls");
		gamedraw();
		if (jude())
		{
			level++;	//关卡最大数量是3
			if (level > 2)
			{
				printf("~~~已通关~~~");
				_getch();
				break;
			}

		}
		keyEvent();

	}
	getchar(); //不让程序退出
	return 0;
}