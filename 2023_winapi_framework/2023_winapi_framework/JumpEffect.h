#pragma once
#include "Object.h"

class Texture;

class JumpEffect : 
	public Object
{
public:
	JumpEffect();
	~JumpEffect();
public:
	void Update() override;
	void Render(HDC _dc) override;
private:
	Texture* m_pTex;
	float per;
};