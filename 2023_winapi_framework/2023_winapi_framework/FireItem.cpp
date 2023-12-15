#include "pch.h"
#include "FireItem.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Player.h"
#include "ItemFactory.h"
#include "EventMgr.h"

FireItem::FireItem()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"FireItem", L"Texture\\fireItem.bmp");

	CreateCollider();
	GetCollider()->SetScale(GetScale());

	CreateAnimator();

	GetAnimator()->CreateAnim(L"idle", m_pTex, Vec2(0), Vec2(16), Vec2(16.0f, 0.f), 4, .2f);
	GetAnimator()->PlayAnim(L"idle", true);
}

FireItem::~FireItem()
{
}

void FireItem::Update()
{
	GetAnimator()->Update();
}

void FireItem::Render(HDC _dc)
{
	Component_Render(_dc);
}

void FireItem::EnterCollision(Collider* other)
{
	Item::EnterCollision(other);
	Player* player = dynamic_cast<Player*>(other->GetObj());

	if (player) {
		player->SetMode(L"fire", true);
		m_pOwner->ResetObj();
		EventMgr::GetInst()->DeleteObject(this);
	}
}
