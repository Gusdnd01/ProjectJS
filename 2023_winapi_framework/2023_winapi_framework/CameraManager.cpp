#include "pch.h"
#include "CameraManager.h"
#include "TimeMgr.h"
#include "Object.h"
#include "Core.h"

void CameraManager::Update()
{
	//Ÿ���� ������ ���߾��� ���� �Ѵ�.
	if (m_pTarget == nullptr) {
		m_vLookPos = Vec2((int)Core::GetInst()->GetResolution().x / 2, (int)Core::GetInst()->GetResolution().y / 2);
	}
	else {
		//���� Ư���� �ƹ����� ��� ��� �������״� x���� �Ȱ��� ���߾��� �ٶ󺻴�.

		//������ Ư���� Ư�� ��ġ �̻��� �ö󰡸� �ٸ� Target�� y���� �������ų� Target�� ��ġ�� �������ش�.
		m_vLookPos = Vec2((int)Core::GetInst()->GetResolution().x / 2,
			(int)m_pTarget->GetPos().y);
	}

	CaculateDiff();
}

void CameraManager::CaculateDiff()
{
	//���� �����ؾ��ߴ� ����ȿ���� �ʿ������ �����ϰ� �����̰� �Ѵ�.
	Vec2 resolution = Core::GetInst()->GetResolution();
	Vec2 centerPos = resolution / 2.0f;

	Vec2 vLookDir = m_vLookPos - (m_vPrevLookPos);

	m_vDiffPos = m_vLookPos - centerPos;
}

Vec2 CameraManager::GetRenderPos(const Vec2& _value)
{
	return (m_vDiffPos - _value) * -1;
}
