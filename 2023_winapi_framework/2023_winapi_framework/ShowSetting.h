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
	const float GetBGM() { return bgmVolume * .1f; }
	const float GetSFX() { return effectVolume * .1f; }
private:
	void SoundBoxUI(int x, int y, int volume, HDC _dc);
private:
	int m_pSettingMoveY;
	int m_pSettingYIncrease;
	int m_pSettingArrowY;

	int m_pEscMoveY;
	int m_pEscYIncrease;
	int m_pEscArrowY;
private:
	float m_pBgmVolume;
	float m_pEffectVolume;
private:
	Texture* m_pTex_SettingPannel;
	Texture* m_pTex_arrow;
	Texture* m_pTex_ESC;
	Texture* m_pTex_SoundBar_null;
	Texture* m_pTex_SoundBar;
};