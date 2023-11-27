#pragma once
class Texture;
class ShowSetting
{
	SINGLE(ShowSetting);
public:
	bool IsActive = false;
public:
	void Init();
	void Render(HDC _dc);
	void Update();
private:
	int moveY;
	int yIncrease;
	int arrowY; 
	float bgmVolume;
	float effectVolume;
private:
	Texture* m_pTex = nullptr;
};