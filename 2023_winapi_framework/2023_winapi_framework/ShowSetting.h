#pragma once
class Texture;
class Object;
class ShowSetting
{
	SINGLE(ShowSetting);
public:
	bool IsActive = false;
	bool IsEscActive = false;
public:
	void Init();
	void Render(HDC _dc);
	void Update();
private:
	int settingMoveY;
	int settingYIncrease;
	int settingArrowY;

	int escMoveY;
	int escYIncrease;
	int escArrowY;

public:
	float bgmVolume;
	float effectVolume;
private:
	Texture* m_pTex_SettingPannel;
	Texture* m_pTex_arrow;
	Texture* m_pTex_ESC;
	Texture* m_pTex_SoundBar_null;
	Texture* m_pTex_SoundBar;
};