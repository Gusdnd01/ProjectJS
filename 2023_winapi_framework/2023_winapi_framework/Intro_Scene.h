#pragma once
#include "Scene.h"

class Intro_Scene
	: public Scene
{
private:
	int moveY;
	int yIncrease;
	int arrowY;
public:
	virtual void Init() override;
	virtual void Render(HDC _dc) override;
	virtual void Update() override;
};