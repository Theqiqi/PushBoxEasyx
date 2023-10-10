#include "CallBack.hpp"


int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{

    WNDCLASSEX wc = { };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszMenuName = L"MainMenu";
    wc.lpszClassName = L"MainWindowClass";
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

    /*
    1.注册 RegisterClassEx
    2.创建窗口 CreateWindowEx
    3.显示窗口 ShowWindow
    4.进入消息循环 GetMessage
    */
    // Register the window class for the main window. 
    if (!hPrevInstance)
    {

        if (!RegisterClassEx(&wc))
            return FALSE;
    }
    // Create the main window. 
    HWND hwnd = CreateWindowEx(
        0,                             // Optional window styles.
        wc.lpszClassName,               // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        // Size and position
        100,
        100,
        800,
        600,
        NULL,       // Parent window    
        (HMENU)NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    // If the main window cannot be created, terminate the application. 
    if (!hwnd)
        return FALSE;

    // Show the window and paint its contents. 
    ShowWindow(hwnd, SW_NORMAL);
    UpdateWindow(hwnd);

    BOOL bRet;
    MSG msg = { };
    // Start the message loop. 
    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if (bRet == -1)
        {
            // handle the error and possibly exit
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    // Return the exit code to the system. 
    return msg.wParam;

}
