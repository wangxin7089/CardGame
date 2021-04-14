#include "OObject.h"

RunTimeClass* COObject::pHead = 0;
COObject::COObject(void)
{
}


COObject::~COObject(void)
{
}
COObject* COObject::Create(const char* pszClassName)
{
	RunTimeClass* pTemp = COObject::pHead;
	while(pTemp)
	{
		if(!strcmp(pTemp->szClassName,pszClassName))
		{
			//  调用  绑定的函数指针 创建对象
			return (*(pTemp->pfnCreateObject))();
		}
		pTemp = pTemp->pNext;
	}

	return 0;
}