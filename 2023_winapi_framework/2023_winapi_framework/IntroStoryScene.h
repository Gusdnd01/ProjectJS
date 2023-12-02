#pragma once
#include "Scene.h"


class IntroStoryScene
	: public Scene
{
public:
	virtual void Init() override;
	virtual void Render(HDC _dc) override;
	virtual void Release() override;
private:
	int m_ImgCnt;
};

