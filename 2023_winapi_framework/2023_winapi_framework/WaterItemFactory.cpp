#include "pch.h"
#include "WaterItemFactory.h"
#include "SceneMgr.h"
#include "TimeMgr.h"
#include "WaterItem.h"
#include "Scene.h"

WaterItemFactory::WaterItemFactory()
	: m_fTimer(0.0f)
{
}

WaterItemFactory::~WaterItemFactory()
{
}

void WaterItemFactory::Update()
{
	if (GetFactory()) return;
	if (!GetFactory()) {
		m_fTimer += fDT;
		if (m_fTimer >= GetDuration()) {
			m_fTimer = 0;

			SetFactory(new WaterItem);
			WaterItem* item = dynamic_cast<WaterItem*>(GetFactory());
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
