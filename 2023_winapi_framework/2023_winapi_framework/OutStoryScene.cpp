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
	ShowSetting::GetInst()->IsEscActive = false;
	ShowSetting::GetInst()->SetSceneName(L"OutStoryScene");

	m_BK = ResMgr::GetInst()->TexLoad(L"BK", L"Texture\\BLACKBK.bmp");
	m_vStoryTexture.push_back(ResMgr::GetInst()->TexLoad(L"OutStory1", L"Texture\\OutStory\\OutStory1.bmp"));
	m_vStoryTexture.push_back(ResMgr::GetInst()->TexLoad(L"OutStory2", L"Texture\\OutStory\\OutStory2.bmp"));
	m_vStoryTexture.push_back(ResMgr::GetInst()->TexLoad(L"OutStory3", L"Texture\\OutStory\\OutStory3.bmp"));
	m_vStoryTexture.push_back(ResMgr::GetInst()->TexLoad(L"OutStory4", L"Texture\\OutStory\\OutStory4.bmp"));
	m_vStoryTexture.push_back(ResMgr::GetInst()->TexLoad(L"Cradit1", L"Texture\\OutStory\\Cradit1.bmp"));
	m_vStoryTexture.push_back(ResMgr::GetInst()->TexLoad(L"Cradit", L"Texture\\OutStory\\Cradit.bmp"));
}

void OutStoryScene::Render(HDC _dc)
{
	if (KEY_DOWN(KEY_TYPE::ESC))
	{
		ShowSetting::GetInst()->IsEscActive = true;
	}

	if (KEY_DOWN(KEY_TYPE::SPACE) && ShowSetting::GetInst()->ShowSetting::GetInst()->IsEscActive==false)
	{
		m_ImgCnt++;
	}

	TransparentBlt(_dc, 0, 0, 1280, 720, m_BK->GetDC(), 0, 0, m_BK->GetWidth(), m_BK->GetHeight(), RGB(255, 255, 255));

	TransparentBlt(_dc, 0, 0, 1280, 720, m_BK->GetDC(), 0, 0, m_BK->GetWidth(), m_BK->GetHeight(), RGB(255, 255, 255));

	if (m_ImgCnt >= 1 && m_ImgCnt <= m_vStoryTexture.size())
	{
		Texture* currentStory = m_vStoryTexture[m_ImgCnt - 1];
		TransparentBlt(_dc, 0, 0, 1280, 720, currentStory->GetDC(), 0, 0, currentStory->GetWidth(), currentStory->GetHeight(), RGB(255, 0, 255));
	}

	if (m_ImgCnt == 8)
	{
		SceneMgr::GetInst()->LoadScene(L"Intro_Scene");
	}
}

void OutStoryScene::Release()
{
	m_ImgCnt = 0;
	m_vStoryTexture.clear();
	m_BK = nullptr;
}