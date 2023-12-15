#include "pch.h"
#include "LowVelocitySpace.h"
#include "Player.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Animator.h"
#include "ResMgr.h"

LowVelocitySpace::LowVelocitySpace()
	: m_vAddVelo {}
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"waterFall", L"Texture\\waterFall.bmp");

	CreateCollider();

	CreateAnimator();
	GetAnimator()->CreateAnim(L"idle",m_pTex, Vec2(0.0f),Vec2(128.0f), Vec2(128.0f, 0.0f), 6, 0.1f);
	GetAnimator()->PlayAnim(L"idle", true);
}

LowVelocitySpace::~LowVelocitySpace()
{

}

void LowVelocitySpace::Update()
{
	GetAnimator()->Update();
}

void LowVelocitySpace::Render(HDC _dc)
{
	Component_Render(_dc);
}

void LowVelocitySpace::EnterCollision(Collider* other)
{
	Player* player = dynamic_cast<Player*>(other->GetObj());

	if (player) {
		if(!player->GetPlayerMode(L"water"))
			player->GetRigidBody()->AddForce(m_vAddVelo, FORCE_MODE::IMPULSE);
		else {
			return;
		}
	}
}

void LowVelocitySpace::ExitCollision(Collider* other)
{
	Player* player = dynamic_cast<Player*>(other->GetObj());
	if (player) {
		if (player->GetPlayerMode(L"water")) {
			player->SetMode(L"water", false);
		}
		else if (player->GetPlayerMode(L"fire")) {
			player->SetMode(L"fire", false);
		}
	}
	else {
		return;
	}
}
