#include "pch.h"
#include "ItemFactory.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "WaterItem.h"

void ItemFactory::Update()
{
	if (!m_pCurObject) {
		m_fTimer += fDT;
		if (m_fTimer >= m_fDuration) {
			m_fTimer = 0;

			m_pCurObject = new WaterItem;
			dynamic_cast<Object*>(m_pCurObject)->SetPos(GetPos());
			dynamic_cast<Object*>(m_pCurObject)->SetScale(Vec2(3.0f));
			SceneMgr::GetInst()->GetCurScene()->AddObject(m_pCurObject, OBJECT_GROUP::ITEM);
		}
	}
}

ItemFactory::ItemFactory()
{
}

ItemFactory::~ItemFactory()
{
}
