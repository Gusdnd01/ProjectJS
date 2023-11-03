#pragma once
// �ϳ���, ��𼭵� �����־����.
// �̱����� �����ϴ� ����� ��û ����
// 1�б⶧ �ߴ��� ���̳��� �̱��� = �����Ҵ�
// ����: �������� �ʴ��� �ٽ� ������ �� �ִ�.
// ����: �������� �Ҵ��ϱ⿡ ���Ÿ� ������Ѵ�.
//private:
//	static Core* m_pInst;
//public:
//	static Core* GetInst()
//	{
//		if (m_pInst == nullptr)
//			m_pInst = new Core;
//		return m_pInst;
//	}
//public:
//	static void DestroyInst()
//	{
//		SAFE_DELETE(m_pInst);

// ����(static)�Ҵ�.
#include "define.h"
#include "Object.h"
class Core
{
	SINGLE(Core);
public:
	bool Init(HWND _hWnd, POINT _ptResolution);
	void GameLoop();
	void Release();

public:
	const HWND& GetHWnd() const{ return m_hWnd; }
	const POINT& GetResolution() const {
		return m_ptResolution;
	}

	const HDC& GetMainDC() const {
		return m_hDC;
	}
	const HPEN& GetHPen(PEN_GROUP type) { return m_hPen[static_cast<UINT>(type)]; }

private:
	void Update();
	void Render();

private:
	void CreatePens();

private:
	HWND	m_hWnd;
	HDC		m_hDC; //���� DC
	HDC		m_hbackDC; //�� ���� DC
	HBITMAP m_hbackbit; //�� ���ۿ� �׸� bmp
	POINT	m_ptResolution; //�ػ�
	HPEN	m_hPen[static_cast<UINT>(PEN_GROUP::END)]; //�̸� �����ص� �ҵ�?
};

