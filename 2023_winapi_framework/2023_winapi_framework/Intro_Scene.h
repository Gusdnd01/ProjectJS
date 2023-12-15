#pragma once
#include "Scene.h"

class Texture;
class Intro_Scene
	: public Scene
{
public:
	Intro_Scene();
	~Intro_Scene();

private:
	int m_MoveY;
	int m_YIncrease;
	int m_ArrowY;
	int m_TexSizeX;
	int m_TexSizeY;

	float m_fSstart;
	float m_fSetting;
	float m_fExiT;

public:
	virtual void Init() override;
	virtual void Render(HDC _dc) override;
	virtual void Update() override;
	virtual void Release() override;
private:
	Texture* m_pIntroTex;
	Texture* m_pGameStart;
	Texture* m_pSetting;
	Texture* m_pExit;
};