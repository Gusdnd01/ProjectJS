#include "pch.h"
#include "WaterItem.h"
#include "Player.h"
#include "Collider.h"
#include "ResMgr.h"
#include "Animator.h"
#include "Texture.h"
#include "EventMgr.h"
#include "ItemFactory.h"


WaterItem::WaterItem()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"WaterItem", L"Texture\\waterItem.bmp");

	CreateCollider();
	GetCollider()->SetScale(GetScale());

	CreateAnimator();

	GetAnimator()->CreateAnim(L"idle", m_pTex, Vec2(0), Vec2(16), Vec2(16.0f, 0.f),4, .2f);
	GetAnimator()->PlayAnim(L"idle",true);
}

WaterItem::~WaterItem()
{
}

void WaterItem::Update()
{
	GetAnimator()->Update();
}

void WaterItem::Render(HDC _dc)
{
	Component_Render(_dc);
}

void WaterItem::EnterCollision(Collider* other)
{
	Item::EnterCollision(other);
	Player* player = dynamic_cast<Player*>(other->GetObj());

	if (player) {
		player->SetMode(PLAYER_MODE::WATER);
		m_pOwner->ResetObj();
		EventMgr::GetInst()->DeleteObject(this);
	}
}
