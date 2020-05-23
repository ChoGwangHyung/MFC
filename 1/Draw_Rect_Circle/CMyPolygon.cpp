#include "StdAfx.h"
#include "CMyPolygon.h"

CMyPolygon::CMyPolygon()
{
	pcount = 0;
}

CMyPolygon::~CMyPolygon() {}

void CMyPolygon::point_draw(CDC *pDC)
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CBrush brush(RGB(0, 0, 0));
	pDC->SelectObject(&brush);
	pDC->SelectObject(&pen);
	for (int i = 0; i < pcount ; i++)
	{
		pDC->Ellipse(all_point[i].x - 5, all_point[i].y - 5,
			all_point[i].x + 5, all_point[i].y + 5);
	}
}

void CMyPolygon::rgn_draw(CDC *pDC)
{
	CRgn rgn;
	rgn.CreatePolygonRgn(all_point, pcount, ALTERNATE);
	CBrush brush(RGB(0, 0, 255));
	pDC->FillRgn(&rgn, &brush);
}