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
	vector<Texture*> m_vStoryTexture;
	Texture* m_BK;
};

