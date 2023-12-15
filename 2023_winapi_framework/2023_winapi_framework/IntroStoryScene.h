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
private:
	Texture* m_pStory1;
	Texture* m_pStory2;
	Texture* m_pStory3;
	Texture* m_pStory4;
	Texture* m_pStory5;
	Texture* m_pBK;
};

