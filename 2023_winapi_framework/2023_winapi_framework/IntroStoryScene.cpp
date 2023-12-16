#include "pch.h"
#include "IntroStoryScene.h"
#include "KeyMgr.h"
#include "ShowSetting.h"
#include "ResMgr.h"
#include "Texture.h"
#include "SceneMgr.h"

IntroStoryScene::IntroStoryScene()
	: m_ImgCnt(-1), m_bClear(false),
	m_pStoryTextures(), m_pBK(nullptr)
{
}

IntroStoryScene::~IntroStoryScene()
{
}

void IntroStoryScene::Init()
{
	ShowSetting::GetInst()->IsEscActive = false;
    ShowSetting::GetInst()->SetSceneName(L"IntroStoryScene");

	m_pStoryTextures.push_back(ResMgr::GetInst()->TexLoad(L"Story1", L"Texture\\IntroStory\\Story1.bmp"));
	m_pStoryTextures.push_back(ResMgr::GetInst()->TexLoad(L"Story2", L"Texture\\IntroStory\\Story2.bmp"));
	m_pStoryTextures.push_back(ResMgr::GetInst()->TexLoad(L"Story3", L"Texture\\IntroStory\\Story3.bmp"));
	m_pStoryTextures.push_back(ResMgr::GetInst()->TexLoad(L"Story4", L"Texture\\IntroStory\\Story4.bmp"));
	m_pStoryTextures.push_back(ResMgr::GetInst()->TexLoad(L"Story5", L"Texture\\IntroStory\\Story5.bmp"));

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

    for (int i = 1; i <= m_ImgCnt && i < m_pStoryTextures.size(); ++i)
    {
        if (!m_bClear)
        {
            int xPos = (i % 2 == 0) ? 700 : x;
            int yPos = (i > 2) ? 370 : 5;

            TransparentBlt(_dc, xPos, yPos, 520, 340, m_pStoryTextures[i - 1]->GetDC(), 0, 0,
                m_pStoryTextures[i - 1]->GetWidth(), m_pStoryTextures[i - 1]->GetHeight(), RGB(255, 0, 255));
        }
    }

    if (m_ImgCnt == 5) m_bClear = true;

    if (m_ImgCnt == 6)
    {
        TransparentBlt(_dc, 280, 15, 700, 671, m_pStoryTextures.back()->GetDC(), 0, 0,
            m_pStoryTextures.back()->GetWidth(), m_pStoryTextures.back()->GetHeight(), RGB(255, 0, 255));
    }

    if (m_ImgCnt == 7)
    {
        SceneMgr::GetInst()->LoadScene(L"Start_Scene");
    }
}

void IntroStoryScene::Release()
{
    m_ImgCnt = -1;
    m_bClear = false;
    m_pStoryTextures.clear();
    m_pBK = nullptr;

	ResMgr::GetInst()->Stop(SOUND_CHANNEL::BGM);
	Scene::Release();
}