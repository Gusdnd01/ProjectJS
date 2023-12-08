#pragma once
#include "Scene.h"

class Texture;
class IntroStoryScene
	: public Scene
{
public:
	virtual void Init() override;
	virtual void Render(HDC _dc) override;
	virtual void Release() override;
private:
	int m_ImgCnt;
	bool m_Clear;
private:
	Texture* m_Story1;
	Texture* m_Story2;
	Texture* m_Story3;
	Texture* m_Story4;
	Texture* m_Story5;
	Texture* m_BK;
};

