#include "pch.h"
#include "Start_Scene.h"
#include "Core.h"
#include "KeyMgr.h"
#include "CameraManager.h"
#include "CollisionMgr.h"
#include "TileManager.h"
#include "ResMgr.h"
#include "ShowSetting.h"
#include "Object.h"
#include "Player.h"
#include "Ground.h"
#include "Collider.h"
#include "Texture.h"
#include "Tile.h"

/*Items*/
#include "GameEndVolume.h"
#include "WaterItem.h"
#include "LowVelocitySpace.h"
#include "PlayerItemUI.h"
#include "ItemFactory.h"

void Start_Scene::Init()
{
	Vec2 centerPos = Vec2((int)Core::GetInst()->GetResolution().x/2,
		Core::GetInst()->GetResolution().y/2);

	Object* back = new Tile;
	back->SetPos(centerPos);
	back->SetScale(centerPos * 2);
	back->SetName(L"Background");
	AddObject(back, OBJECT_GROUP::DEFAULT);

	Object* gameEnd = new GameEndVolume;
	gameEnd->SetPos(centerPos + Vec2(-250.0f, -1970.0f));
	gameEnd->SetScale(Vec2(100.0f, 100.0f));
	AddObject(gameEnd, OBJECT_GROUP::VOLUME);

	Object* pObj= new Player;
	pObj->SetPos(centerPos + Vec2(0.0f, centerPos.y - 100.0f));
	pObj->SetScale(Vec2(3.0f,3.0f));
	AddObject(pObj, OBJECT_GROUP::PLAYER);
	m_pPlayer = pObj;
	
	//땅 충돌체.
	Ground* ground = new Ground;
	ground->SetTiles(112);
	CreateObj(ground, Vec2(centerPos.x, centerPos.y * 2), Vec2(1200, 100), Vec2(3000.0f, 100.0f), OBJECT_GROUP::GROUND);

	for (int i = 0; i < m_vStagePlatforms.size(); ++i) {
		Ground* ground = new Ground;
		ground->SetTiles(m_vStagePlatforms[i].tile_index);
		CreateObj(ground, centerPos+ m_vStagePlatforms[i].pos, m_vStagePlatforms[i].scale, m_vStagePlatforms[i].scale, OBJECT_GROUP::GROUND);
	}

	ItemFactory* waterItemFactory_01 = new ItemFactory;
	waterItemFactory_01->SetPos(centerPos + Vec2(-500.0f, -905.0f));
	waterItemFactory_01->SetDuration(3.0f);
	AddObject(waterItemFactory_01, OBJECT_GROUP::DEFAULT);

	ItemFactory* waterItemFactory_02 = new ItemFactory;
	waterItemFactory_02->SetPos(centerPos + Vec2(-390.0f, -1250.0f));
	waterItemFactory_02->SetDuration(3.0f);
	AddObject(waterItemFactory_02, OBJECT_GROUP::DEFAULT);

	LowVelocitySpace* lvs = new LowVelocitySpace;
	lvs->SetPos(centerPos + Vec2(0.0f, -1200.0f));
	lvs->SetScale(Vec2(2.0f, 1.0f));
	AddObject(lvs, OBJECT_GROUP::ITEM);
	
	//Object인데 위치 정보만 갖고 있는 오브젝트이다.
	Object* camRig = new Object;
	camRig->SetName(L"camRig");
	camRig->SetPos(centerPos);
	AddObject(camRig, OBJECT_GROUP::DEFAULT);
	m_pCamRig = camRig;

	PlayerItemUI* piu = new PlayerItemUI;
	piu->SetOwner(camRig);
	piu->SetPlayer(dynamic_cast<Player*>(pObj));
	piu->SetOffsetPos(Vec2(1200, -300));
	piu->SetActive(true);
	piu->SetScale(Vec2(2.0f));
	AddObject(piu, OBJECT_GROUP::DEFAULT);

	// 사운드 세팅
	//ResMgr::GetInst()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	//ResMgr::GetInst()->LoadSound(L"Shoot", L"Sound\\laserShoot.wav", false);
	//ResMgr::GetInst()->Play(L"BGM");

	ResMgr::GetInst()->Volume(SOUND_CHANNEL::BGM, ShowSetting::GetInst()->GetBGM());
	ResMgr::GetInst()->Volume(SOUND_CHANNEL::EFFECT, ShowSetting::GetInst()->GetSFX()); 
	m_vStage.push_back(360.0f);
	for (int i = 1; i < 100; i+=2) {
		float yPos = i * -centerPos.y;
		m_vStage.push_back(yPos);
	}

	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::GROUND);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::VOLUME);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::ITEM);

	CameraManager::GetInst()->SetTarget(camRig);
}

void Start_Scene::Update()
{
	Vec2 resolution = Core::GetInst()->GetResolution();
	Vec2 camPos = m_pCamRig->GetPos();
	Vec2 pPos = m_pPlayer->GetPos();

	ModifyPos(Vec2(0.0f, m_vStage[CheckStage(pPos.y)]), L"camRig");
	ModifyPos(Vec2(resolution.x / 2, m_vStage[CheckStage(pPos.y)]), L"Background");
	
	if (KEY_DOWN(KEY_TYPE::ESC)) {
		ShowSetting::GetInst()->IsEscActive = !ShowSetting::GetInst()->IsEscActive;
	}

	Scene::Update();
}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void Start_Scene::Release() 
{
	CollisionMgr::GetInst()->CheckReset();
	
	m_vStage.clear();

	Scene::Release();
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

void Start_Scene::CreateObj(Object* obj, Vec2 Pos, Vec2 Scale, Vec2 Col, OBJECT_GROUP Type)
{
	obj->SetPos(Pos);
	obj->SetScale(Scale);
	obj->GetCollider()->SetScale(Col);
	AddObject(obj, Type);
}
