#include <windows.h>
#include "CGameCtrl.h"
#include <time.h>


//HINSTANCE hIns;      //  实例的句柄      加载资源的时候需要这个句柄
//HWND      hwnd;      //  窗口句柄        和窗口有关系的
//HDC       dc;        //  GDI 绘图        

PFUN_CREATE_OBJECT CGameCtrl::pfnCreateObject = NULL;

HINSTANCE g_hIns;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR pCmdLine,int nCmdShow)
{
	srand((unsigned int)time(0));
	g_hIns = hInstance;

	HBRUSH hBursh = ::CreateSolidBrush(RGB(0,0,255));   //  创建画刷

	//  1.  设计窗口
	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.hbrBackground = hBursh;    //  背景
	wndclass.hCursor = 0;    //  光标
	wndclass.hIcon = 0;        //  图标
	wndclass.hIconSm = 0;       //  窗口 左上的小图标
	wndclass.hInstance = hInstance;   //  实例句柄
	wndclass.lpfnWndProc = WndProc;          //  消息处理函数
	wndclass.lpszClassName = "lele";        //  注册 窗口类的名字
	wndclass.lpszMenuName = NULL;          
	wndclass.style = CS_HREDRAW|CS_VREDRAW;


	//  2.  注册窗口
	if(!RegisterClassEx(&wndclass))
	{
		::MessageBox(NULL,"注册失败","提示",MB_OK);
		return 0;
	}
		
	//  3.  创建
	HWND hwnd = ::CreateWindow("lele","→_→",WS_OVERLAPPEDWINDOW,200,0,850,600+38,NULL,NULL,hInstance,0);
	if(hwnd == NULL)
	{
		::MessageBox(NULL,"创建失败","提示",MB_OK);
		return 0;
	}


	//  4.  显示
	::ShowWindow(hwnd,SW_SHOW);
	
	//  5.  消息循环
	MSG msg;   //  装消息的  结构体
	while(::GetMessage(&msg,NULL,0,0))
	{
		//翻译消息
		::TranslateMessage(&msg);
		//  分发  调用回调函数
		::DispatchMessage(&msg);
	}


	::DeleteObject(hBursh);    //  删除 绘图的  资源
	return 0;
}


CGameCtrl* pCtrl = NULL;

//                      消息给那个窗口发送的，消息的名称，消息带的数据（WPARAM wParam, LPARAM lParam）
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		if( CGameCtrl::pfnCreateObject == NULL)
		{
			::MessageBox(NULL,"游戏创建失败","提示",MB_OK);
			::DestroyWindow(hwnd);
			::PostQuitMessage(0);
		}
		else
		{
			//  创建游戏的对象
			pCtrl = (*(CGameCtrl::pfnCreateObject))();
			if(pCtrl != NULL)
			{
				//  设置句柄
				pCtrl->SetHandle(g_hIns,hwnd);
				//   初始化
				pCtrl->OnCreateGame();
			}
		}
		break;
	case WM_PAINT:
		if(pCtrl != NULL)
			pCtrl->OnGameDraw();
		break;
	case WM_TIMER:
		if(pCtrl != NULL)
			pCtrl->OnGameRun(wParam);
		break;
	case WM_KEYDOWN:
		if(pCtrl != NULL)
			pCtrl->OnKeyDown(wParam);
		break;
	case WM_KEYUP:
		if(pCtrl != NULL)
			pCtrl->OnKeyUp(wParam);
		break;
	case WM_LBUTTONDOWN:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			if(pCtrl != NULL)
				pCtrl->OnLButtonDown(point);
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			if(pCtrl != NULL)
				pCtrl->OnLButtonUp(point);
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			if(pCtrl != NULL)
				pCtrl->OnMouseMove(point);
		}
		break;
	case WM_CLOSE:
		delete pCtrl;
		pCtrl = 0;
		::PostQuitMessage(0);
		break;
	}
	return DefWindowProc( hwnd,  uMsg,  wParam,  lParam);
}