#include "Poker.h"


CPoker::CPoker(void):m_vecPoker(13)
{
}


CPoker::~CPoker(void)
{
	for(int i=0;i<13;i++)   //  ɾ�� ���е���
		delete m_vecPoker[i];
}
void CPoker::InitPoker(HINSTANCE hIns, int nCardsColor)
{
	//  ���� 13�� �ƵĶ���
	for(int i=0;i<13;i++)
	{
		m_vecPoker[i] = new CCards;
	    //  ÿ���Ƶĳ�ʼ��
		m_vecPoker[i]->InitCards(hIns,nCardsColor,i+1);
	}
}