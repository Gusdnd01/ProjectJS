#include "pch.h"
#include "Core.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "PathManager.h"
#include "ResourceManager.h"

bool Core::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;
	m_hbackbit = 0;
	m_hbackDC = 0;

	m_hDC = GetDC(m_hWnd);
	
	//뒤에 그릴 디시랑 비트맵 생성
	m_hbackDC = CreateCompatibleDC(m_hDC);
	m_hbackbit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);

	//디시한테 비트맵 쥐어주기
	SelectObject(m_hbackDC, m_hbackbit);

	//====Managers=====
	GETINST(PathManager)->Init();
	GETINST(TimeManager)->Init();
	GETINST(KeyManager)->Init();
	GETINST(SceneManager)->Init();

	//===About-Draw====
	CreatePens();

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
	GETINST(TimeManager)->Update();
	GETINST(KeyManager)->Update();
	GETINST(SceneManager)->Update();
}

void Core::Render()
{
	PatBlt(m_hbackDC, 0,0, m_ptResolution.x, m_ptResolution.y,WHITENESS);
	GETINST(SceneManager)->Render(m_hbackDC);

	//여기서 옮기는 작업을 함
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hbackDC, 0, 0, SRCCOPY);
}

void Core::Release()
{
	ReleaseDC(m_hWnd, m_hDC);
	DeleteDC(m_hbackDC);
	DeleteObject(m_hbackbit);
	GETINST(ResourceManager)->Release();
}

void Core::CreatePens()
{
	m_hPen[static_cast<UINT>(PEN_GROUP::RED)] = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	m_hPen[static_cast<UINT>(PEN_GROUP::BLUE)] = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
	m_hPen[static_cast<UINT>(PEN_GROUP::GREEN)] = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
}