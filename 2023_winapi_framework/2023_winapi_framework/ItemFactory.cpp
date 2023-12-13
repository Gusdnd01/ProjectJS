#include "pch.h"
#include "ItemFactory.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

void ItemFactory::Update()
{
	if (!m_pCurObject) {
		m_fTimer += fDT;
		if (m_fTimer >= m_fDuration) {
			m_fTimer = 0;

			
			SceneMgr::GetInst()->GetCurScene()->AddObject();
		}
	}
}

template<class T>
ItemFactory<T>::ItemFactory()
{
}

template<class T>
ItemFactory<T>::~ItemFactory()
{
}
