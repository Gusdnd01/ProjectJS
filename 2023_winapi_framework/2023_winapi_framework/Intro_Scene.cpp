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
	: m_MoveY(0), m_YIncrease(50), m_ArrowY(0), m_TexSizeX(150), m_TexSizeY(27)
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

	ResMgr::GetInst()->LoadSound(L"IntroBGM", L"Sound\\IntroBGM.wav", true);
	ResMgr::GetInst()->Play(L"IntroBGM");
	
}

void Intro_Scene::Render(HDC _dc)
{

	int x = 10;
	int y = Core::GetInst()->GetResolution().y / 2 + 150;

	TransparentBlt(_dc, 0, 0, 1280, 750, m_pIntroTex->GetDC(), 0, 0, m_pIntroTex->GetWidth(), m_pIntroTex->GetHeight(), RGB(255, 0, 255));
	TransparentBlt(_dc, x + 40, y, m_TexSizeX * m_fSstart, m_TexSizeY * m_fSstart, m_pGameStart->GetDC(), 0, 0, m_pGameStart->GetWidth(), m_pGameStart->GetHeight(), RGB(255, 0, 255));
	TransparentBlt(_dc, x, y + m_YIncrease, m_TexSizeX * m_fSetting, m_TexSizeY * m_fSetting, m_pSetting->GetDC(), 0, 0, m_pSetting->GetWidth(), m_pSetting->GetHeight(), RGB(255, 0, 255));
	TransparentBlt(_dc, x, y + m_YIncrease * 2, m_TexSizeX * m_fExiT, m_TexSizeY * m_fExiT, m_pExit->GetDC(), 0, 0, m_pExit->GetWidth(), m_pExit->GetHeight(), RGB(255, 0, 255));

	if (ShowSetting::GetInst()->IsActive == false)
	{
		if (m_MoveY < 100 && KEY_DOWN(KEY_TYPE::DOWN))
		{
			m_MoveY += m_YIncrease;
		}
		if (m_MoveY > 0 && KEY_DOWN(KEY_TYPE::UP))
		{
			m_MoveY -= m_YIncrease;
		}
	}

	m_ArrowY = y + m_MoveY;

	switch (m_ArrowY)
	{
	case 510:
	{
		m_fSstart = 1.25f;
		m_fSetting = 1;
		m_fExiT = 1;
	}
	break;
	case 560:
	{
		m_fSstart = 1;
		m_fSetting = 1.25f;
		m_fExiT = 1;
	}
	break;
	default:
	{
		m_fSstart = 1;
		m_fSetting = 1;
		m_fExiT = 1.25f;
	}
	break;
	}
}

void Intro_Scene::Update()
{
	Scene::Update();
	ResMgr::GetInst()->Volume(SOUND_CHANNEL::BGM, ShowSetting::GetInst()->GetBGM());
	ResMgr::GetInst()->Volume(SOUND_CHANNEL::EFFECT, ShowSetting::GetInst()->GetSFX());
	if (KEY_DOWN(KEY_TYPE::P))
	{
		Object* effect = new JumpEffect;
		effect->SetName(L"JumpEffect");
		effect->SetScale(Vec2(3, 3));
		effect->SetPos(Vec2(50, 50));
		AddObject(effect, OBJECT_GROUP::DEFAULT);
	}

	if (ShowSetting::GetInst()->IsActive == false && KEY_DOWN(KEY_TYPE::SPACE))
	{
		switch (m_ArrowY)
		{
		case 510:
		{
			SceneMgr::GetInst()->LoadScene(L"IntroStoryScene");
		}
		break;
		case 560:
		{
			ShowSetting::GetInst()->IsActive = true;
		}
		break;
		default:
		{
			exit(0);
		}
		break;
		}
	}
}

void Intro_Scene::Release()
{
	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
	Scene::Release();
}