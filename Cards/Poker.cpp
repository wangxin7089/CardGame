#include "Poker.h"


CPoker::CPoker(void):m_vecPoker(13)
{
}


CPoker::~CPoker(void)
{
	for(int i=0;i<13;i++)   //  删除 所有的牌
		delete m_vecPoker[i];
}
void CPoker::InitPoker(HINSTANCE hIns, int nCardsColor)
{
	//  创建 13个 牌的对象
	for(int i=0;i<13;i++)
	{
		m_vecPoker[i] = new CCards;
	    //  每个牌的初始化
		m_vecPoker[i]->InitCards(hIns,nCardsColor,i+1);
	}
}