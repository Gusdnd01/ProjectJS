#include "pch.h"
#include "Gravity.h"
#include "RigidBody.h"
#include "Object.h"

Gravity::Gravity()
	: m_pOwner(nullptr)
	, m_bOnGround(false)
{
}

Gravity::~Gravity()
{
}

void Gravity::FinalUpdate()
{
	RigidBody* rb = m_pOwner->GetRigidBody();
	float alpha = m_bOnGround ? 0 : 500.0f;

	if (rb) {
		rb->SetAccelAlpha(Vec2(0.0f, alpha));
	}

	//m_pOwner->GetRigidBody()->AddForce(Vec2(0.0f, 800.f), FORCE_MODE::FORCE);
}

void Gravity::OnGround(bool _value)
{
	m_bOnGround = _value;

	if (m_bOnGround) {
		m_pOwner->GetRigidBody()->StopImmediatelyY();
	}
}



