#pragma once
#include "CMyShape.h"

class CMyRect : public CMyShape 
{
public:
	CMyRect();
	~CMyRect();

	void draw(CDC *pDC);
};