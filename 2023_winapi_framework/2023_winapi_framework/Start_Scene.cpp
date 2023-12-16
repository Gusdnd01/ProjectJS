#include "pch.h"
#include "Start_Scene.h"
#include "Core.h"
#include "KeyMgr.h"
#include "CameraManager.h"
#include "CollisionMgr.h"
#include "TileManager.h"
#include "TimeMgr.h"
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
#include "WaterItemFactory.h"
#include "FireItemFactory.h"
#include "SnowFlake.h"
#include "Tree.h"

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
	gameEnd->SetPos(centerPos + Vec2(0.0f, -6350.0f));
	gameEnd->SetScale(Vec2(5));
	AddObject(gameEnd, OBJECT_GROUP::VOLUME);//���� ����

	SnowFlake* snow = new SnowFlake;
	snow->SetPos(centerPos);
	snow->SetScale(Vec2(7.5f));
	snow->SetName(L"Snow");
	AddObject(snow, OBJECT_GROUP::DEFAULT);
	
	//Tree* tree = new Tree;
	//tree->SetPos(centerPos + Vec2(-300.0f, 170.0f));
	//tree->SetScale(Vec2(10));
	//AddObject(tree, OBJECT_GROUP::DEFAULT);

	Object* pObj= new Player;
	pObj->SetPos(centerPos + Vec2{ 0.0f, 300.0f});
	pObj->SetScale(Vec2(3.0f,3.0f));
	AddObject(pObj, OBJECT_GROUP::PLAYER);
	m_pPlayer = pObj;
	
	//�� �浹ü.
	Ground* ground = new Ground;
	ground->SetTiles(112);
	CreateObj(ground, Vec2(centerPos.x, centerPos.y * 2), Vec2(1200, 100), Vec2(3000.0f, 100.0f), OBJECT_GROUP::GROUND);

	for (int i = 0; i < m_vStagePlatforms.size(); ++i) {
		Ground* ground = new Ground;
		ground->SetTiles(m_vStagePlatforms[i].tile_index);
		CreateObj(ground, centerPos+ m_vStagePlatforms[i].pos, m_vStagePlatforms[i].scale, m_vStagePlatforms[i].scale, OBJECT_GROUP::GROUND);
	}
#pragma region WaterItemFactories
	WaterItemFactory* waterItemFactory_01 = new WaterItemFactory;
	waterItemFactory_01->SetPos(centerPos + Vec2(-500.0f, -905.0f));
	waterItemFactory_01->SetDuration(3.0f);
	AddObject(waterItemFactory_01, OBJECT_GROUP::DEFAULT);

	WaterItemFactory* waterItemFactory_02 = new WaterItemFactory;
	waterItemFactory_02->SetPos(centerPos + Vec2(-350.0f, -1210.0f));
	waterItemFactory_02->SetDuration(3.0f);
	AddObject(waterItemFactory_02, OBJECT_GROUP::DEFAULT);
	
	WaterItemFactory* waterItemFactory_03 = new WaterItemFactory;
	waterItemFactory_03->SetPos(centerPos + Vec2(550.0f, -4100.0f));
	waterItemFactory_03->SetDuration(3.0f);
	AddObject(waterItemFactory_03, OBJECT_GROUP::DEFAULT);
	
	WaterItemFactory* waterItemFactory_04 = new WaterItemFactory;
	waterItemFactory_04->SetPos(centerPos + Vec2(600.0f, -5100.0f));
	waterItemFactory_04->SetDuration(3.0f);
	AddObject(waterItemFactory_04, OBJECT_GROUP::DEFAULT);
#pragma endregion

