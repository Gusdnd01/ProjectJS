#include "pch.h"
#include "Animation.h"
#include "Texture.h"
#include "Object.h"
#include "Animator.h"
#include "TimeMgr.h"

Animation::Animation()
	: m_animator(nullptr)
	, m_curFrame(0)
	, m_pTex(nullptr)
	, m_fAccTime(0.f)
	, m_repeatCnt(1)
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	m_fAccTime += fDT;
	if (m_fAccTime >= m_vecAnimFrame[m_curFrame].fDuration) {
		m_fAccTime -= m_vecAnimFrame[m_curFrame].fDuration;
		++m_curFrame;
		if (m_curFrame >= m_vecAnimFrame.size()) {
			m_curFrame = 0;
			m_fAccTime = 0.f;
		}
	}
}

void Animation::Render(HDC _dc)
{
	Object* pObj = m_animator->GetOwner();
	Vec2 pos = pObj->GetPos();
	GdiTransparentBlt(_dc,
		(int)(pos.x - m_vecAnimFrame[m_curFrame].vSlice.x / 2.f),
		(int)(pos.y - m_vecAnimFrame[m_curFrame].vSlice.y / 2.f),
		(int)(m_vecAnimFrame[m_curFrame].vSlice.x),
		(int)(m_vecAnimFrame[m_curFrame].vSlice.y),
		m_pTex->GetDC(),
		(int)(m_vecAnimFrame[m_curFrame].vLT.x),
		(int)(m_vecAnimFrame[m_curFrame].vLT.y),
		(int)(m_vecAnimFrame[m_curFrame].vSlice.x),
		(int)(m_vecAnimFrame[m_curFrame].vSlice.y),
		RGB(255, 0, 255)
	);
}

void Animation::Create(Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _frameCount, float _fDuration)
{
	m_pTex = _pTex;
	for (int i = 0; i < _frameCount; ++i) {
		m_vecAnimFrame.push_back(tAnimFrame({ _vLT + _vStep * i, _vSliceSize, _fDuration }));
	}
}
