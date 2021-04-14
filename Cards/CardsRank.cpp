#include "CardsRank.h"


CCardsRank::CCardsRank(int nCount):m_vecRank(nCount)   // ���� ��������
{
	 m_pPoker = 0;   //  װ �����˿�
	m_hBmpWndBack = 0;   //  ���ڵı���ͼ
	m_hBmpCardsBack = 0;  //  �Ƶı���
}


CCardsRank::~CCardsRank(void)
{
	//  ɾ��  ���е��˿�
	delete[] m_pPoker;
	m_pPoker = NULL;

	//  ɾ��ͼƬ
	::DeleteObject(m_hBmpWndBack);
	m_hBmpWndBack = 0;
	::DeleteObject(m_hBmpCardsBack);
	m_hBmpCardsBack = 0;

	// ɾ��  ���е�����Ľڵ�
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
	//  ��ʾ  ����
	if(m_hBmpWndBack == 0)  //  ����Ĭ�ϵ�  ����ͼƬ
		m_hBmpWndBack = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_WND_BACK));

	HDC hTempDC = ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempDC,m_hBmpWndBack);
	::BitBlt(hMemDC,0,0,850,600,hTempDC,0,0,SRCCOPY);
	::DeleteDC(hTempDC);
	//------------------------------------------------------------------


	//------------------------------------------------------------------
	//  ��ʾ���е���
	if(m_hBmpCardsBack == 0)  //  ����Ĭ�ϵ�  �Ƶı���
		m_hBmpCardsBack = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_CARDS_BACK));

	for(size_t i=0;i<m_vecRank.size();i++)
	{
		list<Node*>::iterator ite = m_vecRank[i].begin();
		while(ite != m_vecRank[i].end())
		{
			//---------------------------------------------
			HDC hTempDC = ::CreateCompatibleDC(hMemDC);

			if((*ite)->bFlag == false)   //  ѡ��  �Ƶ� ����
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