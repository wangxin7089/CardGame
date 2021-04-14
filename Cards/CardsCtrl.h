#pragma once
#include "cgamectrl.h"
#include "CardsRank.h"
#include "Rule.h"

class CCardsCtrl :
	public CGameCtrl
{
public:
	CCardsRank* m_pRank;   //  所有的链表
	CRule* m_pRule;    //  创建 规则

	list<Node*> m_lstCursorCards;  //  光标上的牌

	POINT pointMouseDown;
	POINT pointMouseMove;
public:
	DECLARE()
public:
	CCardsCtrl(void);
	~CCardsCtrl(void);
public:
	virtual void OnCreateGame();                 //    WM_CREATE  初始化游戏
	virtual void OnGameDraw();                   //    WM_PAINT   游戏绘图
	virtual void OnLButtonDown(POINT point);    //    WM_LBUTTONDOWN
	virtual void OnLButtonUp(POINT point);       //    WM_LBUTTONDOWN
	virtual void OnMouseMove(POINT point);       //    WM_LBUTTONDOWN
public:
	void ShowCursorCards(HDC hMemDC);   //  显示光表的链表
};

