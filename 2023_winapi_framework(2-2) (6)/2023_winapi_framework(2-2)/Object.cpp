#include "pch.h"
#include "Object.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
Object::Object()
	//: m_ptPos{}
	//, m_ptScale{}
	: m_pCollider(nullptr)
	, m_vPos{}
	, m_vScale{}
	, m_isAlive(true)
	, m_animator(nullptr)
{
}

Object::~Object()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
	if (m_animator != nullptr) {
		delete m_animator;
	}
}

void Object::CreateCollider()
{
	m_pCollider = new Collider;
	m_pCollider->m_pOwner = this;
}

void Object::CreateAnimator()
{
	m_animator = new Animator;
	m_animator->m_pOwner = this;
}

void Object::Update()
{
	//Vec2 vPos = m_obj.GetPos();

//	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
//	if(KeyMgr::GetInst()->GetKey(KEY_TYPE::LEFT) == KEY_STATE::UP)

	//m_obj.SetPos(vPos);
}

void Object::FinalUpdate()
{
	if (m_pCollider)
		m_pCollider->FinalUpdate();
}

void Object::Render(HDC _dc)
{
	/*Vec2 vPos = m_obj.GetPos();
	Vec2 vScale = m_obj.GetScale();*/
	RECT_RENDER(m_vPos.x, m_vPos.y, m_vScale.x, m_vScale.y, _dc);
	Component_Render(_dc);
}

void Object::OnCollisionEnter(Collider* _pOther)
{
}

void Object::OnCollisionStay(Collider* _pOther)
{
}

void Object::OnCollisionExit(Collider* _pOther)
{
}

void Object::Component_Render(HDC _dc)
{
	if (nullptr != m_pCollider)
		m_pCollider->Render(_dc);
	if (m_animator != nullptr)
	{
		m_animator->Render(_dc);
	}
}
