#include "pch.h"
#include "Background.h"
#include "Texture.h"

void Background::Update()
{
	m_vPos = m_vFollowPos;
}

void Background::Render(HDC _dc)
{
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();
	TransparentBlt(_dc
		, (int)(m_vPos.x - m_vScale.x / 2)
		, (int)(m_vPos.y - m_vScale.y / 2)
		, Width, Height, m_pTex->GetDC()
		, 0, 0, Width, Height, RGB(255, 0, 255));
}
