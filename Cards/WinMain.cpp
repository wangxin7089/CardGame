#include <windows.h>
#include "CGameCtrl.h"
#include <time.h>


//HINSTANCE hIns;      //  ʵ���ľ��      ������Դ��ʱ����Ҫ������
//HWND      hwnd;      //  ���ھ��        �ʹ����й�ϵ��
//HDC       dc;        //  GDI ��ͼ        

PFUN_CREATE_OBJECT CGameCtrl::pfnCreateObject = NULL;

HINSTANCE g_hIns;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR pCmdLine,int nCmdShow)
{
	srand((unsigned int)time(0));
	g_hIns = hInstance;

	HBRUSH hBursh = ::CreateSolidBrush(RGB(0,0,255));   //  ������ˢ

	//  1.  ��ƴ���
	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.hbrBackground = hBursh;    //  ����
	wndclass.hCursor = 0;    //  ���
	wndclass.hIcon = 0;        //  ͼ��
	wndclass.hIconSm = 0;       //  ���� ���ϵ�Сͼ��
	wndclass.hInstance = hInstance;   //  ʵ�����
	wndclass.lpfnWndProc = WndProc;          //  ��Ϣ������
	wndclass.lpszClassName = "lele";        //  ע�� �����������
	wndclass.lpszMenuName = NULL;          
	wndclass.style = CS_HREDRAW|CS_VREDRAW;


	//  2.  ע�ᴰ��
	if(!RegisterClassEx(&wndclass))
	{
		::MessageBox(NULL,"ע��ʧ��","��ʾ",MB_OK);
		return 0;
	}
		
	//  3.  ����
	HWND hwnd = ::CreateWindow("lele","��_��",WS_OVERLAPPEDWINDOW,200,0,850,600+38,NULL,NULL,hInstance,0);
	if(hwnd == NULL)
	{
		::MessageBox(NULL,"����ʧ��","��ʾ",MB_OK);
		return 0;
	}


	//  4.  ��ʾ
	::ShowWindow(hwnd,SW_SHOW);
	
	//  5.  ��Ϣѭ��
	MSG msg;   //  װ��Ϣ��  �ṹ��
	while(::GetMessage(&msg,NULL,0,0))
	{
		//������Ϣ
		::TranslateMessage(&msg);
		//  �ַ�  ���ûص�����
		::DispatchMessage(&msg);
	}


	::DeleteObject(hBursh);    //  ɾ�� ��ͼ��  ��Դ
	return 0;
}


CGameCtrl* pCtrl = NULL;

//                      ��Ϣ���Ǹ����ڷ��͵ģ���Ϣ�����ƣ���Ϣ�������ݣ�WPARAM wParam, LPARAM lParam��
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		if( CGameCtrl::pfnCreateObject == NULL)
		{
			::MessageBox(NULL,"��Ϸ����ʧ��","��ʾ",MB_OK);
			::DestroyWindow(hwnd);
			::PostQuitMessage(0);
		}
		else
		{
			//  ������Ϸ�Ķ���
			pCtrl = (*(CGameCtrl::pfnCreateObject))();
			if(pCtrl != NULL)
			{
				//  ���þ��
				pCtrl->SetHandle(g_hIns,hwnd);
				//   ��ʼ��
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