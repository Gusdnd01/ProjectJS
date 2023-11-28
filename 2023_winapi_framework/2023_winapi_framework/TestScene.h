#pragma once
#include "Scene.h"


class TestScene
	: public Scene
{
public:
	virtual void Init() override;
	virtual void Render(HDC _dc) override;
};

