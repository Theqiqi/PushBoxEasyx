#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <Locale.h>
#include <graphics.h>
bool IsKeyDown(int key);


#define VK_A	0x41
#define VK_B	0x42
#define VK_C	0x43
#define VK_D	0x44
#define VK_E	0x45
#define VK_F	0x46
#define VK_G	0x47
#define VK_H	0x48
#define VK_I	0x49
#define VK_J	0x4A
#define VK_K	0x4B
#define VK_L	0x4C
#define VK_M	0x4D
#define VK_N	0x4E
#define VK_O	0x4F
#define VK_P	0x50
#define VK_Q	0x51
#define VK_R	0x52
#define VK_S	0x53
#define VK_T	0x54
#define VK_U	0x55
#define VK_V	0x56
#define VK_W	0x57
#define VK_X	0x58
#define VK_Y	0x59
#define VK_Z	0x5A

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
	{0,1,1,1,1,1,1,1,1,0},
	{0,1,0,0,0,2,0,0,1,0},
	{0,1,2,0,3,1,0,0,1,0},
	{0,1,0,1,0,0,1,2,1,0},
	{0,1,0,3,4,0,0,3,1,0},
	{0,1,0,0,0,0,0,0,1,0},
	{0,1,0,0,0,0,0,0,1,0},
	{0,1,0,0,0,0,0,0,1,0},
	{0,1,2,0,0,0,0,0,1,0},
	{0,1,1,1,1,1,1,1,1,0}
	}
};

IMAGE img_all[6];
void loadImg()
{
	//保存图片


	for (int i = 0; i < 6; i++)
	{
		wchar_t file[20] = L"";
		wsprintf(file, _T("./images/%d.jpg"), i);
		loadimage(img_all + i, file, 64, 64);


	}

}
void gamedraw()
{
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			int x = k * 64;
			int y = i * 64;
			switch (map[level][i][k])
			{
			case SPACE:
				putimage(x, y, img_all);
				break;
			case WALL:
				putimage(x, y, img_all + 1);
				break;
			case DEST:
				putimage(x, y, img_all + 2);
				break;
			case BOX:
				putimage(x, y, img_all + 3);
				break;
			case PLAYER:
				putimage(x, y, img_all + 4);
				break;
			case PLAYER + DEST:
				putimage(x, y, img_all);
				break;
			case BOX + DEST:
				putimage(x, y, img_all + 5);
				break;
			}

		}

	}
}
//按键消息处理

int GetChoice(int* keys, size_t size)
{
	size_t n;

	Sleep(200);
	for (n = 0; n < size; n++)
	{
		
		if (GetAsyncKeyState(keys[n]))


			return keys[n];
	}

	return 0;
}

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
	int keys[] = { 'W','S','A','D' };
	int cKey = GetChoice(keys, 4);
	switch (cKey)
	{
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
	//Sleep(100);
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

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	initgraph(10 * 64, 10 * 64);


	//circle(200, 200, 100);
	loadImg();
	;	//setlocale(LC_ALL, NULL); // c语言函数,本地化语言设置为中文，否则中文乱码
		//调整窗口大小
	//system("mode con lines=10 cols=25");
	for (;;)
	{
		//system("cls");
		gamedraw();
		if (jude())
		{
			level++;	//关卡最大数量是3
			if (level > 2)
			{
				settextcolor(BLACK);
				settextstyle(25, 0, L"微软雅黑");
				setbkmode(TRANSPARENT);
				outtextxy(250, 250, L"~~~恭喜通关~~~");
				//_getch();
				if (GetAsyncKeyState('Q'))break;

			}

		}

		keyEvent();

	}


	//getchar(); //不让程序退出

}

