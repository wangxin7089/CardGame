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
			//  ����  �󶨵ĺ���ָ�� ��������
			return (*(pTemp->pfnCreateObject))();
		}
		pTemp = pTemp->pNext;
	}

	return 0;
}