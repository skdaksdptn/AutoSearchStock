
// AutoSearchStock.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CAutoSearchStockApp:
// �� Ŭ������ ������ ���ؼ��� AutoSearchStock.cpp�� �����Ͻʽÿ�.
//

class CAutoSearchStockApp : public CWinApp
{
public:
	CAutoSearchStockApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CAutoSearchStockApp theApp;