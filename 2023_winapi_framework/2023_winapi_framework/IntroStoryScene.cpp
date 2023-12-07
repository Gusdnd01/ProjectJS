#include "pch.h"
#include "IntroStoryScene.h"
#include "KeyMgr.h"
#include "ShowSetting.h"
#include "ResMgr.h"
#include "Texture.h"
#include "SceneMgr.h"

void IntroStoryScene::Init()
{
	m_ImgCnt = 0;
	m_Clear = false;
	ShowSetting::GetInst()->IsEscActive == false;
	ShowSetting::GetInst()->GetBGM();
	ShowSetting::GetInst()->CurSceneName = L"IntroStoryScene";

	m_Story1 = ResMgr::GetInst()->TexLoad(L"Story1", L"Texture\\IntroStory\\Story1.bmp");
	m_Story2 = ResMgr::GetInst()->TexLoad(L"Story2", L"Texture\\IntroStory\\Story2.bmp");
	m_Story3 = ResMgr::GetInst()->TexLoad(L"Story3", L"Texture\\IntroStory\\Story3.bmp");
	m_Story4 = ResMgr::GetInst()->TexLoad(L"Story4", L"Texture\\IntroStory\\Story4.bmp");
	m_Story5 = ResMgr::GetInst()->TexLoad(L"Story5", L"Texture\\IntroStory\\Story5.bmp");

	ResMgr::GetInst()->LoadSound(L"IntroBGM", L"Sound\\IntroBGM.wav", true);
	ResMgr::GetInst()->Play(L"IntroBGM");
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

	if (m_ImgCnt > 1 && !m_Clear)
	{
		TransparentBlt(_dc, x, 5, 550, 340, m_Story1->GetDC(), 0,0,500, 285, RGB(255,0,255));
	}

	if (m_ImgCnt > 2 && !m_Clear)
	{
		TransparentBlt(_dc, 700, 5, 520, 340, m_Story2->GetDC(), 0, 0, 473, 285, RGB(255, 0, 255));
	}

	if (m_ImgCnt > 3 && !m_Clear)
	{
		TransparentBlt(_dc, x, 370, 550, 340, m_Story3->GetDC(), 0, 0, 473, 285, RGB(255, 0, 255));
	}

	if (m_ImgCnt > 4 && !m_Clear)
	{
		TransparentBlt(_dc, 700, 370, 520, 340, m_Story4->GetDC(), 0, 0, 469, 285, RGB(255, 0, 255));
	}

	if (m_ImgCnt == 6)
	{
		m_Clear = true;
		TransparentBlt(_dc, 280, 15, 700, 671, m_Story5->GetDC(), 0, 0, 527, 498, RGB(255, 0, 255));
	}
	if (m_ImgCnt == 7)
	{
		SceneMgr::GetInst()->LoadScene(L"Start_Scene");
	}
}

void IntroStoryScene::Release()
{
	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
}