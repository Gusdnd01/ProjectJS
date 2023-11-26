#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "SelectGDI.h"
#include "Player.h"
UINT Collider::m_sNextID = 0;
Collider::Collider()
	: m_pOwner(nullptr)
	, m_vScale(Vec2(40.f, 40.f))
	, m_ID(m_sNextID++)
	, m_check(0)
	, m_vFinalPos{}
	, m_bCheckLeft(false)
	, m_bCheckRight(false)
	, m_bCheckTop(false)
	, m_bCheckBottom(false)
{
}

Collider::Collider(const Collider& _origin)
	: m_pOwner(nullptr)
	, m_vScale(_origin.m_vScale)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_ID(m_sNextID++)
	, m_check(0)
	, m_vFinalPos{}
	, m_bCheckLeft(false)
	, m_bCheckRight(false)
	, m_bCheckTop(false)
	, m_bCheckBottom(false)
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
	RECT_RENDER(m_vFinalPos.x, m_vFinalPos.y, m_vScale.x, m_vScale.y, _dc);
}

void Collider::EnterCollision(Collider* _pOther)
{
	++m_check;
	m_pOwner->EnterCollision(_pOther);
	CheckPosition(_pOther);
}

void Collider::ExitCollision(Collider* _pOther)
{
	--m_check;
	m_pOwner->ExitCollision(_pOther);
	ReleaseCheck();
}

void Collider::StayCollision(Collider* _pOther)
{
	m_pOwner->StayCollision(_pOther);
}

void Collider::CheckPosition(Collider* _pOther)
{
	CheckLeft(_pOther);
	CheckRight(_pOther);
	CheckTop(_pOther);
	CheckBottom(_pOther);
}

void Collider::ReleaseCheck()
{
	m_bCheckLeft = false;
	m_bCheckRight = false;
	m_bCheckTop = false;
	m_bCheckBottom = false;
}

void Collider::CheckLeft(Collider* _pOther)
{
	if (_pOther->GetFinalPos().x < GetFinalPos().x) {
		m_bCheckLeft = true;
	}
	else {
		m_bCheckLeft = false;

	}
}

void Collider::CheckRight(Collider* _pOther)
{
	if (_pOther->GetFinalPos().x > GetFinalPos().x) {
		m_bCheckRight = true;
	}
	else {
		m_bCheckRight = false;

	}
}

void Collider::CheckTop(Collider* _pOther)
{
	if (_pOther->GetFinalPos().y < GetFinalPos().y) {
		m_bCheckTop = true;
	}
	else {
		m_bCheckTop = false;
	}
}

void Collider::CheckBottom(Collider* _pOther)
{
	if (_pOther->GetFinalPos().y > GetFinalPos().y) {
		m_bCheckBottom = true;
	}
	else {
		m_bCheckBottom = false;
	}

	//m_pOwner->CheckBottom(_pOther);
}

void Collider::FinalUpdate()
{
	Vec2 vObjPos = m_pOwner->GetPos();
	m_vFinalPos = vObjPos + m_vOffsetPos;
}

