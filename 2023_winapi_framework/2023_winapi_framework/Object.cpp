#include "pch.h"
#include "Object.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Gravity.h"

Object::Object()
	: m_vPos{}
	, m_vScale{}
	, m_IsAlive(true)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_cRb(nullptr)
	, m_cGravity(nullptr)

{
}

Object::~Object()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
	if (nullptr != m_pAnimator)
		delete m_pAnimator;
	if (m_cRb != nullptr)
		delete m_cRb;
	if (m_cGravity != nullptr)
		delete m_cGravity;

}

void Object::CreateCollider()
{
	m_pCollider = new Collider;
	m_pCollider->m_pOwner = this;
}

void Object::CreateAnimator()
{
	m_pAnimator = new Animator;
	m_pAnimator->m_pOwner = this;
}

void Object::CreateRigidBody()
{
	m_cRb = new RigidBody;
	m_cRb->m_pOwner = this;
}

void Object::CreateGravity()
{
	m_cGravity = new Gravity;
	m_cGravity->m_pOwner = this;
}

void Object::Update()
{
}

void Object::FinalUpdate()
{
	if (m_cGravity)
		m_cGravity->FinalUpdate();
	if (m_pCollider)
		m_pCollider->FinalUpdate();
	if (m_cRb)
		m_cRb->FinalUpdate();
}

void Object::Render(HDC _dc)
{
	/*Vec2 vPos = m_obj.GetPos();
	Vec2 vScale = m_obj.GetScale();*/
	RECT_RENDER(m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y, _dc);
	Component_Render(_dc);
}

void Object::EnterCollision(Collider* _pOther)
{
}

void Object::ExitCollision(Collider* _pOther)
{
}

void Object::StayCollision(Collider* _pOther)
{

}

void Object::CheckLeft(Collider* _pOther)
{
}

void Object::CheckRight(Collider* _pOther)
{
}

void Object::CheckTop(Collider* _pOther)
{
}

void Object::CheckBottom(Collider* _pOther)
{
}

void Object::Component_Render(HDC _dc)
{
	if (nullptr != m_pCollider)
		m_pCollider->Render(_dc);
	if (nullptr != m_pAnimator)
		m_pAnimator->Render(_dc);
}

