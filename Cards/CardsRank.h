#pragma once
#include "oobject.h"
#include "Sys.h"
#include "Poker.h"

class CCardsRank :
	public COObject
{
public:
	CCardsRank(int nCount);
	~CCardsRank(void);
public:
	CPoker* m_pPoker;   //  装 几副扑克
	HBITMAP m_hBmpWndBack;   //  窗口的背景图
	HBITMAP m_hBmpCardsBack;  //  牌的背面
	vector<list<Node*>> m_vecRank;   //   所有的链表
public:
	void ShowRank(HDC hMemDC, HINSTANCE hIns);  // 显示所有的牌
public:
	virtual void InitCardsRank(HINSTANCE hIns)=0;   //  初始化
};

