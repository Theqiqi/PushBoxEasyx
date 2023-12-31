#include <easyx.h>
#include "Message.h"

static MouseMessage mouse;

void PeekMouseMessage()
{
	ExMessage msg;

	while (peekmessage(&msg, EX_MOUSE))
	{
		if (msg.message == WM_MOUSEMOVE)
		{
			mouse.x = msg.x;
			mouse.y = msg.y;
		}
		else if (msg.message == WM_LBUTTONUP)
		{
			mouse.isUp = true;
			mouse.isDown = false;
		}
		else if (msg.message == WM_LBUTTONDOWN)
		{
			mouse.isUp = false;
			mouse.isDown = true;
		}
	}
}

bool IsKeyDown(int key)
{
	return GetAsyncKeyState(key);
}
MouseMessage* GetMouseMessage()
{
	return &mouse;
}