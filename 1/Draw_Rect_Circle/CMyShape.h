#pragma once

class CMyShape
{
public:
	CPoint m_start;
	CPoint m_end;

	CMyShape();
	~CMyShape();

	virtual void draw(CDC *pDC);
};