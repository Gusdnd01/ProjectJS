#include "pch.h"
#include "FireItemFactory.h"
#include "TimeMgr.h"
#include "FireItem.h"
#include "SceneMgr.h"
#include "Scene.h"

FireItemFactory::FireItemFactory()
	: m_fTimer(0.0f)
{
}

FireItemFactory::~FireItemFactory()
{
}

void FireItemFactory::Update()
{
	if (GetFactory()) return;
	if (!GetFactory()) {
		m_fTimer += fDT;
		if (m_fTimer >= GetDuration()) {
			m_fTimer = 0;

			SetFactory(new FireItem);
			FireItem* item = dynamic_cast<FireItem*>(GetFactory());
			item->SetType(L"fire");
			item->SetPos(GetPos());
			item->SetScale(Vec2(3.0f));
			item->SetOwner(this);
			SceneMgr::GetInst()->GetCurScene()->AddObject(item, OBJECT_GROUP::ITEM);
		}
	}
	else {
		return;
	}
}
