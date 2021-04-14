#include "CardsRank.h"


CCardsRank::CCardsRank(int nCount):m_vecRank(nCount)   // 创建 多少链表
{
	 m_pPoker = 0;   //  装 几副扑克
	m_hBmpWndBack = 0;   //  窗口的背景图
	m_hBmpCardsBack = 0;  //  牌的背面
}


CCardsRank::~CCardsRank(void)
{
	//  删除  所有的扑克
	delete[] m_pPoker;
	m_pPoker = NULL;

	//  删除图片
	::DeleteObject(m_hBmpWndBack);
	m_hBmpWndBack = 0;
	::DeleteObject(m_hBmpCardsBack);
	m_hBmpCardsBack = 0;

	// 删除  所有的链表的节点
	for(size_t i=0;i<m_vecRank.size();i++)
	{
		list<Node*>::iterator ite = m_vecRank[i].begin();
		while(ite != m_vecRank[i].end())
		{
			delete(*ite);
			++ite;
		}
	}
}
void CCardsRank::ShowRank(HDC hMemDC, HINSTANCE hIns)
{
	//------------------------------------------------------------------
	//  显示  背景
	if(m_hBmpWndBack == 0)  //  加载默认的  背景图片
		m_hBmpWndBack = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_WND_BACK));

	HDC hTempDC = ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempDC,m_hBmpWndBack);
	::BitBlt(hMemDC,0,0,850,600,hTempDC,0,0,SRCCOPY);
	::DeleteDC(hTempDC);
	//------------------------------------------------------------------


	//------------------------------------------------------------------
	//  显示所有的牌
	if(m_hBmpCardsBack == 0)  //  加载默认的  牌的背面
		m_hBmpCardsBack = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_CARDS_BACK));

	for(size_t i=0;i<m_vecRank.size();i++)
	{
		list<Node*>::iterator ite = m_vecRank[i].begin();
		while(ite != m_vecRank[i].end())
		{
			//---------------------------------------------
			HDC hTempDC = ::CreateCompatibleDC(hMemDC);

			if((*ite)->bFlag == false)   //  选入  牌的 背面
				::SelectObject(hTempDC,m_hBmpCardsBack);
			else
				::SelectObject(hTempDC,(*ite)->pCards->m_hBmpCards);

			::BitBlt(hMemDC,(*ite)->x,(*ite)->y,71,96,hTempDC,0,0,SRCCOPY);
			::DeleteDC(hTempDC);
			//---------------------------------------------
			++ite;
		}
	}
	//------------------------------------------------------------------
}