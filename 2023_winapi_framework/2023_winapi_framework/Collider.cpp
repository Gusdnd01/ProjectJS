#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "SelectGDI.h"
#include "Player.h"
#include "CameraManager.h"
UINT Collider::m_sNextID = 0;
Collider::Collider()
	: m_pOwner(nullptr)
	, m_vScale(Vec2(40.f, 40.f))
	, m_ID(m_sNextID++)
	, m_check(0)
	, m_vFinalPos{}
{
}

Collider::Collider(const Collider& _origin)
	: m_pOwner(nullptr)
	, m_vScale(_origin.m_vScale)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_ID(m_sNextID++)
	, m_check(0)
	, m_vFinalPos{}
	, m_bIsCollision(false)
{
}

Collider::~Collider()
{}

void Collider::Render(HDC _dc)
{
	//Core::GetInst()->GetPen(PEN_TYPE::GREEN);
	//Core::GetInst()->GetBrush(BRUSH_TYPE::HOLLOW);
	//SelectObject();
	PEN_TYPE ePen = PEN_TYPE::GREEN;
	if (m_check)
		ePen = PEN_TYPE::RED;
	SelectGDI pen(_dc, ePen);
	SelectGDI brush(_dc, BRUSH_TYPE::HOLLOW);

	Vec2 renderPos = CameraManager::GetInst()->GetRenderPos(m_vFinalPos);

	RECT_RENDER(renderPos.x, renderPos.y, m_vScale.x, m_vScale.y, _dc);
}

void Collider::EnterCollision(Collider* _pOther)
{
	++m_check;
	m_bIsCollision = true;
	m_pOwner->EnterCollision(_pOther);
}

void Collider::ExitCollision(Collider* _pOther)
{
	--m_check;
	m_bIsCollision = false;
	m_pOwner->ExitCollision(_pOther);
}

void Collider::StayCollision(Collider* _pOther)
{
	m_pOwner->StayCollision(_pOther);
}

bool Collider::CheckBottom(Collider* _pOther)
{
	//COllider checke!
	if (_pOther->GetFinalPos().y > GetFinalPos().y && 
		((_pOther->GetFinalPos().x + _pOther->GetScale().x / 2) > (GetFinalPos().x - GetScale().x/2) && 
		 (_pOther->GetFinalPos().x - _pOther->GetScale().x / 2) < (GetFinalPos().x + GetScale().x/2))) {
		return true;
	}
	return false;
}

bool Collider::CheckTop(Collider* _pOther)
{
	if (_pOther->GetFinalPos().y < GetFinalPos().y &&
		((_pOther->GetFinalPos().x + _pOther->GetScale().x / 2) > (GetFinalPos().x - GetScale().x/2) &&
		 (_pOther->GetFinalPos().x - _pOther->GetScale().x / 2) < (GetFinalPos().x + GetScale().x/2))) {
		return true;
	}

	return false;
}

bool Collider::CheckLeft(Collider* _pOther)
{
	if (_pOther->GetFinalPos().x < GetFinalPos().x &&
		((_pOther->GetFinalPos().y + _pOther->GetScale().y / 2) > (GetFinalPos().y- GetScale().y/2) &&
		 (_pOther->GetFinalPos().y - _pOther->GetScale().y / 2) < (GetFinalPos().y+ GetScale().y/2))) {
		return true;
	}
	return false;
}

bool Collider::CheckRight(Collider* _pOther)
{
	if (_pOther->GetFinalPos().x > GetFinalPos().x &&
		((_pOther->GetFinalPos().y + _pOther->GetScale().y / 2) >(GetFinalPos().y - GetScale().y/2) &&
		 (_pOther->GetFinalPos().y - _pOther->GetScale().y / 2) <(GetFinalPos().y + GetScale().y/2))) {
		return true;
	}
	return false;
}

void Collider::FinalUpdate()
{
	Vec2 vObjPos = m_pOwner->GetPos();
	m_vFinalPos = vObjPos + m_vOffsetPos;
}

