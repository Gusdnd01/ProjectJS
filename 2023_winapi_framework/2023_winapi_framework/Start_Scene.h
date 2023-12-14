#pragma once
#include "Scene.h"
#include "Object.h"

struct platforms
{
	int tile_index;
	Vec2 pos;
	Vec2 scale;
};

class Start_Scene :
	public Scene
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	virtual void Release() override;

public:
	void ModifyPos(const Vec2& _pos, const wstring& _name) {
		for (UINT i = 0; i < 30; i++) {
			for (UINT j = 0; j < m_vecObj[i].size(); j++)
			{
				if (m_vecObj[i][j] != nullptr && m_vecObj[i][j]->GetName() == _name) {
					m_vecObj[i][j]->SetPos(_pos);
					return;
				}
			}
		}
	}

	int CheckStage(float _yValue);
	void CreateObj(Object* obj, Vec2 Pos, Vec2 Scale, Vec2 Col, OBJECT_GROUP Type);

private:
	Object* m_pPlayer;
	Object* m_pCamRig;

	vector<float> m_vStage;
	vector<platforms> m_vStagePlatforms = {
		{ 277, Vec2(600.0f, 150.0f), Vec2(300.0f, 100.0f)},
		{ 277, Vec2(40.0f, 0.0f), Vec2(240.0f, 80.0f)},
		{ 277, Vec2(-150.0f, -200.0f), Vec2(90.0f, 90.0f)},
		{ 277, Vec2(-600.0f, -200.0f), Vec2(240.0f, 80.0f)},//1Ãþ(-360)
		{ 277, Vec2(-100.0f, -500.0f), Vec2(240.0f, 80.0f)},
		{ 277, Vec2(300.0f, -650.0f), Vec2(240.0f, 80.0f)},
		{ 277, Vec2(100.0f, -900.0f), Vec2(50.0f, 50.0f)},
		{ 117, Vec2(-200.0f, -900.0f), Vec2(150.0f, 50.0f)},
		{ 117, Vec2(-500.0f, -840.0f), Vec2(75.0f, 75.0f)}, //2Ãþ(-1080)
		{ 117, Vec2(-300.0f, -1150.0f), Vec2(225.0f, 75.0f)},
		{ 117, Vec2(200.0f, -1180.0f), Vec2(150.0f, 75.0f)},
		{ 117, Vec2(-270.0f, -1370.0f), Vec2(250.0f, 75.0f)},
		{ 75, Vec2(180.0f, -1520.0f), Vec2(50.0f, 50.0f)},
		{ 89, Vec2(600.0f, -1580.0f), Vec2(100.0f, 100.0f)},//3Ãþ (-1800)
		{ 137, Vec2(250.0f, -1970.0f), Vec2(210.0f, 70.0f)},
	};
};

