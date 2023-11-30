#pragma once
#include "Scene.h"

class Texture;
class Intro_Scene
	: public Scene
{
private:
	int moveY;
	int yIncrease;
	int arrowY;
	int TexSizeX;
	int TexSizeY;

	float start;
	float setting;
	float exiT;

public:
	virtual void Init() override;
	virtual void Render(HDC _dc) override;
	virtual void Update() override;
	virtual void Release() override;
private:
	Texture* introTex;
	Texture* GameStart;
	Texture* Setting;
	Texture* Exit;
};