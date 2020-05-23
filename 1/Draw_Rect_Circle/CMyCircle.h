#pragma once
#include "CMyShape.h"

class CMyCircle :public CMyShape
{
public:
	CMyCircle();
	~CMyCircle();

	void draw(CDC *pDC);

};