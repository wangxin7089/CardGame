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


	//  拿牌的规则
	virtual bool IsGetCardsRule(CCardsRank* pCardsRank, int nlstID, list<Node*>::iterator iteCursorPos);
	//  发牌
	virtual bool IsOpenCards(POINT point, CCardsRank* pCardsRank);
	virtual void OpenCards(CCardsRank* pCardsRank);
	//  接收牌的规则
	virtual bool IsReceiveCardsRule(POINT point, int nlstID, CCardsRank* pCardsRank, list<Node*>& lstCursorCards);
	//  更新坐标
	virtual void UpDatePos(CCardsRank* pCardsRank, int nlstID);

	void DeleteCard(CCardsRank* pCardsRank, int nlstID);
};

