#pragma once

#include "ResMgr.h"
#include "Texture.h"

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

public:
	void SetSceneName(const wstring& value) { m_wCurSceneName = value; }
	const float GetBGM() { return m_pBgmVolume * .1f; }
	const float GetSFX() { return m_pEffectVolume * .1f; }

private:
	void AdjustVolume(SOUND_CHANNEL channel, float& volume);
	void DrawSoundBars(HDC _dc, int x, int y, int width, int height, int totalBars, int volume);

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
	wstring m_wCurSceneName;

private:
	Texture* m_pTex_SettingPannel;
	Texture* m_pTex_arrow;
	Texture* m_pTex_ESC;
	Texture* m_pTex_SoundBar_null;
	Texture* m_pTex_SoundBar;
};