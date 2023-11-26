#include "pch.h"
#include "Gravity.h"
#include "RigidBody.h"
#include "Object.h"

Gravity::Gravity()
	: m_pOwner(nullptr)
	, m_bOnGround(false)
	, m_fGravity(0.0f)
{
}

Gravity::~Gravity()
{
}

void Gravity::FinalUpdate()
{
	if (m_bOnGround) return;
	m_pOwner->GetRigidBody()->AddForce(Vec2(0.0f, m_fGravity), FORCE_MODE::FORCE);
}

void Gravity::OnGround(bool _value)
{
	m_bOnGround = _value;

	if (m_bOnGround) {
		m_pOwner->GetRigidBody()->StopImmediatelyY();
	}
}



