#include <Windows.h>
#include <easyx.h>
#include "Message.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	initgraph(640, 480);

	MouseMessage* mouse;
	while (true)
	{
		PeekMouseMessage();
		if (IsKeyDown(VK_Q))
		{
			break;
		}
		mouse = GetMouseMessage();
	

		circle((int)mouse->x, (int)mouse->y, 10);
		Sleep(15);
	}

	closegraph();
	return 0;

}