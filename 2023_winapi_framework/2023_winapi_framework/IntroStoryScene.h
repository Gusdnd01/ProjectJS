#pragma once
#include "Scene.h"

class Texture;
class IntroStoryScene
	: public Scene
{
public:
	IntroStoryScene();
	~IntroStoryScene();
public:
	virtual void Init() override;
	virtual void Render(HDC _dc) override;
	virtual void Release() override;
private:
	int m_ImgCnt;
	bool m_bClear;

	vector<Texture*> m_pStoryTextures;
	Texture* m_pBK;
};

