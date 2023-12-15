#include "pch.h"
#include "ShowSetting.h"
#include "Core.h"
#include "KeyMgr.h"
#include "ResMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "Texture.h"
#include "Object.h"

void ShowSetting::Init()
{
	m_pSettingArrowY = 0;
	m_pSettingMoveY = -100;
	m_pSettingYIncrease = 100;

	m_pEscArrowY = 0;
	m_pEscMoveY = -100;
	m_pEscYIncrease = 65;

	#pragma region Texture Load

	m_pTex_SettingPannel = ResMgr::GetInst()->TexLoad(L"Setting", L"Texture\\GameP_Setting.bmp");
	m_pTex_arrow = ResMgr::GetInst()->TexLoad(L"Arrow", L"Texture\\arrow.bmp");
	m_pTex_ESC = ResMgr::GetInst()->TexLoad(L"ESC", L"Texture\\GameP_ESC.bmp");
	m_pTex_SoundBar = ResMgr::GetInst()->TexLoad(L"SoundBar", L"Texture\\SoundBar.bmp");
	m_pTex_SoundBar_null = ResMgr::GetInst()->TexLoad(L"SoundBar_null", L"Texture\\SoundBar_null.bmp");
#pragma endregion
}

void ShowSetting::Render(HDC _dc)
{
	int x = Core::GetInst()->GetResolution().x / 2;
	int y = Core::GetInst()->GetResolution().y / 2;

	if (IsActive)
	{
		TransparentBlt(_dc, x - 430, y - 250, 850, 500, m_pTex_SettingPannel->GetDC(), 0, 0, 
			m_pTex_SettingPannel->GetWidth(), m_pTex_SettingPannel->GetHeight(), RGB(255, 0, 255));
	
		if (m_pSettingMoveY < m_pSettingYIncrease && KEY_DOWN(KEY_TYPE::DOWN))
		{
			m_pSettingMoveY += m_pSettingYIncrease;
		}
		if (m_pSettingMoveY > -m_pSettingYIncrease && KEY_DOWN(KEY_TYPE::UP))
		{
			m_pSettingMoveY -= m_pSettingYIncrease;
		}

		DrawSoundBars(_dc, x, y - 102, 10, 25, 10, m_pBgmVolume);

		DrawSoundBars(_dc, x, y - 5, 10, 25, 10, m_pEffectVolume);


		m_pSettingArrowY = y + m_pSettingMoveY;
		
		TransparentBlt(_dc, x - 170, m_pSettingArrowY, 20, 20, m_pTex_arrow->GetDC(), 0, 0, 
			m_pTex_arrow->GetWidth(), m_pTex_arrow->GetHeight(), RGB(255, 0, 255));

		if (m_pSettingArrowY == 460 && KEY_DOWN(KEY_TYPE::SPACE))
		{
			IsActive = false;
		}
	}
	if (!IsActive && IsEscActive)
	{
		TransparentBlt(_dc, x - 430, y - 250, 850, 500, m_pTex_ESC->GetDC(), 0, 0, 
			m_pTex_ESC->GetWidth(), m_pTex_ESC->GetHeight(), RGB(255, 0, 255));
		if (m_pEscMoveY < 80 && KEY_DOWN(KEY_TYPE::DOWN))
		{
			m_pEscMoveY += m_pEscYIncrease;
		}
		if (m_pEscMoveY > -100 && KEY_DOWN(KEY_TYPE::UP))
		{
			m_pEscMoveY -= m_pEscYIncrease;
		}
		
		m_pEscArrowY = y + m_pEscMoveY;

		TransparentBlt(_dc, x - 170, m_pEscArrowY, 20, 20, m_pTex_arrow->GetDC(), 0, 0, 
			m_pTex_arrow->GetWidth(), m_pTex_arrow->GetHeight(), RGB(255, 0, 255));
	}
}

void ShowSetting::DrawSoundBars(HDC _dc, int x, int y, int width, int height, int totalBars, int volume)
{
	for (int i = 0; i < totalBars; i++)
	{
		TransparentBlt(_dc, x + i * 13, y, width, height, m_pTex_SoundBar_null->GetDC(), 0, 0,
			m_pTex_SoundBar_null->GetWidth(), m_pTex_SoundBar_null->GetHeight(), RGB(255, 255, 255));
	}

	for (int i = 0; i < volume; i++)
	{
		TransparentBlt(_dc, x + i * 13, y, width, height, m_pTex_SoundBar->GetDC(), 0, 0,
			m_pTex_SoundBar->GetWidth(), m_pTex_SoundBar->GetHeight(), RGB(255, 255, 255));
	}
}


void ShowSetting::Update()
{
	if (IsActive) //���� ����â
	{
		if (m_pSettingArrowY == 260)
		{
			AdjustVolume(SOUND_CHANNEL::BGM, m_pBgmVolume);
		}
		else if (m_pSettingArrowY == 360)
		{
			AdjustVolume(SOUND_CHANNEL::EFFECT, m_pEffectVolume);
		}
	}
	else //���� ����â �ʱ�ȭ
	{
		m_pSettingArrowY = 0;
		m_pSettingMoveY = -100;
		m_pSettingYIncrease = 100;
	}

	if (IsEscActive && KEY_DOWN(KEY_TYPE::SPACE)) //����â
	{
		if (m_pEscArrowY == 260) //����ϱ�
		{
			IsEscActive = false;
		}
		if (m_pEscArrowY == 325) //���� �ٽ��ϱ�
		{
			SceneMgr::GetInst()->LoadScene(m_wCurSceneName);
			IsEscActive = false;
		}
		if (m_pEscArrowY == 390) //���� ����
		{
			IsActive = true;
		}
		if (m_pEscArrowY == 455) //���� ������
		{
			SceneMgr::GetInst()->LoadScene(L"Intro_Scene");
			IsEscActive = false;
		}
	}
	if (!IsEscActive) //����â �ʱ�ȭ
	{
		m_pEscArrowY = 0;
		m_pEscMoveY = -100;
		m_pEscYIncrease = 65;
	}
}

void ShowSetting::AdjustVolume(SOUND_CHANNEL channel, float& volume)
{
	if (volume > 0 && KEY_DOWN(KEY_TYPE::LEFT))
	{
		volume -= 1;
	}
	if (volume < 10 && KEY_DOWN(KEY_TYPE::RIGHT))
	{
		volume += 1;
	}
	ResMgr::GetInst()->Volume(channel, volume * 0.1f);
}