#pragma region FireItemFactory
	FireItemFactory* fireItemFactory_01 = new FireItemFactory;
	fireItemFactory_01->SetPos(centerPos + Vec2(600.0f, -2150.0f));
	fireItemFactory_01->SetDuration(3.0f);
	AddObject(fireItemFactory_01, OBJECT_GROUP::DEFAULT);
	FireItemFactory* fireItemFactory_02 = new FireItemFactory;
	fireItemFactory_02->SetPos(centerPos + Vec2(-600.0f, -2800.0f));
	fireItemFactory_02->SetDuration(3.0f);
	AddObject(fireItemFactory_02, OBJECT_GROUP::DEFAULT);
	
	FireItemFactory* fireItemFactory_03 = new FireItemFactory;
	fireItemFactory_03->SetPos(centerPos + Vec2{ 600.0, -3620.0f });
	fireItemFactory_03->SetDuration(3.0f);
	AddObject(fireItemFactory_03, OBJECT_GROUP::DEFAULT);
	
	FireItemFactory* fireItemFactory_04 = new FireItemFactory;
	fireItemFactory_04->SetPos(centerPos + Vec2(-475.0f, -4575.0f));
	fireItemFactory_04->SetDuration(3.0f);
	AddObject(fireItemFactory_04, OBJECT_GROUP::DEFAULT);

	FireItemFactory* fireItemFactory_05 = new FireItemFactory;
	fireItemFactory_05->SetPos(centerPos + Vec2(550.0f, -5100.0f));
	fireItemFactory_05->SetDuration(3.0f);
	AddObject(fireItemFactory_05, OBJECT_GROUP::DEFAULT);

	FireItemFactory* fireItemFactory_06 = new FireItemFactory;
	fireItemFactory_06->SetPos(centerPos + Vec2(550.0f, -5725.0f));
	fireItemFactory_06->SetDuration(3.0f);
	AddObject(fireItemFactory_06, OBJECT_GROUP::DEFAULT);
#pragma endregion

#pragma region LowVelSpace
	LowVelocitySpace* lvs_01 = new LowVelocitySpace;
	lvs_01->SetPos(centerPos + Vec2(-30.0f, -1150.0f));
	lvs_01->SetScale(Vec2(2.8f, 1.0f));
	AddObject(lvs_01, OBJECT_GROUP::ITEM);

	LowVelocitySpace* lvs_02 = new LowVelocitySpace;
	lvs_02->SetPos(centerPos+Vec2(0.0f, -4600.0f));
	lvs_02->SetScale(Vec2(2.2f, 2.54f));
	AddObject(lvs_02, OBJECT_GROUP::ITEM);

	LowVelocitySpace* lvs_03 = new LowVelocitySpace;
	lvs_03->SetPos(centerPos+ Vec2(0.0f, -5100.0f));
	lvs_03->SetScale(Vec2(1));
	AddObject(lvs_03, OBJECT_GROUP::ITEM);
#pragma endregion

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

	// ���� ����
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

	m_mModifiers.insert(make_pair(L"camRig", camRig));
	m_mModifiers.insert(make_pair(L"Background", back));
	m_mModifiers.insert(make_pair(L"Snow", snow));


	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::GROUND);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::VOLUME);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::ITEM);

	CameraManager::GetInst()->SetTarget(camRig);
}

void Start_Scene::Update()
{
	if (KEY_DOWN(KEY_TYPE::ESC)) {
		ShowSetting::GetInst()->IsEscActive = !ShowSetting::GetInst()->IsEscActive;
	}

	if (ShowSetting::GetInst()->IsEscActive || ShowSetting::GetInst()->IsActive) return;

	ResMgr::GetInst()->Volume(SOUND_CHANNEL::BGM, ShowSetting::GetInst()->GetBGM());
	ResMgr::GetInst()->Volume(SOUND_CHANNEL::EFFECT, ShowSetting::GetInst()->GetSFX());
	Vec2 resolution = Vec2((int)Core::GetInst()->GetResolution().x, (int)Core::GetInst()->GetResolution().y );
	Vec2 camPos = m_pCamRig->GetPos();
	Vec2 pPos = m_pPlayer->GetPos();

	ModifyPos(Vec2(0.0f, m_vStage[CheckStage(pPos.y)]), L"camRig");
	ModifyPos(Vec2(resolution.x / 2, m_vStage[CheckStage(pPos.y)]), L"Background");
	ModifyPos(Vec2(resolution.x / 2, m_vStage[CheckStage(pPos.y)]), L"Snow");
	
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
