#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "Monster.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "CameraManager.h"
#include "ResMgr.h"
#include "Ground.h"
#include "Collider.h"
void Start_Scene::Init()
{
	Vec2 centerPos = Vec2((int)Core::GetInst()->GetResolution().x/2,
		Core::GetInst()->GetResolution().y/2);

	Object* pObj= new Player;
	pObj->SetPos(centerPos);
	pObj->SetScale(Vec2(3.0f,3.0f));
	AddObject(pObj, OBJECT_GROUP::PLAYER);
	m_pPlayer = pObj;

	Object* wallL = new Ground;
	wallL->SetPos(centerPos - Vec2(centerPos.x, 0.0f));
	wallL->SetScale(Vec2(10.0f, 10000.0f));
	wallL->GetCollider()->SetScale(wallL->GetScale());
	AddObject(wallL, OBJECT_GROUP::GROUND);
	
	Object* wallR = new Ground;
	wallR->SetPos(centerPos + Vec2(centerPos.x, 0.0f));
	wallR->SetScale(Vec2(10.0f, 10000.0f));
	wallR->GetCollider()->SetScale(wallR->GetScale());
	AddObject(wallR, OBJECT_GROUP::GROUND);

	Object* ground = new Ground;
	ground->SetPos(centerPos + Vec2(0.0f, centerPos.y));
	ground->SetScale(Vec2(3100.0f, 100.0f));
	ground->GetCollider()->SetScale(ground->GetScale());
	AddObject(ground, OBJECT_GROUP::GROUND);

	Object* ground2 = new Ground;
	ground2->SetPos(centerPos + Vec2(200.0f, 100.0f));
	ground2->SetScale(Vec2(300.0f, 50.0f));
	ground2->GetCollider()->SetScale(ground2->GetScale());
	AddObject(ground2, OBJECT_GROUP::GROUND);
	
	Object* ground3 = new Ground;
	ground3->SetPos(centerPos + Vec2(-200.0f, -100.0f));
	ground3->SetScale(Vec2(300.0f, 50.0f));
	ground3->GetCollider()->SetScale(ground3->GetScale());
	AddObject(ground3, OBJECT_GROUP::GROUND);

	Object* ground4 = new Ground;
	ground4->SetPos(centerPos + Vec2(200.0f, -200.0f));
	ground4->SetScale(Vec2(300.0f, 50.0f));
	ground4->GetCollider()->SetScale(ground4->GetScale());
	AddObject(ground4, OBJECT_GROUP::GROUND);
	
	Object* ground5 = new Ground;
	ground5->SetPos(centerPos + Vec2(-200.0f, -300.0f));
	ground5->SetScale(Vec2(300.0f, 50.0f));
	ground5->GetCollider()->SetScale(ground5->GetScale());
	AddObject(ground5, OBJECT_GROUP::GROUND);

	Object* ground6 = new Ground;
	ground6->SetPos(centerPos + Vec2(200.0f, -400.0f));
	ground6->SetScale(Vec2(300.0f, 50.0f));
	ground6->GetCollider()->SetScale(ground6->GetScale());
	AddObject(ground6, OBJECT_GROUP::GROUND);
	
	Object* ground7 = new Ground;
	ground7->SetPos(centerPos + Vec2(-200.0f, -500.0f));
	ground7->SetScale(Vec2(300.0f, 50.0f));
	ground7->GetCollider()->SetScale(ground7->GetScale());
	AddObject(ground7, OBJECT_GROUP::GROUND);

	//Object인데 위치 정보만 갖고 있는 오브젝트이다.
	Object* camRig = new Object;
	camRig->SetName(L"camRig");
	camRig->SetPos(centerPos);
	AddObject(camRig, OBJECT_GROUP::DEFAULT);
	m_pCamRig = camRig;
	// 몬스터 세팅 마구마구 배치를 해봅시다.

	//Vec2 vResolution = Core::GetInst()->GetResolution();
	//Monster* pMonster = nullptr;
	//int iMonster = 10;		// 몬스터 수 
	//float fMoveDist = 30.f; // 움직일 거리
	//float fMonsterScale = 50.f; // 몬스터 크기
	//// 해상도x - ( 움직일 거리 + 오브젝트 크기 /2) * 2 / 몬스터수 -1 
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
	// 사운드 세팅
	//ResMgr::GetInst()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	//ResMgr::GetInst()->LoadSound(L"Shoot", L"Sound\\laserShoot.wav", false);
	//ResMgr::GetInst()->Play(L"BGM");

	m_vStage.push_back(360.0f);
	for (int i = 1; i < 100; i+=2) {
		float yPos = i * -centerPos.y;
		m_vStage.push_back(yPos);
	}

	// 충돌체크해야되는것들을 설정하자.
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::GROUND);

	CameraManager::GetInst()->SetTarget(camRig);
}

void Start_Scene::Update()
{
	Vec2 resolution = Vec2((int)Core::GetInst()->GetResolution().x, (int)Core::GetInst()->GetResolution().y );
	Vec2 camPos = m_pCamRig->GetPos();
	Vec2 pPos = m_pPlayer->GetPos();
	
	ModifyPos(Vec2(0.0f, m_vStage[CheckStage(pPos.y)]), L"camRig", true);

	Scene::Update();
	//if(KEY_DOWN(KEY_TYPE::ENTER))
	//	// 씬 변경
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

int Start_Scene::CheckStage(float _yValue)
{
	float minValue = 100000.0f;
	int stage_index = 0;
	for (int i = 0; i < m_vStage.size(); ++i) {
		if (abs(abs(m_vStage[i]) - abs(_yValue)) < minValue) {
			minValue = abs(m_vStage[i] - _yValue);
			stage_index = i;
		}
	}

	return stage_index;
}
