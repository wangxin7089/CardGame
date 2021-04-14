#pragma once
#include "cgamectrl.h"
#include "CardsRank.h"
#include "Rule.h"

class CCardsCtrl :
	public CGameCtrl
{
public:
	CCardsRank* m_pRank;   //  ���е�����
	CRule* m_pRule;    //  ���� ����

	list<Node*> m_lstCursorCards;  //  ����ϵ���

	POINT pointMouseDown;
	POINT pointMouseMove;
public:
	DECLARE()
public:
	CCardsCtrl(void);
	~CCardsCtrl(void);
public:
	virtual void OnCreateGame();                 //    WM_CREATE  ��ʼ����Ϸ
	virtual void OnGameDraw();                   //    WM_PAINT   ��Ϸ��ͼ
	virtual void OnLButtonDown(POINT point);    //    WM_LBUTTONDOWN
	virtual void OnLButtonUp(POINT point);       //    WM_LBUTTONDOWN
	virtual void OnMouseMove(POINT point);       //    WM_LBUTTONDOWN
public:
	void ShowCursorCards(HDC hMemDC);   //  ��ʾ��������
};

