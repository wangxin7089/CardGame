#pragma once
#include "Sys.h"
#include "Cards.h"


class CPoker
{
public:
	CPoker(void);
	~CPoker(void);
public:
	vector<CCards*> m_vecPoker;  //  װ13����
public:
	void InitPoker(HINSTANCE hIns, int nCardsColor); 
};

