#include "pch.h"
#include "CameraManager.h"
#include "Object.h"
#include "Core.h"

void CameraManager::Update()
{
	//Ÿ���� ������ ���߾��� ���� �Ѵ�.
	if (m_pTarget == nullptr) {
		m_vLookPos = Vec2((int)Core::GetInst()->GetResolution().x / 2, (int)Core::GetInst()->GetResolution().y / 2);
	}
	else {
		//���� Ư���� �ƹ����� ��� ��� �������״� x���� �Ȱ��� ���߾��� �ٶ󺻴�.
	}
	
}
