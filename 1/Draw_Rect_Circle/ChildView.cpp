
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "Draw_Rect_Circle.h"
#include "ChildView.h"
#include "CMyRect.h"
#include "CMyShape.h"
#include "CMyCircle.h"
#include "CMyPolygon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	LDown = false;
	RDown = false;
	MDown = true;
	make_num = 0;
	p_count = 0;
	//포인터 배열 초기화
	for (int i = 0; i < 100; i++)
		make[i] = &reset[i];
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
//	ON_WM_NCLBUTTONDOWN()
//	ON_WM_NCLBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect rect;
	GetClientRect(rect);
	
	//더블 버퍼링
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	
	//출력
	for (int i = 0; i < make_num + 1; i++)
	{
		make[i]->draw(&memDC);
		p_make[i].point_draw(&memDC);
		if (MDown)
			p_make[i].rgn_draw(&memDC);
	}
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (LDown) {
		r_make[make_num].m_end = point;
		Invalidate();
	}

	if (RDown) {
		c_make[make_num].m_end = point;
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (MDown)
	{
		make[make_num] = &c_make[make_num];

		SetCapture();

		RDown = true;

		make[make_num + 1] = make[make_num];

		c_make[make_num].m_start = point;
	}
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (MDown)
	{
		ReleaseCapture();

		RDown = false;

		c_make[make_num].m_end = point;
		make_num++;

		Invalidate();
	}
	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (MDown)
	{
		make[make_num] = &r_make[make_num];

		SetCapture();

		LDown = true;

		make[make_num + 1] = make[make_num];

		r_make[make_num].m_start = point;
	}
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (MDown)
	{
		ReleaseCapture();

		LDown = false;

		r_make[make_num].m_end = point;
		make_num++;

		Invalidate();
	}
	CWnd::OnLButtonUp(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}


void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	MDown = true;

	make_num++;

	Invalidate();

	CWnd::OnLButtonDblClk(nFlags, point);
}


void CChildView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다
	CClientDC dc(this);

	MDown = false;
	
	CBrush brush(RGB(0, 0, 0));
	dc.SelectObject(&brush);
	dc.Ellipse(point.x - 5, point.y - 5, point.x + 5, point.y + 5);
	p_make[make_num].all_point[p_make[make_num].pcount] = point;
	p_make[make_num].pcount++;

	CWnd::OnMButtonDown(nFlags, point);
}
