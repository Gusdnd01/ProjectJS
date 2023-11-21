#pragma once
#include "Object.h"

class IntroObj :
	public Object
{
public:
	IntroObj();
	~IntroObj();
public:
	void Render(HDC _dc) override;
	void Update() override;
private:
	int x = 500;
	int y = 100;
	int arrowX = x - 10;
	int arrowY = y;
};

