#include "stdafx.h"
#include "CMyRect.h"
#include "resource.h"

CMyRect::CMyRect()
	: CMyShape() 
{}

CMyRect::~CMyRect() {}


void CMyRect::draw(CDC *pDC) {
	
	//ºñÆ®¸Ê
	CBitmap r_bitmap;
	r_bitmap.LoadBitmap(IDB_BITMAP1);
	BITMAP bmpInfo;
	r_bitmap.GetBitmap(&bmpInfo);

	CDC rDc;
	rDc.CreateCompatibleDC(pDC);
	rDc.SelectObject(&r_bitmap);
	
	CPen pen(PS_SOLID, 10, RGB(0, 0, 0));
	//ÇÏ¾á»ö
	CBrush brush(RGB(255, 255, 255));
	pDC->SelectObject(&brush);
	pDC->SelectObject(&pen);
	
	//»ç°ÝÇü ¹× ºñÆ®¸Ê Ãâ·Â
	pDC->Rectangle(m_start.x, m_start.y , m_end.x , m_end.y);
	pDC->StretchBlt(m_start.x, m_start.y, m_end.x - m_start.x, m_end.y - m_start.y,
		&rDc, 0,0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
	
}