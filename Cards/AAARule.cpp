#include "AAARule.h"

IMPLEMENT_DYNCREATE(CAAARule,CRule)
CAAARule::CAAARule(void)
{

}


CAAARule::~CAAARule(void)
{
}

  //拿牌的规则
bool CAAARule::IsGetCardsRule(CCardsRank* pCardsRank, int nlstID, list<Node*>::iterator iteCursorPos)
{
	
//	list<Node*>::iterator ite=pCardsRank->m_vecRank[nlstID].begin();
	int num=(*iteCursorPos)->pCards->m_nCardsNum;
	while(iteCursorPos != pCardsRank->m_vecRank[nlstID].end())
	{
		if((*iteCursorPos)->pCards->m_nCardsNum != num)
		{
			return false;
		}
		--num;
		++iteCursorPos;
	}

	return true;
}
	//  发牌
bool CAAARule::IsOpenCards(POINT point, CCardsRank* pCardsRank)
{
	if(!pCardsRank->m_vecRank[10].empty())
	{
		if(point.x >= pCardsRank->m_vecRank[10].back()->x&&point.x <= pCardsRank->m_vecRank[10].back()->x+71
			&&point.y >= pCardsRank->m_vecRank[10].back()->y&&point.y<= pCardsRank->m_vecRank[10].back()->y+96 )
		{
			for(int i=0;i<10;i++)
			{
				if( pCardsRank->m_vecRank[i].empty())
				{
					return false;
				}
			}
			return true;
		}
	}
	return false;
}
void CAAARule::OpenCards(CCardsRank* pCardsRank)
{
		for(int i=0;i<10;i++)
		{
			pCardsRank->m_vecRank[10].back()->bFlag=true;
			pCardsRank->m_vecRank[10].back()->x=pCardsRank->m_vecRank[i].back()->x;
			pCardsRank->m_vecRank[10].back()->y=pCardsRank->m_vecRank[i].back()->y+20;
			pCardsRank->m_vecRank[i].push_back(pCardsRank->m_vecRank[10].back());
			pCardsRank->m_vecRank[10].pop_back();
		}

}
	//  接收牌的规则
bool CAAARule::IsReceiveCardsRule(POINT point, int nlstID, CCardsRank* pCardsRank, list<Node*>& lstCursorCards)
{
	if(pCardsRank->m_vecRank[nlstID].empty())
	{
		if(point.x >= 10+81*nlstID&&point.x <= 10+81*nlstID
			&&point.y >= 20&&point.y <= 20+96)
		{
			return true;
		}
	}else
	{
		if(point.x >= pCardsRank->m_vecRank[nlstID].back()->x&&point.x <= pCardsRank->m_vecRank[nlstID].back()->x+71
			&&point.y >= pCardsRank->m_vecRank[nlstID].back()->y&&point.y<= pCardsRank->m_vecRank[nlstID].back()->y+96)
		{
			if(pCardsRank->m_vecRank[nlstID].back()->pCards->m_nCardsNum-1 == lstCursorCards.front()->pCards->m_nCardsNum)
				return true;
		}
		
	}
	return false;
}
	//  更新坐标
void CAAARule::UpDatePos(CCardsRank* pCardsRank, int nlstID)
{
	list<Node*>::iterator ite=pCardsRank->m_vecRank[nlstID].begin();
	int j=0;
	while(ite != pCardsRank->m_vecRank[nlstID].end())
	{
		(*ite)->x=10+81*nlstID;
		(*ite)->y=20+20*j;
		++j;
		++ite;
	}
	this->DeleteCard(pCardsRank,nlstID);
}

void CAAARule::DeleteCard(CCardsRank* pCardsRank, int nlstID)
{
	if(pCardsRank->m_vecRank[nlstID].size()>=13&&pCardsRank->m_vecRank[nlstID].back()->pCards->m_nCardsNum==1)
	{
		list<Node *>::reverse_iterator iteRev = pCardsRank->m_vecRank[nlstID].rbegin();
		for(int i = 0;i < 13;i++)
		{
			if((*iteRev)->bFlag==false)
				return;

			if((*iteRev)->pCards->m_nCardsNum != i+1)
				return ;
			++iteRev;
		}

		list<Node *>::iterator ite=iteRev.base();
		while(ite != pCardsRank->m_vecRank[nlstID].end())
		{
			delete[] *ite;
			ite=pCardsRank->m_vecRank[nlstID].erase(ite);

		}
		if(!pCardsRank->m_vecRank[nlstID].empty())
			pCardsRank->m_vecRank[nlstID].back()->bFlag=true;

	}
}
