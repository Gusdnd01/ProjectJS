#pragma once
#pragma once
#include "Scene.h"

class Texture;
class OutStoryScene 
	: public Scene
{
public:
	virtual void Init() override;
	virtual void Render(HDC _dc) override;
	virtual void Release() override;
private:
	int m_ImgCnt;
private:
	Texture* m_Story1;
	Texture* m_Story2;
	Texture* m_Story3;
	Texture* m_Story4;
	Texture* m_BK;
};

