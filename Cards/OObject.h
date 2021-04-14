#pragma once
#include <iostream>
using namespace std;


#define DECLARE_DYNCREATE()\
	static RunTimeClass run;\
	static COObject* CreateObject();

#define IMPLEMENT_DYNCREATE(ThisClass,BaseClass)\
	RunTimeClass ThisClass::run = {#BaseClass,&ThisClass::CreateObject,0};\
	InitObject initObject##ThisClass(&ThisClass::run);\
	COObject* ThisClass::CreateObject()\
	{\
		return new ThisClass;\
	}

class COObject;
struct RunTimeClass
{
	char szClassName[20];   //  װһ������
	COObject* (*pfnCreateObject)();   //  ��������ĺ���ָ��
	RunTimeClass* pNext;
};

class COObject
{
public:
	static RunTimeClass* pHead;    //  ����� ͷ
public:
	COObject(void);
	virtual ~COObject(void);
public:
	static COObject* Create(const char* pszClassName);
};

class InitObject
{
public:
	InitObject(RunTimeClass* pTemp)  //  �� pHead ������� ͷ��ӽڵ�   push_front
	{
		pTemp->pNext = COObject::pHead;
		COObject::pHead = pTemp;
	}
};