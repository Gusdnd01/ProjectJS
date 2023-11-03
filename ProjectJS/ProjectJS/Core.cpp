#include "pch.h"
#include "Core.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneManager.h"
#include "PathManager.h"
#include "ResManager.h"

bool Core::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;
	m_hbackbit = 0;
	m_hbackDC = 0;

	m_hDC = GetDC(m_hWnd);
	
	// 1. 생성
	m_hbackDC = CreateCompatibleDC(m_hDC);
	m_hbackbit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);

	// 2. 연결
	SelectObject(m_hbackDC, m_hbackbit);

	//m_obj.SetPos(Vector2({ m_ptResolution.x / 2, m_ptResolution.y / 2 }));
	//m_obj.SetScale({ 100, 100 });

	//====Managers=====
	PathManager::GetInst()->Init();
	TimeMgr::GetInst()->Init();
	KeyMgr::GetInst()->Init();
	SceneManager::GetInst()->Init();

	return m_hDC != nullptr;
}

void Core::GameLoop()
{
	Update();
	Render();
}

void Core::Update()
{
	//=====Manager Update=====
	TimeMgr::GetInst()->Update();
	KeyMgr::GetInst()->Update();
	SceneManager::GetInst()->Update();
}

void Core::Render()
{
	PatBlt(m_hbackDC, 0,0, m_ptResolution.x, m_ptResolution.y,WHITENESS);
	SceneManager::GetInst()->Render(m_hbackDC);
	// 3. 옮긴다.
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hbackDC, 0, 0, SRCCOPY);
}

void Core::Release()
{
	ReleaseDC(m_hWnd, m_hDC);
	DeleteDC(m_hbackDC);
	DeleteObject(m_hbackbit);
	ResManager::GetInst()->Release();
}
