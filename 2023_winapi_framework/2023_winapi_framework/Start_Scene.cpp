#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "Monster.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ResMgr.h"
#include "Ground.h"
#include "Collider.h"
void Start_Scene::Init()
{
	Object* pObj = new Player;
	pObj->SetPos((Vec2({Core::GetInst()->GetResolution().x /2, Core::GetInst()->GetResolution().y / 2})));
	pObj->SetScale(Vec2(3.0f,3.0f));
	AddObject(pObj, OBJECT_GROUP::PLAYER);

	Object* ground = new Ground;
	ground->SetPos(Vec2({ Core::GetInst()->GetResolution().x / 2, Core::GetInst()->GetResolution().y }));
	ground->SetScale(Vec2(3100.0f, 100.0f));
	ground->GetCollider()->SetScale(ground->GetScale());
	AddObject(ground, OBJECT_GROUP::GROUND);

	Object* ground2 = new Ground;
	ground2->SetPos(Vec2({ Core::GetInst()->GetResolution().x / 2 + 200.0f, Core::GetInst()->GetResolution().y/2 + 100.0f }));
	ground2->SetScale(Vec2(300.0f, 50.0f));
	ground2->GetCollider()->SetScale(ground2->GetScale());
	AddObject(ground2, OBJECT_GROUP::GROUND);
	
	Object* ground3 = new Ground;
	ground3->SetPos(Vec2({ Core::GetInst()->GetResolution().x / 2 - 300.0f, Core::GetInst()->GetResolution().y/2 -100.0f }));
	ground3->SetScale(Vec2(300.0f, 50.0f));
	ground3->GetCollider()->SetScale(ground3->GetScale());
	AddObject(ground3, OBJECT_GROUP::GROUND);

	// ���� ���� �������� ��ġ�� �غ��ô�.

	//Vec2 vResolution = Core::GetInst()->GetResolution();
	//Monster* pMonster = nullptr;
	//int iMonster = 10;		// ���� �� 
	//float fMoveDist = 30.f; // ������ �Ÿ�
	//float fMonsterScale = 50.f; // ���� ũ��
	//// �ػ�x - ( ������ �Ÿ� + ������Ʈ ũ�� /2) * 2 / ���ͼ� -1 
	//float fTerm = (vResolution.x - (fMoveDist + fMonsterScale / 2.f) * 2) 
	//				/ (float)(iMonster -1);
	//for (int i = 0; i < iMonster; ++i)
	//{
	//	pMonster = new Monster;
	//	pMonster->SetPos(Vec2(
	//		(fMoveDist + fMonsterScale / 2.f) + i* fTerm
	//		,300.f));
	//	pMonster->SetScale(Vec2(fMonsterScale, fMonsterScale));
	//	pMonster->SetCenterPos(pMonster->GetPos());
	//	pMonster->SetMoveDis(fMoveDist);
	//	AddObject(pMonster, OBJECT_GROUP::MONSTER);
	//}
	// ���� ����
	//ResMgr::GetInst()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	//ResMgr::GetInst()->LoadSound(L"Shoot", L"Sound\\laserShoot.wav", false);
	//ResMgr::GetInst()->Play(L"BGM");

	// �浹üũ�ؾߵǴ°͵��� ��������.
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::GROUND);
}

void Start_Scene::Update()
{
	Scene::Update();
	//if(KEY_DOWN(KEY_TYPE::ENTER))
	//	// �� ����
}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
