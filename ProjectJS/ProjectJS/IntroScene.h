#pragma once
#include "Scene.h"

class IntroScene :
	public Scene
{
public:
	void Init() override;
	void Render(HDC _dc) override;
	void Update() override;
};