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
	char szClassName[20];   //  装一个类名
	COObject* (*pfnCreateObject)();   //  创建对象的函数指针
	RunTimeClass* pNext;
};

class COObject
{
public:
	static RunTimeClass* pHead;    //  链表的 头
public:
	COObject(void);
	virtual ~COObject(void);
public:
	static COObject* Create(const char* pszClassName);
};

class InitObject
{
public:
	InitObject(RunTimeClass* pTemp)  //  给 pHead 这个链表 头添加节点   push_front
	{
		pTemp->pNext = COObject::pHead;
		COObject::pHead = pTemp;
	}
};