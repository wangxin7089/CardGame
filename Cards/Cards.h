#pragma once
#include "Sys.h"


class CCards
{
public:
	CCards(void);
	~CCards(void);
public:
	HBITMAP m_hBmpCards;  //  �Ƶ�  ͼƬ
	int m_nCardsColor;   //  �Ƶ���ɫ
	int m_nCardsNum;    //  �Ƶ�����
public:
	void InitCards(HINSTANCE hIns, int nCardsColor, int nCardsNum);  //  ��ʼ��
};

