
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "Draw_Remove_Point.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	what_color = RGB(0, 0, 0);
	lb = false;
	rb = false;
	shape = true;
	e = false;
	up = false;
	down = false;
	right = false;
	left = false;
	rmove = false;
	value = 5;
	num = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_COLOR_RED, &CChildView::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CChildView::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CChildView::OnColorBlue)
	ON_COMMAND(ID_COLOR_BLACK, &CChildView::OnColorBlack)
	ON_COMMAND(ID_Rectangle, &CChildView::OnRectangle)
	ON_COMMAND(ID_Circle, &CChildView::OnCircle)
	ON_COMMAND(ID_Erase, &CChildView::OnErase)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CChildView::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CChildView::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CChildView::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CChildView::OnUpdateColorBlack)
	ON_UPDATE_COMMAND_UI(ID_Circle, &CChildView::OnUpdateCircle)
	ON_UPDATE_COMMAND_UI(ID_Rectangle, &CChildView::OnUpdateRectangle)
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_Erase, &CChildView::OnUpdateErase)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

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
	
	CPen pen1(PS_SOLID, 1, RGB(0, 0, 0));
	memDC.SelectObject(&pen1);

	//점 찍기
	POSITION ptList = m_pt.GetHeadPosition();
	POSITION crList = m_color.GetHeadPosition();
	POSITION shList = m_shape.GetHeadPosition();
	while (ptList != NULL)
	{
		CPoint pt = m_pt.GetAt(ptList);
		CBrush brush(m_color.GetAt(crList));
		bool rec = m_shape.GetAt(shList);
		memDC.SelectObject(&brush);
		if (rec)
			memDC.Rectangle(pt.x, pt.y, pt.x + 10, pt.y + 10);
		else
			memDC.Ellipse(pt.x, pt.y, pt.x + 10, pt.y + 10);
		m_pt.GetNext(ptList);
		m_color.GetNext(crList);
		m_shape.GetNext(shList);
	}

	//사각형
	if (rb) {
		CBrush rbrush(RGB(255, 255, 255));
		memDC.SelectObject(&rbrush);
		CPen pen2(PS_SOLID, 6, RGB(100, 0, 100));
		memDC.SelectObject(&pen2);
		memDC.Rectangle(start.x, start.y, end.x, end.y);
	}

	//점 개수 출력
	CString pt_num;
	pt_num.Format(_T("How point : %d"), num);
	memDC.TextOut(0, 0, pt_num);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (start.x < point.x && point.x < end.x && start.y < point.y && point.y < end.y) {
		lb = true;
		Invalidate();
	}
	else{
	m_pt.AddTail(point);
	m_shape.AddTail(shape);
	m_color.AddTail(what_color);
	num++;
	}
	lb = true;
	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	lb = false;
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	start = point;
	rb = true;
	rmove = true;
	Invalidate();
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	rmove = false;
	end = point;
	if (start.x > end.x) {
		temp = start.x;
		start.x = end.x;
		end.x = temp;
	}
	if (start.y > end.y) {
		temp = start.y;
		start.y = end.y;
		end.y = temp;
	}

	POSITION ptList = m_pt.GetHeadPosition();
	POSITION crList = m_color.GetHeadPosition();
	POSITION shList = m_shape.GetHeadPosition();

	while (ptList != NULL)
	{
		POSITION cur1 = ptList;
		POSITION cur2 = crList;
		POSITION cur3 = shList;
		CPoint pt = m_pt.GetAt(ptList);
		m_pt.GetNext(ptList);
		m_color.GetNext(crList);
		m_shape.GetNext(shList);

		if (start.x < pt.x && pt.x < end.x && start.y < pt.y && pt.y < end.y)
		{
			m_pt.RemoveAt(cur1);
			m_color.RemoveAt(cur2);
			m_shape.RemoveAt(cur3);
			num--;
		}
	}

	Invalidate();
	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (lb) {
		if (start.x < point.x && point.x < end.x && start.y < point.y && point.y < end.y)
			Invalidate();
		else {
			m_pt.AddTail(point);
			m_shape.AddTail(shape);
			m_color.AddTail(what_color);
			num++;
		}
		Invalidate();
	}
	if (rmove) {
		end = point;
		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnColorRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	what_color = RGB(255, 0, 0);
	Invalidate();
}


void CChildView::OnColorGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	what_color = RGB(0, 255, 0);
	Invalidate();
}


void CChildView::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	what_color = RGB(0, 0, 255);
	Invalidate();
}


void CChildView::OnColorBlack()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	what_color = RGB(0, 0, 0);
	Invalidate();
}


void CChildView::OnRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	shape = true;
}


void CChildView::OnCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	shape = false;
}


void CChildView::OnErase()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (e)
		e = false;
	else
		e = true;
}


void CChildView::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(what_color == RGB(255, 0, 0));
}


void CChildView::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(what_color == RGB(0, 255, 0));
}


void CChildView::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(what_color == RGB(0, 0, 255));
}


void CChildView::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(what_color == RGB(0, 0, 0));
}


void CChildView::OnUpdateCircle(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(shape == false);
}


void CChildView::OnUpdateRectangle(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(shape == true);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return true;
}


void CChildView::OnUpdateErase(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (e)
		pCmdUI->SetCheck(true);

	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (e) {
		if (nChar == VK_UP) {
			up = true;
			down = false;
			right = false;
			left = false;
		}
		if (nChar == VK_DOWN) {
			up = false;
			down = true;
			right = false;
			left = false;
		}
		if (nChar == VK_RIGHT) {
			up = false;
			down = false;
			right = true;
			left = false;
		}
		if (nChar == VK_LEFT) {
			up = false;
			down = false;
			right = false;
			left = true;
		}
	}
	else {
		up = false;
		down = false;
		right = false;
		left = false;
	}

	Invalidate();
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 0)
	{
		if (e) {
			CRect rect;
			GetClientRect(rect);
			if (up) {
				start.y -= value;
				end.y -= value;
				if (start.y <= rect.top) {
					up = false;
					down = true;
				}
				Invalidate();
			}
			if (down) {
				start.y += value;
				end.y += value;
				if (end.y >= rect.bottom) {
					up = true;
					down = false;
				}
				Invalidate();
			}
			if (right) {
				start.x += value;
				end.x += value;
				if (end.x >= rect.right) {
					right = false;
					left = true;
				}
				Invalidate();
			}
			if (left) {
				start.x -= value;
				end.x -= value;
				if (start.x <= rect.left) {
					right = true;
					left = false;
				}
				Invalidate();
			}

			POSITION ptList = m_pt.GetHeadPosition();
			POSITION crList = m_color.GetHeadPosition();
			POSITION shList = m_shape.GetHeadPosition();
			while (ptList != NULL)
			{
				POSITION cur1 = ptList;
				POSITION cur2 = crList;
				POSITION cur3 = shList;
				CPoint pt = m_pt.GetAt(ptList);
				m_pt.GetNext(ptList);
				m_color.GetNext(crList);
				m_shape.GetNext(shList);

				if (start.x < pt.x && pt.x < end.x && start.y < pt.y && pt.y < end.y) {
					m_pt.RemoveAt(cur1);
					m_color.RemoveAt(cur2);
					m_shape.RemoveAt(cur3);
					num--;
				}
			}
		}
		else {
			up = false;
			down = false;
			right = false;
			left = false;
		}

	}

	CWnd::OnTimer(nIDEvent);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(0, 1, NULL);

	return 0;
}
