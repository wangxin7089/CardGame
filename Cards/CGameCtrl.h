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
typedef CGameCtrl* (*PFUN_CREATE_OBJECT)();   //  ����һ������ָ�������


class CGameCtrl
{
public:
	static PFUN_CREATE_OBJECT pfnCreateObject;   //  ����һ������ ָ��ı���
protected:
	HINSTANCE m_hIns;
	HWND      m_hMainWnd;   //  ������
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
	virtual void OnCreateGame(){}                 //    WM_CREATE  ��ʼ����Ϸ
	virtual void OnGameDraw(){}                   //    WM_PAINT   ��Ϸ��ͼ
	virtual void OnGameRun(WPARAM nTimerID){}     //    WM_TIMER   ��Ϸ����
	virtual void OnKeyDown(WPARAM nKey){}         //    WM_KEYDOWN      
	virtual void OnKeyUp(WPARAM nKey){}           //    WM_KEYDOWN 
	virtual void OnLButtonDown(POINT point){}     //    WM_LBUTTONDOWN
	virtual void OnLButtonUp(POINT point){}       //    WM_LBUTTONDOWN
	virtual void OnMouseMove(POINT point){}       //    WM_LBUTTONDOWN
};



class Init
{
public:
	Init(PFUN_CREATE_OBJECT pfn)    // ͨ�����캯��  ��  ����ָ�븳ֵ
	{
		CGameCtrl::pfnCreateObject = pfn;;
	}
};

#endif//_CGAMECTRL_H_