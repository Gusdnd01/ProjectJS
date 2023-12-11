#pragma once
class Texture;
class Object;
class ResMgr;
class ShowSetting
{
	SINGLE(ShowSetting);
public:
	bool IsActive = false;
	bool IsEscActive = false;

	wstring  CurSceneName;
public:
	void Init();
	void Render(HDC _dc);
	void Update();
public:
	const float GetBGM() { return bgmVolume; }
	const float GetSFX() { return effectVolume; }
private:
	int settingMoveY;
	int settingYIncrease;
	int settingArrowY;

	int escMoveY;
	int escYIncrease;
	int escArrowY;
private:
	float bgmVolume;
	float effectVolume;
private:
	Texture* m_pTex_SettingPannel;
	Texture* m_pTex_arrow;
	Texture* m_pTex_ESC;
	Texture* m_pTex_SoundBar_null;
	Texture* m_pTex_SoundBar;
};