#include "pch.h"
#include "Core.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "CollisionMgr.h"
#include "EventMgr.h"
#include "ShowSetting.h"
#include "CameraManager.h"
#include "TileManager.h"

bool Core::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;
	m_hbackDC = 0;
	m_hbackbit = 0;

	m_hDC = GetDC(m_hWnd);	
	m_hbackbit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hbackDC = CreateCompatibleDC(m_hDC);

	SelectObject(m_hbackDC, m_hbackbit);

	CreateGDI();
	// ==== Manager Init ====
	PathMgr::GetInst()->Init();
	TimeMgr::GetInst()->Init();
	KeyMgr::GetInst()->Init();
	ResMgr::GetInst()->Init();
	SceneMgr::GetInst()->Init();
	TileManager::GetInst()->Init();
	ShowSetting::GetInst()->Init();
	//SetWindowText(m_hWnd, L"GAEGURIDA!");


	return true;
}

void Core::GameLoop()
{
	Update();
	Render();
}


void Core::Update()
{
	// === Manager Update === 
	TimeMgr::GetInst()->Update();
	KeyMgr::GetInst()->Update();
	SceneMgr::GetInst()->Update();
	CollisionMgr::GetInst()->Update();
	ShowSetting::GetInst()->Update();

//	Vec2 vPos = m_obj.GetPos();
//
////	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
////	if(KeyMgr::GetInst()->GetKey(KEY_TYPE::LEFT) == KEY_STATE::UP)
//	if(KEY_UP(KEY_TYPE::LEFT))
//	{
////		m_obj.m_ptPos.x -= 1;
//		vPos.x -= 100.f;// *fDT;
//	}
//
////	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
//	if(KEY_DOWN(KEY_TYPE::RIGHT))
//	{
////		m_obj.m_ptPos.x += 1;
//		vPos.x += 100.f * fDT;
//	}
//	m_obj.SetPos(vPos);
}

void Core::Render()
{
	// ĥ�Ѵ�.
	//Rectangle(m_hbackDC, -1,-1,m_ptResolution.x +1,m_ptResolution.y + 1);
	PatBlt(m_hbackDC, 0, 0, m_ptResolution.x, m_ptResolution.y, WHITENESS);

	CameraManager::GetInst()->Update();

	SceneMgr::GetInst()->Render(m_hbackDC);
	ShowSetting::GetInst()->Render(m_hbackDC);

	/*Vec2 vPos = m_obj.GetPos();
	Vec2 vScale = m_obj.GetScale();
	RECT_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, m_hbackDC);*/

	//// cursor test
	//POINT mousepos = KeyMgr::GetInst()->GetMousePos();
	//static wchar_t mousebuf[100] = {};
	//swprintf_s(mousebuf, L"Mouse: x %d, y: %d", mousepos.x, mousepos.y);
	//TextOut(m_hbackDC, 10, 10, mousebuf, wcslen(mousebuf));

	// 3. �ű��.
	BitBlt(m_hDC, 0,0, m_ptResolution.x, m_ptResolution.y, 
		m_hbackDC, 0,0, SRCCOPY);
	EventMgr::GetInst()->Update();

	//TransparentBlt();
	//StretchBlt();
	// 
	//RECT_RENDER(m_obj.m_ptPos.x, m_obj.m_ptPos.y, m_obj.m_ptScale.x, m_obj.m_ptScale.y, m_hDC);
	//Rectangle(m_hDC
	//	, m_obj.m_ptPos.x - ERROR_CANT_CROSS_RM_BOUNDARY,50,150,150);
}

void Core::CreateGDI()
{
	// HOLLOW
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::RED] = (HBRUSH)CreateSolidBrush(RGB(255, 167, 167));
	m_arrBrush[(UINT)BRUSH_TYPE::GREEN] = (HBRUSH)CreateSolidBrush(RGB(134, 229, 134));
	m_arrBrush[(UINT)BRUSH_TYPE::BLUE] = (HBRUSH)CreateSolidBrush(RGB(103, 153, 255));
	m_arrBrush[(UINT)BRUSH_TYPE::YELLOW] = (HBRUSH)CreateSolidBrush(RGB(255, 187, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));

	//RED GREEN BLUE PEN
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::HOLLOW] = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::BLACK] = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
}

void Core::Release()
{
	ReleaseDC(m_hWnd, m_hDC);
	DeleteDC(m_hbackDC); // createdc �Ѱ� ����°�
	DeleteObject(m_hbackbit); // createbit �Ѱ� ����°�
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
	for (int i = 1; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		DeleteObject(m_arrBrush[i]);
	}

	ResMgr::GetInst()->Release();
}
