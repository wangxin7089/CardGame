#pragma once
#include "rule.h"
class CAAARule :
	public CRule
{
public:
	CAAARule(void);
	~CAAARule(void);
public:
	DECLARE_DYNCREATE()


	//  ���ƵĹ���
	virtual bool IsGetCardsRule(CCardsRank* pCardsRank, int nlstID, list<Node*>::iterator iteCursorPos);
	//  ����
	virtual bool IsOpenCards(POINT point, CCardsRank* pCardsRank);
	virtual void OpenCards(CCardsRank* pCardsRank);
	//  �����ƵĹ���
	virtual bool IsReceiveCardsRule(POINT point, int nlstID, CCardsRank* pCardsRank, list<Node*>& lstCursorCards);
	//  ��������
	virtual void UpDatePos(CCardsRank* pCardsRank, int nlstID);

	void DeleteCard(CCardsRank* pCardsRank, int nlstID);
};

