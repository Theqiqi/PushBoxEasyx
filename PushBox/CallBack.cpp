#include "CallBack.hpp"
#include "PushBox.hpp"
#pragma comment(lib,"Msimg32.lib")//引入库Msimg32.lib TransparentBlt
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch (uMsg)
    {
    case WM_CREATE:
        InitializeWindow(hwnd);
        return 0;

    case WM_PAINT:
        // Paint the window's client area.
        PaintWindow(hwnd);
        return 0;
    case WM_LBUTTONDOWN:
    {
        MessageBeep(0);
    }
    case WM_SIZE:
        // Set the size and position of the window. 
        // Respond to the message:
    {
        int width = LOWORD(lParam);  // Macro to get the low-order word.
        int height = HIWORD(lParam); // Macro to get the high-order word.
        OnSize(hwnd, (UINT)wParam, width, height);
        return 0;
    }
    case WM_DESTROY:
        // Clean up window-specific data objects. 
        PostQuitMessage(0);
        return 0;
    case WM_COMMAND:
        MessageBox(hwnd, TEXT("what's wrong?"), L"message", MB_ICONINFORMATION);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void OnSize(HWND hwnd, UINT flag, int width, int height)
{
    // Handle resizing
    
}

void InitializeWindow(HWND hwnd)
{
    CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"OK",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        10,         // y position 
        100,        // Button width
        100,        // Button height
        hwnd,     // Parent window
        (HMENU)101,       //  menu.
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

}
void PaintWindow(HWND hwnd)
{
    //HDC hdc;
    //PAINTSTRUCT ps;
   // hdc = BeginPaint(hwnd, &ps);
    //FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
    //TextOut(hdc, 150, 150, L"This is a winow", 28);
    //EndPaint(hwnd, &ps);

    //接下来是代码区:

    //此段插入在InitInstance函数中 UpdateWindow(hWnd);代码的下一行！
    /*
    HDC mdc;
    HBITMAP bg;
    hdc = GetDC(hwnd); //获得显示上下文设备的句柄
    mdc = CreateCompatibleDC(hdc);//创建一个与指定设备兼容的内存设备上下文环境
    bg = (HBITMAP)LoadImage(NULL, TEXT("./image//lena.bmp"), IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);//加载一张指定了路径的bmp图片，此图片大小为63*128，用这个函数之前需要知道这张图的大小，分别填写在第4、5个参数里 ，第二个参数中填图片路径
    SelectObject(mdc, bg);//选入设备环境
    BitBlt(hdc, 0, 0, 800, 600, mdc, 0, 0, SRCAND);//显示这张图 参数一：填HDC类型的变量,
    */
    //拿到画图设备环境（拿到画布）DC
    HDC hdc = GetDC(hwnd);//hdc大小跟窗口一致
    //临时画布,缓冲 创建兼容DC
    HDC mdc = CreateCompatibleDC(hdc);//mdc大小不确定
    HDC bufdc = CreateCompatibleDC(hdc);//bufdc大小跟图片一致
    //创建空白位图,给mdc确定大小
    HBITMAP whiteBmp = CreateCompatibleBitmap(hdc, 800, 600);
    SelectObject(mdc, whiteBmp);//指定目标图片的同时指定了大小
    //拿到图片 （？，名称路径（BMP），宽，高，加载方式（从文件夹加载））
    HBITMAP hBG = (HBITMAP)LoadImage(NULL, L"image/background.bmp",
        IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);
    HBITMAP hTitle = (HBITMAP)LoadImage(NULL, L"image/title.bmp", IMAGE_BITMAP, 80, 36, LR_LOADFROMFILE);
    //把图片放到中间层（缓冲区）上
    SelectObject(bufdc, hBG);//指定目标图片的同时指定了大小
    //把buffdc的东西叠到mdc上,再拿到hdc画布上
    BitBlt(mdc, 0, 0, 800, 600, bufdc, 0, 0, SRCCOPY);
    SelectObject(bufdc, hTitle);
    //BitBlt(mdc,0,0,800,600,bufdc,0,0,SRCCOPY);//无法取出背景色
    //去除背景色（画布，起始x,起始y,宽高,缓冲区,起始x,起始y,宽，高,去除颜色(黑色)
    TransparentBlt(mdc, 320, 264, 80, 36, bufdc, 0, 0, 80, 36, RGB(0, 0, 0));//需要库Msimg32.lib
    BitBlt(hdc, 0, 0, 800, 600, mdc, 0, 0, SRCCOPY);
    //销毁自己创建的DC,释放系统提供的设备画布DC
    DeleteDC(bufdc);
    DeleteDC(mdc);
    ReleaseDC(hwnd, hdc);//需要窗口句柄和画布句柄

    //参数2、3：X、Y坐标，
    //参数4、5：图片大小
    //参数6：指向源设备环境的句柄。
    //参数7、8：指定图片左上角的X、Y逻辑坐标，没有特殊情况一般都填0
 
    
    /*
    for (;;)
    {
        //system("cls");
        gamedraw(hdc);
        if (jude())
        {
            level++;	//关卡最大数量是3
            if (level > 2)
            {
                //MessageBox(hwnd, TEXT("~~已通关~~~"), L"message", MB_ICONINFORMATION);
                //_getch();
                break;
            }

        }
        keyEvent();
        
    }*/

}

