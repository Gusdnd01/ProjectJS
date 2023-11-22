#include "pch.h"
#include "RigidBody.h"
#include "Object.h"

RigidBody::RigidBody()
	: m_pOwner(nullptr)
	, m_fMass(.0f)
	, m_UseGravity(true)
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::Update()
{
	if (!m_UseGravity) return;
	Vec2 pos = m_pOwner->GetPos();

	pos.y -= m_fGravity * m_fMass;
	m_pOwner->SetPos(pos);
}