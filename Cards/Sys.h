#pragma once

#include <windows.h>
#include <list>
#include <vector>
#include <algorithm>
#include "resource.h"


using namespace std;

// �Ƶ� ��ɫ
enum {Cards_Flower,Cards_Square,Cards_Red,Cards_Black};

class CCards;
struct Node
{
	bool bFlag;  // ������
	CCards* pCards;  //  װһ����
	int x;            //  �Ƶ�λ��
	int y;
};