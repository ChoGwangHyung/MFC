#pragma once

class CMyPolygon
{
public:
	CPoint all_point[20];
	int pcount;

	CMyPolygon();
	~CMyPolygon();

	void point_draw(CDC *pDC);
	void rgn_draw(CDC *pDC);
};