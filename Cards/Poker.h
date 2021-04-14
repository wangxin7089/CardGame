#pragma once
#include "Sys.h"
#include "Cards.h"


class CPoker
{
public:
	CPoker(void);
	~CPoker(void);
public:
	vector<CCards*> m_vecPoker;  //  в╟13уееф
public:
	void InitPoker(HINSTANCE hIns, int nCardsColor); 
};

