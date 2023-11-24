#include "pch.h"
#include "GravityManager.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Object.h"

void GravityManager::Update()
{
	for (int i = 0; i < m_vGravityObj.size(); ++i) {
		if (!m_vGravityObj[i]->GetCollider()->GetCheckBottom()) {
			m_vGravityObj[i]->GetRigidBody()->Update();
		}
	}
}

void GravityManager::AddGravObj(Object* _obj)
{
	if (_obj != nullptr) {
		m_vGravityObj.push_back(_obj);
	}
}
