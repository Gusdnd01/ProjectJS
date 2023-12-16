#include "pch.h"
#include "Intro_Scene.h"
#include "Object.h"
#include "Core.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "TimeMgr.h"
#include "ShowSetting.h"
#include "ResMgr.h"
#include "Texture.h"
#include "JumpEffect.h"
#include "HitEffect.h"

Intro_Scene::Intro_Scene()
	: m_MoveY(0), m_YIncrease(50), m_ArrowY(0), m_TexSizeX(150), m_TexSizeY(27), m_BtnScale(10)
	, m_fSstart(1), m_fSetting(1), m_fExiT(1)
	, m_pIntroTex(nullptr), m_pGameStart(nullptr), m_pSetting(nullptr), m_pExit(nullptr)
{
}

Intro_Scene::~Intro_Scene()
{
}

void Intro_Scene::Init()
{
	m_pIntroTex = ResMgr::GetInst()->TexLoad(L"IntroBK", L"Texture\\Intro\\Game_Intro.bmp");
	m_pGameStart = ResMgr::GetInst()->TexLoad(L"GameStartTex", L"Texture\\Intro\\GameStart.bmp");
	m_pSetting = ResMgr::GetInst()->TexLoad(L"SettingTex", L"Texture\\Intro\\Setting.bmp");
	m_pExit = ResMgr::GetInst()->TexLoad(L"ExitTex", L"Texture\\Intro\\Exit.bmp");

	ShowSetting::GetInst()->SetSceneName(L"Intro_Scene");
	ResMgr::GetInst()->LoadSound(L"IntroBGM", L"Sound\\IntroBGM.wav", true);
	ResMgr::GetInst()->Play(L"IntroBGM");

}

void Intro_Scene::Render(HDC _dc)
{

	int x = m_BtnScale;
	int y = Core::GetInst()->GetResolution().y / 2 + 150;

	TransparentBlt(_dc, 0, 0, 1280, 750, m_pIntroTex->GetDC(), 0, 0, m_pIntroTex->GetWidth(), m_pIntroTex->GetHeight(), RGB(255, 0, 255));

	Texture* textures[] = { m_pGameStart, m_pSetting, m_pExit };

	for (int i = 0; i < 3; ++i)
	{
		int onlyScaleForStartBtn = 43;
		if (i == 0) x = x + onlyScaleForStartBtn;
		else x = m_BtnScale;

		TransparentBlt(_dc, x, y + m_YIncrease * i, m_TexSizeX * GetTexScale(i), m_TexSizeY * GetTexScale(i),
			textures[i]->GetDC(), 0, 0, textures[i]->GetWidth(), textures[i]->GetHeight(), RGB(255, 0, 255));
	}

	if (!ShowSetting::GetInst()->IsActive)
	{
		m_MoveY = MoveScalePos(y);
	}
}

float Intro_Scene::GetTexScale(int value) const
{
	if (value == m_MoveY / m_YIncrease)
	{
		return 1.25f;
	}
	else
	{
		return 1.0f;
	}
}

int Intro_Scene::MoveScalePos(int y)
{
	int newMoveY = m_MoveY;

	if (newMoveY < 100 && KEY_DOWN(KEY_TYPE::DOWN))
	{
		newMoveY += m_YIncrease;
	}

	if (newMoveY > 0 && KEY_DOWN(KEY_TYPE::UP))
	{
		newMoveY -= m_YIncrease;
	}

	m_ArrowY = y + newMoveY;

	if (m_ArrowY == 510)
	{
		m_fSstart = 1.25f;
		m_fSetting = 1.0f;
		m_fExiT = 1.0f;
	}
	else if (m_ArrowY == 560)
	{
		m_fSstart = 1.0f;
		m_fSetting = 1.25f;
		m_fExiT = 1.0f;
	}
	else
	{
		m_fSstart = 1.0f;
		m_fSetting = 1.0f;
		m_fExiT = 1.25f;
	}

	return newMoveY;
}

void Intro_Scene::Update()
{
	Scene::Update();
	ResMgr::GetInst()->Volume(SOUND_CHANNEL::BGM, ShowSetting::GetInst()->GetBGM());
	ResMgr::GetInst()->Volume(SOUND_CHANNEL::EFFECT, ShowSetting::GetInst()->GetSFX());

	if (!ShowSetting::GetInst()->IsActive && KEY_DOWN(KEY_TYPE::SPACE))
	{
		InputSpaceKey();
	}
}

void Intro_Scene::InputSpaceKey()
{
	if (ShowSetting::GetInst()->IsActive == false)
	{
		switch (m_ArrowY)
		{
		case 510:
			SceneMgr::GetInst()->LoadScene(L"IntroStoryScene");
			break;
		case 560:
			ShowSetting::GetInst()->IsActive = true;
			break;
		default:
			exit(0);
			break;
		}
	}
}

void Intro_Scene::Release()
{
	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
	Scene::Release();
}