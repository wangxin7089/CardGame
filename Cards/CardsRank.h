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
	CPoker* m_pPoker;   //  װ �����˿�
	HBITMAP m_hBmpWndBack;   //  ���ڵı���ͼ
	HBITMAP m_hBmpCardsBack;  //  �Ƶı���
	vector<list<Node*>> m_vecRank;   //   ���е�����
public:
	void ShowRank(HDC hMemDC, HINSTANCE hIns);  // ��ʾ���е���
public:
	virtual void InitCardsRank(HINSTANCE hIns)=0;   //  ��ʼ��
};

