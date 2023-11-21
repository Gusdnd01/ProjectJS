#pragma once
#include "Scene.h"

class Intro_Scene
	: public Scene
{
private:
	int moveY = 0;
	int yIncrease = 50;
public:
	virtual void Init() override;
	virtual void Render(HDC _dc) override;
};

