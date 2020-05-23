
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once


// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	CList<CPoint> m_list;
	CList<int> s_list;
	CList<bool> shape_list;
	bool rec;
	bool start_pt;
	int radious;

	CButton clear;
	CButton save;
	CButton load;
	CButton replay;
	CButton stop;

	CScrollBar Hbar;
	int count;
	int curPos;

	CPoint play_pt;
	CPoint s_pt;
	CPoint e_pt;
	POSITION m;
	POSITION s;
	bool go;
	bool play;
	int scroll_pos;
	int repeat;
	bool s_bl;
	bool e_bl;
// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();
	void ClearButtonClicked();
	void SaveButtonClicked();
	void LoadButtonClicked();
	void ReplayButtonClicked();
	void StopButtonClicked();
	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

