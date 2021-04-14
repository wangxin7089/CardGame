#pragma once
#include "cardsrank.h"
class CAAACardsRank :
	public CCardsRank
{
public:
	CAAACardsRank(void);
	~CAAACardsRank(void);
public:
	DECLARE_DYNCREATE()


	virtual void InitCardsRank(HINSTANCE hIns);
};

