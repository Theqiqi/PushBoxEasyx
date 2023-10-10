#ifndef _CALLBACK_HPP
#define _CALLBACK_HPP

#include <windows.h>


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void OnSize(HWND hwnd, UINT flag, int width, int height);
void InitializeWindow(HWND hwnd);
void PaintWindow(HWND hwnd);

#endif // PUSHBOX_HPP