#include "pch.h"
#include "Item.h"
#include "ResMgr.h"

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
}
