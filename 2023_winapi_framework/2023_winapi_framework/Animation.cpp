#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "Object.h"
#include "Texture.h"
#include "TimeMgr.h"
#include "CameraManager.h"
#include "Core.h"
Animation::Animation()
	: m_pAnimator(nullptr)
	, m_CurFrame(0)
	, m_pTex(nullptr)
	, m_fAccTime(0.f)
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (m_pAnimator->GetRepeatcnt() <= 0)
		return;
	m_fAccTime += fDT;
	// 누적한 시간이 내가 이 프레임에 진행한 시간을 넘어섰냐?
	if (m_fAccTime >= m_vecAnimFrame[m_CurFrame].fDuration)
	{
		// 일단 모은 시간에서 현재 진행한 시간을 빼고
		m_fAccTime -= m_vecAnimFrame[m_CurFrame].fDuration;
		++m_CurFrame; // 다음프레임으로 옮기기
		if (m_CurFrame >= m_vecAnimFrame.size()) // 한바퀴 돌게하고싶어
		{
			if (!m_pAnimator->GetRepeat())
				m_pAnimator->SetRepeatcnt();
			m_CurFrame = 0;
			m_fAccTime = 0.f;
		}

	}
}

void Animation::Render(HDC _dc)
{
	Object* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	Vec2 vScale = pObj->GetScale();
	Vec2 resolution = Core::GetInst()->GetResolution();

	if (vPos.y - vScale.y / 2.f > CameraManager::GetInst()->GetLookPos().y + resolution.y / 2.f ||
		vPos.y + vScale.y / 2.f < CameraManager::GetInst()->GetLookPos().y - resolution.y / 2.f) return;
	Vec2 renderPos = CameraManager::GetInst()->GetRenderPos(vPos);

	// 오프셋 적용
	renderPos = renderPos + m_vecAnimFrame[m_CurFrame].vOffset;
	HBITMAP _backbit = CreateCompatibleBitmap(_dc, Core::GetInst()->GetResolution().x, Core::GetInst()->GetResolution().y);
	HDC _backDC = CreateCompatibleDC(_dc);
	SelectObject(_backDC, _backbit);
	PatBlt(_backDC, 0, 0, Core::GetInst()->GetResolution().x, Core::GetInst()->GetResolution().y, WHITENESS);
	StretchBlt(_backDC
		,0
		,0
		, (int)(m_vecAnimFrame[m_CurFrame].vSlice.x) * vScale.x
		, (int)(m_vecAnimFrame[m_CurFrame].vSlice.y) * vScale.y
		, m_pTex->GetDC()
		, (int)(m_vecAnimFrame[m_CurFrame].vLT.x)
		, (int)(m_vecAnimFrame[m_CurFrame].vLT.y)
		, (int)(m_vecAnimFrame[m_CurFrame].vSlice.x)
		, (int)(m_vecAnimFrame[m_CurFrame].vSlice.y), SRCCOPY);

	TransparentBlt(_dc
		,(int)(renderPos.x - m_vecAnimFrame[m_CurFrame].vSlice.x /2.f * vScale.x)
		,(int)(renderPos.y - m_vecAnimFrame[m_CurFrame].vSlice.y / 2.f * vScale.y)
		,(int)(m_vecAnimFrame[m_CurFrame].vSlice.x) * vScale.x
		,(int)(m_vecAnimFrame[m_CurFrame].vSlice.y) * vScale.y
		,_backDC
		,0
		,0
		,(int)(m_vecAnimFrame[m_CurFrame].vSlice.x) * vScale.x
		,(int)(m_vecAnimFrame[m_CurFrame].vSlice.y) * vScale.y
		,RGB(255,0,255));

	DeleteObject(_backbit);
	DeleteDC(_backDC);
}

void Animation::Create(Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, int _framecount, float _fDuration)
{
	m_pTex = _pTex;
	for (int i = 0; i < _framecount; ++i)
	{
		m_vecAnimFrame.push_back(tAnimFrame({ _vLT + _vStep * i,
			_vSliceSize, _fDuration,{0.f,0.f} }));
	}

}
