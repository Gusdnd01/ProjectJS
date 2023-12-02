#include "pch.h"
#include "IntroStoryScene.h"
#include "KeyMgr.h"
#include "ShowSetting.h"
#include "ResMgr.h"

void IntroStoryScene::Init()
{
	m_ImgCnt = 0;
	ShowSetting::GetInst()->IsEscActive == false;
	ShowSetting::GetInst()->CurSceneName = L"IntroStoryScene";

	ResMgr::GetInst()->LoadSound(L"IntroBGM", L"Sound\\IntroBGM.wav", true);
	ResMgr::GetInst()->Play(L"IntroBGM");
}

void IntroStoryScene::Render(HDC _dc)
{

	if (KEY_DOWN(KEY_TYPE::ESC))
	{
		ShowSetting::GetInst()->IsEscActive = true;
	}

	if (KEY_DOWN(KEY_TYPE::SPACE))
	{
		m_ImgCnt++;
	}

	if (m_ImgCnt > 1)
	{
		//이미지 1
	}

	if (m_ImgCnt > 2)
	{
		//이미지 2
	}

	if (m_ImgCnt > 3)
	{
		//이미지 3
	}

	if (m_ImgCnt > 4)
	{
		//이미지 4
	}
}

void IntroStoryScene::Release()
{
	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
}