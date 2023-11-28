#include "pch.h"
#include "CameraManager.h"
#include "Object.h"
#include "Core.h"

void CameraManager::Update()
{
	//타겟이 없으면 정중앙을 보게 한다.
	if (m_pTarget == nullptr) {
		m_vLookPos = Vec2((int)Core::GetInst()->GetResolution().x / 2, (int)Core::GetInst()->GetResolution().y / 2);
	}
	else {
		//게임 특성상 아무래도 상승 운동만 존재할테니 x값은 똑같이 정중앙을 바라본다.
	}
	
}
