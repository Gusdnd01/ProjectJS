#include "pch.h"
#include "IntroStoryScene.h"
#include "KeyMgr.h"
#include "ShowSetting.h"
#include "ResMgr.h"
#include "Texture.h"
#include "SceneMgr.h"

IntroStoryScene::IntroStoryScene()
	: m_ImgCnt(0), m_bClear(false)
	, m_pStory1(nullptr), m_pStory2(nullptr)
	, m_pStory3(nullptr), m_pStory4(nullptr)
	, m_pStory5(nullptr), m_pBK(nullptr)
{
}

IntroStoryScene::~IntroStoryScene()
{
}

void IntroStoryScene::Init()
{
	ShowSetting::GetInst()->IsEscActive = false;
	ShowSetting::GetInst()->CurSceneName = L"IntroStoryScene";

	m_pStory1 = ResMgr::GetInst()->TexLoad(L"Story1", L"Texture\\IntroStory\\Story1.bmp");
	m_pStory2 = ResMgr::GetInst()->TexLoad(L"Story2", L"Texture\\IntroStory\\Story2.bmp");
	m_pStory3 = ResMgr::GetInst()->TexLoad(L"Story3", L"Texture\\IntroStory\\Story3.bmp");
	m_pStory4 = ResMgr::GetInst()->TexLoad(L"Story4", L"Texture\\IntroStory\\Story4.bmp");
	m_pStory5 = ResMgr::GetInst()->TexLoad(L"Story5", L"Texture\\IntroStory\\Story5.bmp");
	m_pBK = ResMgr::GetInst()->TexLoad(L"BK", L"Texture\\BLACKBK.bmp");

	ResMgr::GetInst()->LoadSound(L"IntroStoryBGM", L"Sound\\IntroStoryBGM.wav", true);
	ResMgr::GetInst()->Play(L"IntroStoryBGM");

	ResMgr::GetInst()->Volume(SOUND_CHANNEL::BGM, ShowSetting::GetInst()->GetBGM());
	ResMgr::GetInst()->Volume(SOUND_CHANNEL::EFFECT, ShowSetting::GetInst()->GetSFX());
}

void IntroStoryScene::Render(HDC _dc)
{
	int x = 60;
	int y = 10;

	if (KEY_DOWN(KEY_TYPE::ESC))
	{
		ShowSetting::GetInst()->IsEscActive = true;
	}

	if (KEY_DOWN(KEY_TYPE::SPACE) && ShowSetting::GetInst()->IsEscActive == false)
	{
		m_ImgCnt++;
	}

	TransparentBlt(_dc, 0, 0, 1280, 720, m_pBK->GetDC(), 0, 0, m_pBK->GetWidth(), m_pBK->GetHeight(), RGB(255, 255, 255));

	if (m_ImgCnt > 1 && !m_bClear)
	{
		TransparentBlt(_dc, x, 5, 550, 340, m_pStory1->GetDC(), 0, 0, m_pStory1->GetWidth(), m_pStory1->GetHeight(), RGB(255, 0, 255));
	}

	if (m_ImgCnt > 2 && !m_bClear)
	{
		TransparentBlt(_dc, 700, 5, 520, 340, m_pStory2->GetDC(), 0, 0, m_pStory2->GetWidth(), m_pStory2->GetHeight(), RGB(255, 0, 255));
	}

	if (m_ImgCnt > 3 && !m_bClear)
	{
		TransparentBlt(_dc, x, 370, 550, 340, m_pStory3->GetDC(), 0, 0, m_pStory3->GetWidth(), m_pStory3->GetHeight(), RGB(255, 0, 255));
	}

	if (m_ImgCnt > 4 && !m_bClear)
	{
		TransparentBlt(_dc, 700, 370, 520, 340, m_pStory4->GetDC(), 0, 0, m_pStory4->GetWidth(), m_pStory4->GetHeight(), RGB(255, 0, 255));
	}

	if (m_ImgCnt == 6)
	{
		m_bClear = true;
		TransparentBlt(_dc, 280, 15, 700, 671, m_pStory5->GetDC(), 0, 0, m_pStory5->GetWidth(), m_pStory5->GetHeight(), RGB(255, 0, 255));
	}
	if (m_ImgCnt == 7)
	{
		SceneMgr::GetInst()->LoadScene(L"Start_Scene");
	}
}

void IntroStoryScene::Release()
{
	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
	Scene::Release();
}