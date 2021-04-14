#include "AAACardsRank.h"

IMPLEMENT_DYNCREATE(CAAACardsRank,CCardsRank)
CAAACardsRank::CAAACardsRank(void):CCardsRank(11)
{
}


CAAACardsRank::~CAAACardsRank(void)
{
}


void CAAACardsRank::InitCardsRank(HINSTANCE hIns)
{
	CPoker* poker = new CPoker[8];
	for(int i = 0;i < 8;i++)
	{
		poker[i].InitPoker(hIns,Cards_Black);
	}
	vector<CCards*> card(104);
	for(int i = 0;i < 104; i++)
	{
		card[i] = poker[i/13].m_vecPoker[i%13];
	}
	::random_shuffle(card.begin(),card.end());
	Node *pnode =NULL;
	//for(int i = 0;i < 4; i++)
	//{
	//	for(int j = 0;j < 6;j++)
	//	{
	//		pnode = new Node;
	//		pnode->bFlag = false;
	//		pnode->pCards = card[i*6+j];
	//		pnode->x = 10+81*i;
	//		pnode->y = 20+20*j;

	//		m_vecRank[i].push_back(pnode);
	//	}
	//	m_vecRank[i].back()->bFlag=true;
	//}

	//for(int i = 4;i < 10; i++)
	//{
	//	for(int j = 0;j < 5;j++)
	//	{
	//		pnode = new Node;
	//		pnode->bFlag = false;
	//		pnode->pCards = card[i*6+j];
	//		pnode->x = 10+81*i;
	//		pnode->y = 20+20*j;

	//		m_vecRank[i].push_back(pnode);
	//	}
	//	m_vecRank[i].back()->bFlag=true;
	//}
	for(int i = 0;i < 54; i++)
	{
			pnode = new Node;
			pnode->bFlag = false;
			pnode->pCards = card[i];
			pnode->x = 10+81*(i%10);
			pnode->y = 20+20*(i/10);

			m_vecRank[i%10].push_back(pnode);
	}
	for(int i = 0;i < 10; i++)
	{
		m_vecRank[i].back()->bFlag=true;
	}

	for(int i = 0;i < 50; i++)
	{
			pnode = new Node;
			pnode->bFlag = false;
			pnode->pCards = card[54+i];
			pnode->x = 400+(50-i)*5;
			pnode->y = 500;

			m_vecRank[10].push_back(pnode);
	}

//	int a=0;
}
