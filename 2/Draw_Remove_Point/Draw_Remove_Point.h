// Draw_Remove_Point.h: Draw_Remove_Point ���� ���α׷��� �⺻ ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CDraw_Remove_PointApp:
// �� Ŭ������ ������ ���ؼ��� Draw_Remove_Point.cpp��(��) �����ϼ���.
//

class CDraw_Remove_PointApp : public CWinApp
{
public:
	CDraw_Remove_PointApp() noexcept;


	// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDraw_Remove_PointApp theApp;
