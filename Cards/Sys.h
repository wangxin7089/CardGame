#pragma once

#include <windows.h>
#include <list>
#include <vector>
#include <algorithm>
#include "resource.h"


using namespace std;

// 牌的 颜色
enum {Cards_Flower,Cards_Square,Cards_Red,Cards_Black};

class CCards;
struct Node
{
	bool bFlag;  // 正反面
	CCards* pCards;  //  装一张牌
	int x;            //  牌的位置
	int y;
};