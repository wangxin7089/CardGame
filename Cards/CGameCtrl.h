#pragma once
#ifndef _CGAMECTRL_H_
#define _CGAMECTRL_H_

#include <windows.h>

#define DECLARE() static CGameCtrl* CreateObject();


#define IMPLEMENT(ThisClass)\
	CGameCtrl* ThisClass::CreateObject()\
	{\
		return new ThisClass;\
	}\
	Init init##ThisClass(&ThisClass::CreateObject);







class CGameCtrl;
typedef CGameCtrl* (*PFUN_CREATE_OBJECT)();   //  定义一个函数指针的类型


class CGameCtrl
{
public:
	static PFUN_CREATE_OBJECT pfnCreateObject;   //  定义一个函数 指针的变量
protected:
	HINSTANCE m_hIns;
	HWND      m_hMainWnd;   //  主窗口
public:
	CGameCtrl()
	{
		m_hIns = 0;
		m_hMainWnd = 0;
	}
	virtual ~CGameCtrl()
	{
	
	}
public:
	void SetHandle(HINSTANCE hIns,HWND hWnd)
	{
		this->m_hIns = hIns;
		this->m_hMainWnd = hWnd;
	}
public:
	virtual void OnCreateGame(){}                 //    WM_CREATE  初始化游戏
	virtual void OnGameDraw(){}                   //    WM_PAINT   游戏绘图
	virtual void OnGameRun(WPARAM nTimerID){}     //    WM_TIMER   游戏运行
	virtual void OnKeyDown(WPARAM nKey){}         //    WM_KEYDOWN      
	virtual void OnKeyUp(WPARAM nKey){}           //    WM_KEYDOWN 
	virtual void OnLButtonDown(POINT point){}     //    WM_LBUTTONDOWN
	virtual void OnLButtonUp(POINT point){}       //    WM_LBUTTONDOWN
	virtual void OnMouseMove(POINT point){}       //    WM_LBUTTONDOWN
};



class Init
{
public:
	Init(PFUN_CREATE_OBJECT pfn)    // 通过构造函数  给  函数指针赋值
	{
		CGameCtrl::pfnCreateObject = pfn;;
	}
};

#endif//_CGAMECTRL_H_