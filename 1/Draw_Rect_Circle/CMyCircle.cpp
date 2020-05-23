#include "stdafx.h"
#include "CMyCircle.h"

CMyCircle::CMyCircle()
	: CMyShape()
{}

CMyCircle::~CMyCircle() {}


void CMyCircle::draw(CDC *pDC) {
	
	//노란색
	CBrush brush(RGB(0, 255, 0));
	pDC->SelectObject(&brush);
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	pDC->SelectObject(&pen);
	//타원 출력
	pDC->Ellipse(m_start.x, m_start.y, m_end.x, m_end.y);
}