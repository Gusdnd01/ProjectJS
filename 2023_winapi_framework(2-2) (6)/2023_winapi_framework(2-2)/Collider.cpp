#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "SelectGDI.h"
UINT Collider::m_sNextID = 0;
Collider::Collider()
	: m_pOwner(nullptr)
	, m_vScale(Vec2(40.f,40.f))
	, m_ID(m_sNextID++)
	, m_check(0)
{}

Collider::Collider(const Collider& _origin)
	: m_pOwner(nullptr)
	, m_vScale(_origin.m_vScale)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_ID(m_sNextID++)
	, m_check(0)
{

}

Collider::~Collider()
{}

void Collider::Render(HDC _dc)
{
	//Core::GetInst()->GetPen(PEN_TYPE::GREEN);
	//Core::GetInst()->GetBrush(BRUSH_TYPE::HOLLOW);
	//SelectObject();
	PEN_TYPE pen = PEN_TYPE::GREEN;
	if (m_check) {
		pen = PEN_TYPE::RED;
	}
	SelectGDI spen(_dc, pen);
	SelectGDI brush(_dc, BRUSH_TYPE::HOLLOW);
	RECT_RENDER(m_vFinalPos.x, m_vFinalPos.y, m_vScale.x, m_vScale.y, _dc);
}

void Collider::OnCollisionEnter(Collider* _pOther)
{
	++m_check;
	m_pOwner->OnCollisionEnter(_pOther);
}

void Collider::OnCollisionStay(Collider* _pOther)
{
	m_pOwner->OnCollisionStay(_pOther);

}

void Collider::OnCollisionExit(Collider* _pOther)
{
	--m_check;
	m_pOwner->OnCollisionExit(_pOther);
}

void Collider::FinalUpdate()
{
	// Object위치를 따라가야 하는거야.
	Vec2 vObjPos = m_pOwner->GetPos();
	m_vFinalPos = vObjPos + m_vOffsetPos;
}

