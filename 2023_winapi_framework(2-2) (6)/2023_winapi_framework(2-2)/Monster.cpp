#include "pch.h"
#include "Monster.h"
#include "TimeMgr.h"
#include "Object.h"
#include "Collider.h"
#include "EventManager.h"
Monster::Monster()
	: m_fSpeed(100.f)
	, m_fMaxDis(50.f)
	, m_vCenterPos(Vec2(0.f,0.f))
	, m_fDir(1.f) // �����ʺ��� �̵�
	, m_iHp(5)
{
	CreateCollider();
}

Monster::~Monster()
{
}

void Monster::Update()
{
	Vec2 vCurPos = GetPos();
	vCurPos.x += m_fSpeed * fDT * m_fDir;
	
	// ���� �� �� �ִ� �Ÿ� �ִ�� ����? => ���� �ٲ��ٰž�.
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDis;
	if (fDist > 0.f)
	{
		// dir �ٲٱ�
		m_fDir *= -1;
		vCurPos.x += fDist * m_fDir;
	}
	SetPos(vCurPos);
}

void Monster::OnCollisionEnter(Collider* _pOther)
{
	const Object* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player_Bullet") {
		m_iHp--;
		if (m_iHp <= 0) {
			EventManager::GetInst()->DeleteObject(this);
		}
	}
}

void Monster::OnCollisionStay(Collider* _pOther)
{
}

void Monster::OnCollisionExit(Collider* _pOther)
{
}
