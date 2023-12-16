#include "pch.h"
#include "Item.h"
#include "ResMgr.h"
#include "Player.h"
#include "Object.h"
#include "ItemFactory.h"
#include "EventMgr.h"
#include "Collider.h"
Item::Item()
	: m_pTex(nullptr)
{
	ResMgr::GetInst()->LoadSound(L"GetItemSound", L"Sound\\GetItemSound", false);
}

Item::~Item()
{
}

void Item::Update()
{
}

void Item::Render(HDC _dc)
{

}

void Item::EnterCollision(Collider* other)
{
	ResMgr::GetInst()->Play(L"GetItemSound");
	Player* player = dynamic_cast<Player*>(other->GetObj());

	if (player) {
		player->SetMode(m_wItemType, true);
		m_pOwner->ResetObj();
		EventMgr::GetInst()->DeleteObject(this);
	}
}
