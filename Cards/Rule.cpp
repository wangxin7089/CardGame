#include "Rule.h"


CRule::CRule(void)
{
	m_nGetCardsListID = -1;
}


CRule::~CRule(void)
{
}
bool CRule::ReceiveCards(POINT point, CCardsRank* pCardsRank, list<Node*>& lstCursor)
{
	//  �������е�����
	for(size_t i=0;i<pCardsRank->m_vecRank.size();i++)
	{
		//  �������ж�  ����   �ж��Ƿ��������
		if( this->IsReceiveCardsRule(point,i,pCardsRank,lstCursor) == true)
		{
			//  �� ��������  �� ��i����������
			pCardsRank->m_vecRank[i].splice(pCardsRank->m_vecRank[i].end(),lstCursor);
			//  ��������
			this->UpDatePos(pCardsRank,i);
			//  �����Ƶ� �ĸ������ ���һ�ŷ���
			if(m_nGetCardsListID != -1 && pCardsRank->m_vecRank[m_nGetCardsListID].empty() == false)
			{
				pCardsRank->m_vecRank[m_nGetCardsListID].back()->bFlag = true;
				m_nGetCardsListID = -1;
			}
			return true;
		}
	}
	return false;
}
void CRule::GetCards(POINT point, CCardsRank* pCardsRank, list<Node*>& lstCursor)
{
	for(size_t i=0;i<pCardsRank->m_vecRank.size();i++)
	{
		 //������������
		list<Node*>::reverse_iterator rev_ite = pCardsRank->m_vecRank[i].rbegin();
		while(rev_ite != pCardsRank->m_vecRank[i].rend())
		{ 
			//   �� ���� ���� �жϵ㵽�ĸ�����
			if(point.x >= (*rev_ite)->x && point.x <= (*rev_ite)->x+71
				&& point.y >= (*rev_ite)->y && point.y <= (*rev_ite)->y+96)
			{
				//  �ж��ǲ��� ����
				if((*rev_ite)->bFlag == true)
				{
					list<Node*>::iterator iteCursorPos = --(rev_ite.base());
					//   �ж� �Ƿ����������
					if( this->IsGetCardsRule(pCardsRank,i,iteCursorPos) == true)
					{
						//   ���� ����ƶ�
						lstCursor.splice(lstCursor.begin(),pCardsRank->m_vecRank[i],iteCursorPos,pCardsRank->m_vecRank[i].end());
						//  ��¼���ĸ��������õ�
						m_nGetCardsListID = i;
					}
				}
				return;
			}
			++rev_ite;
		}

	}
}
void CRule::RevertCards(CCardsRank* pCardsRank, list<Node*>& lstCursor)
{
	if(m_nGetCardsListID != -1)
	{
		//  �Żص�ԭ����λ��
		pCardsRank->m_vecRank[m_nGetCardsListID].splice(pCardsRank->m_vecRank[m_nGetCardsListID].end(),lstCursor);
		m_nGetCardsListID = -1;
	}
}