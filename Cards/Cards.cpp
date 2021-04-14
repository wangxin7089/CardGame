#include "Cards.h"


CCards::CCards(void)
{
	m_hBmpCards = 0;  //  牌的  图片
	m_nCardsColor = 0;   //  牌的颜色
	m_nCardsNum = 0;    //  牌的数字
}


CCards::~CCards(void)
{
	::DeleteObject(m_hBmpCards);
	m_hBmpCards = 0;
}
void CCards::InitCards(HINSTANCE hIns, int nCardsColor, int nCardsNum)
{
	m_nCardsColor = nCardsColor;
	m_nCardsNum = nCardsNum;
	m_hBmpCards = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BITMAP1+nCardsColor*13+nCardsNum-1));
}