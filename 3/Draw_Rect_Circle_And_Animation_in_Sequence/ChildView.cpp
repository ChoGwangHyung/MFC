
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "Draw_Rect_Circle_And_Animation_in_Sequence.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	start_pt = true;
	play = false;
	count = 0;
	curPos = count;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_BN_CLICKED(101, ClearButtonClicked)
	ON_BN_CLICKED(102, SaveButtonClicked)
	ON_BN_CLICKED(103, LoadButtonClicked)
	ON_BN_CLICKED(104, ReplayButtonClicked)
	ON_BN_CLICKED(105, StopButtonClicked)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_WM_RBUTTONDOWN()
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

	CPen pen1(PS_DASH, 1, RGB(0, 0, 0));
	CPen pen2(PS_SOLID, 1, RGB(0, 0, 0));
	CPen pen3(PS_SOLID, 2, RGB(255, 0, 0));

	//애니메이션
	if (play == true && m_list.GetHeadPosition() != NULL) {
		memDC.SelectObject(&pen1);
		POSITION ptList = m_list.GetHeadPosition();

		while (ptList != NULL)
		{
			CPoint pt = m_list.GetAt(ptList);
			if (start_pt) {
				memDC.MoveTo(pt.x, pt.y);
				start_pt = false;
			}
			memDC.LineTo(pt.x, pt.y);
			m_list.GetNext(ptList);
		}
		start_pt = true;

		memDC.SelectObject(&pen2);
		memDC.RoundRect(play_pt.x - 40, play_pt.y - 40, play_pt.x + 40, play_pt.y + 40, radious, radious);
	}
	else if (play == false) {
		memDC.SelectObject(&pen2);

		//실선 출력
		POSITION ptList = m_list.GetHeadPosition();
		while (ptList != NULL)
		{
			CPoint pt = m_list.GetAt(ptList);
			if (start_pt) {
				memDC.MoveTo(pt.x, pt.y);
				start_pt = false;
			}
			memDC.LineTo(pt.x, pt.y);
			m_list.GetNext(ptList);
		}
		start_pt = true;

		//도형출력
		ptList = m_list.GetHeadPosition();
		POSITION blList = shape_list.GetHeadPosition();
		POSITION sList = s_list.GetHeadPosition();
		while (ptList != NULL)
		{
			CPoint pt = m_list.GetAt(ptList);
			bool bl = shape_list.GetAt(blList);
			int curpos = s_list.GetAt(sList);
			//선택 사각형 빨간색 선
			if (ptList == NULL || curpos == curPos)memDC.SelectObject(&pen3);
			else memDC.SelectObject(&pen2);

			if (bl == true)
				memDC.Rectangle(pt.x - 40, pt.y - 40, pt.x + 40, pt.y + 40);
			else
				memDC.Ellipse(pt.x - 40, pt.y - 40, pt.x + 40, pt.y + 40);

			s_list.GetNext(sList);
			m_list.GetNext(ptList);
			shape_list.GetNext(blList);
		}
	}

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (play == true)return;
	rec = true;
	m_list.AddTail(point);
	shape_list.AddTail(rec);
	count++;
	s_list.AddTail(count);
	Hbar.SetScrollRange(1, count);
	curPos = count;
	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	clear.Create(_T("CLEAR"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(0, 0, 100, 30),
		this, 101);
	save.Create(_T("SAVE"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(100, 0, 200, 30),
		this, 102);
	load.Create(_T("LOAD"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(200, 0, 300, 30),
		this, 103);
	replay.Create(_T("REPLAY"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(300, 0, 400, 30),
		this, 104);
	stop.Create(_T("STOP"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		CRect(400, 0, 500, 30),
		this, 105);

	Hbar.Create(SBS_HORZ, CRect(500, 0, 800, 30), this, 106);
	Hbar.ShowWindow(true);
	Hbar.SetScrollPos(500);

	SetTimer(0, 5, NULL);
	return 0;
}


void CChildView::ClearButtonClicked()
{
	m_list.RemoveAll();
	s_list.RemoveAll();
	shape_list.RemoveAll();
	count = 0;
	Invalidate();
}

void CChildView::SaveButtonClicked()
{
	CFile file;
	CFileException e;
	if (!file.Open(_T("SaveData.dat"),
		CFile::modeReadWrite |
		CFile::modeCreate, &e))
	{
		e.ReportError();
		return;
	}
	CArchive ar(&file, CArchive::store);
	m_list.Serialize(ar);
	s_list.Serialize(ar);
	shape_list.Serialize(ar);
	ar << count << curPos;
	Invalidate();
}

void CChildView::LoadButtonClicked()
{
	ClearButtonClicked();
	CFile file;
	CFileException e;
	if (!file.Open(_T("SaveData.dat"),
		CFile::modeRead, &e))
	{
		e.ReportError();
		return;
	}
	CArchive ar(&file, CArchive::load);
	m_list.Serialize(ar);
	s_list.Serialize(ar);
	shape_list.Serialize(ar);
	ar >> count >> curPos;
	Hbar.SetScrollRange(1, count);
	if (play)ReplayButtonClicked();
	Invalidate();
}

void CChildView::ReplayButtonClicked()
{
	play = true;
	if (m_list.GetHeadPosition() == NULL)return;
	m = m_list.GetHeadPosition();
	s = shape_list.GetHeadPosition();
	play_pt = m_list.GetAt(m);
	go = false;
	curPos = 1;
	Invalidate();
}

void CChildView::StopButtonClicked()
{
	play = false;
	Invalidate();
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nIDEvent == 0)
	{
		if (play == false || m_list.GetHeadPosition() == NULL) return;
		Hbar.SetScrollPos(curPos);
		if (go == false) {
			s_pt = m_list.GetAt(m);
			s_bl = shape_list.GetAt(s);
			m_list.GetNext(m);
			shape_list.GetNext(s);
			if (m == NULL) {
				Sleep(1000);
				return ReplayButtonClicked();
			}
			e_pt = m_list.GetAt(m);
			e_bl = shape_list.GetAt(s);
			if (s_bl == true && e_bl == true)radious = 0;
			else if (s_bl == true && e_bl == false)radious = 0;
			else if (s_bl == false && e_bl == true)radious = 80;
			else if (s_bl == false && e_bl == false)radious = 80;
			repeat = 0;
			go = true;
		}

		long moveX;
		long moveY;

		moveX = e_pt.x - s_pt.x;
		moveY = e_pt.y - s_pt.y;
		repeat++;

		play_pt.x = s_pt.x + moveX * repeat / 40;
		play_pt.y = s_pt.y + moveY * repeat / 40;

		if (s_bl == true && e_bl == false)radious += 2;
		else if (s_bl == false && e_bl == true)radious -= 2;

		if (repeat >= 40) {
			go = false;
			curPos++;
			play_pt = e_pt;
		}

		Invalidate();
		CWnd::OnTimer(nIDEvent);
	}
}


void CChildView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (pScrollBar != NULL) {
		if (nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION) {
			pScrollBar->SetScrollPos(nPos);
			curPos = nPos;
		}
		if (nSBCode == SB_LINELEFT) {
			int pos = pScrollBar->GetScrollPos() - 1;
			if (pos < 1) { curPos = 1; return; }
			pScrollBar->SetScrollPos(pos);
			curPos = pos;
		}
		if (nSBCode == SB_LINERIGHT) {
			int pos = pScrollBar->GetScrollPos() + 1;
			if (pos > count)return;
			pScrollBar->SetScrollPos(pos);
			curPos = pos;
		}
		this->Invalidate();
	}
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (play == true)return;
	rec = false;
	m_list.AddTail(point);
	shape_list.AddTail(rec);
	count++;
	s_list.AddTail(count);
	Hbar.SetScrollRange(1, count);
	curPos = count;
	Invalidate();
	CWnd::OnRButtonDown(nFlags, point);
}
