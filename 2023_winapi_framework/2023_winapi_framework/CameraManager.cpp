#include "pch.h"
#include "CameraManager.h"
#include "TimeMgr.h"
#include "Object.h"
#include "Core.h"

void CameraManager::Update()
{
	//타겟이 없으면 정중앙을 보게 한다.
	if (m_pTarget == nullptr) {
		m_vLookPos = Vec2((int)Core::GetInst()->GetResolution().x / 2, (int)Core::GetInst()->GetResolution().y / 2);
	}
	else {
		//게임 특성상 아무래도 상승 운동만 존재할테니 x값은 똑같이 정중앙을 바라본다.

		//게임의 특성상 특정 위치 이상을 올라가면 다른 Target의 y값을 가져오거나 Target의 위치를 변경해준다.
		m_vLookPos = Vec2((int)Core::GetInst()->GetResolution().x / 2,
			(int)m_pTarget->GetPos().y);
	}

	CaculateDiff();
}

void CameraManager::CaculateDiff()
{
	//원래 존재해야했던 보정효과가 필요없으니 딱딱하게 움직이게 한다.
	Vec2 resolution = Core::GetInst()->GetResolution();
	Vec2 centerPos = resolution / 2.0f;

	Vec2 vLookDir = m_vLookPos - (m_vPrevLookPos);

	m_vDiffPos = m_vLookPos - centerPos;
}

Vec2 CameraManager::GetRenderPos(const Vec2& _value)
{
	return (m_vDiffPos - _value) * -1;
}
