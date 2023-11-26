#include "pch.h"
#include "RigidBodyManager.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Object.h"

void RigidBodyManager::Update()
{
	for (int i = 0; i < m_vGravityObj.size(); ++i) {
		if (!m_vGravityObj[i]->GetCollider()->GetCheckBottom()) {
			m_vGravityObj[i]->GetRigidBody()->Update();
		}
	}
}

void RigidBodyManager::AddGravObj(Object* _obj)
{
	if (_obj != nullptr) {
		m_vGravityObj.push_back(_obj);
	}
}
