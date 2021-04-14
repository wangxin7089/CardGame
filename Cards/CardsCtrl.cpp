#include "CardsCtrl.h"

IMPLEMENT(CCardsCtrl)
CCardsCtrl::CCardsCtrl(void)
{
	m_pRank = 0;
	m_pRule = 0;
}


CCardsCtrl::~CCardsCtrl(void)
{
	delete m_pRank;
	m_pRank = 0;

	delete m_pRule;
	m_pRule = 0;


	list<Node*>::iterator ite = m_lstCursorCards.begin();
	while(ite != m_lstCursorCards.end())
	{
		delete(*ite);
		++ite;
	}
}

void CCardsCtrl::OnCreateGame()                 //    WM_CREATE  初始化游戏
{
	// 1。   通过  动态创建对象   创建  CCardsRank 和 CRule 的派生类对象
	m_pRank = (CCardsRank*)COObject::Create("CCardsRank");
	m_pRule = (CRule*)COObject::Create("CRule");

	// 2.    执行 CCardsRank 的 初始化
	if(m_pRank != NULL && m_pRule != 0)
		m_pRank->InitCardsRank(m_hIns);
	else
		::MessageBox(NULL,"游戏初始化失败","提示",MB_OK);
}


void CCardsCtrl::OnGameDraw()                   //    WM_PAINT   游戏绘图
{
	HDC dc = ::GetDC(m_hMainWnd);
	HDC hMemDC = ::CreateCompatibleDC(dc);
	HBITMAP hBitmap = ::CreateCompatibleBitmap(dc,850,600);
	::SelectObject(hMemDC,hBitmap);

	//------------------------------------------
	if(m_pRank != NULL)
		m_pRank->ShowRank(hMemDC,m_hIns);
	this->ShowCursorCards(hMemDC);
	//------------------------------------------
	::BitBlt(dc,0,0,850,600,hMemDC,0,0,SRCCOPY);


	::DeleteDC(hMemDC);
	::DeleteObject(hBitmap);
	::ReleaseDC(m_hMainWnd,dc);
}
void CCardsCtrl::OnLButtonDown(POINT point)    //    WM_LBUTTONDOWN
{
	pointMouseDown = point;
	if(m_lstCursorCards.empty() == false)
		m_pRule->RevertCards(m_pRank,m_lstCursorCards);  // 还原
	if(m_pRule != NULL)    //  拿牌
		m_pRule->GetCards(point,m_pRank,m_lstCursorCards);

	//  重绘
	this->OnGameDraw();
}
void CCardsCtrl::OnLButtonUp(POINT point)       //    WM_LBUTTONDOWN
{
	//  光标有没有牌
	if(m_lstCursorCards.empty() == false)
	{
		//  能不能接收
		if(m_pRule->ReceiveCards(point,m_pRank,m_lstCursorCards) == false)
			m_pRule->RevertCards(m_pRank,m_lstCursorCards);  // 还原	
	}
	else
	{
		//  判断 是否可以  发牌
		if(m_pRule->IsOpenCards(point,m_pRank) == true)
		{
			m_pRule->OpenCards(m_pRank);
		}
	}
		
	//  重绘
	this->OnGameDraw();
}
void CCardsCtrl::OnMouseMove(POINT point)       //    WM_LBUTTONDOWN
{
	pointMouseMove = point;
	//  重绘
	this->OnGameDraw();
}

void CCardsCtrl::ShowCursorCards(HDC hMemDC)
{
	//  获取  移动的 距离
	int X = pointMouseMove.x - pointMouseDown.x;
	int Y = pointMouseMove.y - pointMouseDown.y;

	list<Node*>::iterator ite = m_lstCursorCards.begin();
	while(ite != m_lstCursorCards.end())
	{
		HDC hTempDC = ::CreateCompatibleDC(hMemDC);
		::SelectObject(hTempDC,(*ite)->pCards->m_hBmpCards);
		::BitBlt(hMemDC,(*ite)->x+X,(*ite)->y+Y,850,600,hTempDC,0,0,SRCCOPY);
		::DeleteDC(hTempDC);
		++ite;
	}
}