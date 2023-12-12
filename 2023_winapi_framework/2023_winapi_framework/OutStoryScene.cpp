#include "pch.h"
#include "OutStoryScene.h"
#include "ShowSetting.h"
#include "KeyMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "SceneMgr.h"

void OutStoryScene::Init()
{
	m_ImgCnt = 0;
	ShowSetting::GetInst()->IsEscActive == false;
	ShowSetting::GetInst()->CurSceneName = L"OutStoryScene";

	m_BK = ResMgr::GetInst()->TexLoad(L"BK", L"Texture\\BLACKBK.bmp");
	m_Story1 = ResMgr::GetInst()->TexLoad(L"OutStory1", L"Texture\\OutStory\\OutStory1.bmp");
	m_Story2 = ResMgr::GetInst()->TexLoad(L"OutStory2", L"Texture\\OutStory\\OutStory2.bmp");
	m_Story3 = ResMgr::GetInst()->TexLoad(L"OutStory3", L"Texture\\OutStory\\OutStory3.bmp");
	m_Story4 = ResMgr::GetInst()->TexLoad(L"OutStory4", L"Texture\\OutStory\\OutStory4.bmp");
}

void OutStoryScene::Render(HDC _dc)
{
	if (KEY_DOWN(KEY_TYPE::ESC))
	{
		ShowSetting::GetInst()->IsEscActive = true;
	}

	if (KEY_DOWN(KEY_TYPE::SPACE) && ShowSetting::GetInst()->IsEscActive == false)
	{
		m_ImgCnt++;
	}

	TransparentBlt(_dc, 0, 0, 1280, 720, m_BK->GetDC(), 0, 0, m_BK->GetWidth(), m_BK->GetHeight(), RGB(255, 255, 255));

	if (m_ImgCnt == 1)
	{
		TransparentBlt(_dc, 0, 0, 1280, 720, m_Story1->GetDC(), 0, 0, m_Story1->GetWidth(), m_Story1->GetHeight(), RGB(255, 0, 255));
	}

	if (m_ImgCnt == 2)
	{
		TransparentBlt(_dc, 0, 0, 1280, 720, m_Story2->GetDC(), 0, 0, m_Story2->GetWidth(), m_Story2->GetHeight(), RGB(255, 0, 255));
	}

	if (m_ImgCnt == 3)
	{
		TransparentBlt(_dc, 0, 0, 1280, 720, m_Story3->GetDC(), 0, 0, m_Story3->GetWidth(), m_Story3->GetHeight(), RGB(255, 0, 255));
	}

	if (m_ImgCnt == 4)
	{
		m_Clear = true;
		TransparentBlt(_dc, 0, 0, 1280, 720, m_Story4->GetDC(), 0, 0, m_Story4->GetWidth(), m_Story4->GetHeight(), RGB(255, 0, 255));
	}
	if (m_ImgCnt == 6)
	{
		SceneMgr::GetInst()->LoadScene(L"Intro_Scene");
	}
}

void OutStoryScene::Release()
{

}