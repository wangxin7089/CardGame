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
	//  遍历所有的链表
	for(size_t i=0;i<pCardsRank->m_vecRank.size();i++)
	{
		//  让子类判断  坐标   判断是否可以拿牌
		if( this->IsReceiveCardsRule(point,i,pCardsRank,lstCursor) == true)
		{
			//  把 光标的链表  和 第i个链表链接
			pCardsRank->m_vecRank[i].splice(pCardsRank->m_vecRank[i].end(),lstCursor);
			//  更新坐标
			this->UpDatePos(pCardsRank,i);
			//  把拿牌的 哪个链表的 最后一张翻牌
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
		 //遍历所有链表
		list<Node*>::reverse_iterator rev_ite = pCardsRank->m_vecRank[i].rbegin();
		while(rev_ite != pCardsRank->m_vecRank[i].rend())
		{ 
			//   用 光标的 坐标 判断点到哪个牌上
			if(point.x >= (*rev_ite)->x && point.x <= (*rev_ite)->x+71
				&& point.y >= (*rev_ite)->y && point.y <= (*rev_ite)->y+96)
			{
				//  判断是不是 正面
				if((*rev_ite)->bFlag == true)
				{
					list<Node*>::iterator iteCursorPos = --(rev_ite.base());
					//   判断 是否可以拿起来
					if( this->IsGetCardsRule(pCardsRank,i,iteCursorPos) == true)
					{
						//   跟着 光标移动
						lstCursor.splice(lstCursor.begin(),pCardsRank->m_vecRank[i],iteCursorPos,pCardsRank->m_vecRank[i].end());
						//  记录在哪个链表上拿的
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
		//  放回到原来的位置
		pCardsRank->m_vecRank[m_nGetCardsListID].splice(pCardsRank->m_vecRank[m_nGetCardsListID].end(),lstCursor);
		m_nGetCardsListID = -1;
	}
}