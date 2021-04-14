#pragma once
#include "Sys.h"


class CCards
{
public:
	CCards(void);
	~CCards(void);
public:
	HBITMAP m_hBmpCards;  //  牌的  图片
	int m_nCardsColor;   //  牌的颜色
	int m_nCardsNum;    //  牌的数字
public:
	void InitCards(HINSTANCE hIns, int nCardsColor, int nCardsNum);  //  初始化
};

