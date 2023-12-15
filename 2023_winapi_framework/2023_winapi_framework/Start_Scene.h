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
		m_mModifiers[_name]->SetPos(_pos);
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
		{ 277, Vec2(-600.0f, -200.0f), Vec2(240.0f, 80.0f)},//1��(-360)
		{ 277, Vec2(-100.0f, -500.0f), Vec2(240.0f, 80.0f)},
		{ 277, Vec2(300.0f, -650.0f), Vec2(240.0f, 80.0f)},
		{ 277, Vec2(100.0f, -900.0f), Vec2(50.0f, 50.0f)},
		{ 117, Vec2(-200.0f, -900.0f), Vec2(150.0f, 50.0f)},
		{ 117, Vec2(-500.0f, -840.0f), Vec2(75.0f, 75.0f)}, //2��(-1080)
		{ 117, Vec2(-300.0f, -1150.0f), Vec2(225.0f, 75.0f)},
		{ 117, Vec2(200.0f, -1180.0f), Vec2(150.0f, 75.0f)},
		{ 117, Vec2(-270.0f, -1370.0f), Vec2(250.0f, 75.0f)},
		{ 75, Vec2(100.0f, -1520.0f), Vec2(50.0f, 50.0f)},
		{ 89, Vec2(600.0f, -1680.0f), Vec2(100.0f, 100.0f)},//3�� (-1800)
		{ 75, Vec2(350.0f, -2000.0f), Vec2(50.0f, 70.0f)},
		{ 89, Vec2(600.0f, -2100.0f), Vec2(150.0f, 70.0f)},
		{ 89, Vec2(-600.0f, -2100.0f), Vec2(210.0f, 70.0f)},
		{ 75, Vec2(-300.0f, -2400.0f), Vec2(100.0f, 70.0f)}, //4
		{ 277, Vec2(-600.0f, -2750.0f), Vec2(150.0f, 70.0f)},
		{ 277, Vec2(600.0f, -2750.0f), Vec2(200.0f, 70.0f)},	
		{ 117, Vec2(300.0f, -2900.0f), Vec2(50.0f, 70.0f)},
		{ 117, Vec2(150.0f, -2900.0f), Vec2(50.0f, 70.0f)},
		{89, Vec2{-100.0, -3150.0f}, Vec2(60.0f, 70.f)}, //5
		{277, Vec2{200.0, -3300.0f}, Vec2(120.0f, 70.f)},
		{277, Vec2{600.0, -3550.0f}, Vec2(200.0f, 70.f)},
		{277, Vec2{-600.0, -3550.0f}, Vec2(200.0f, 70.f)},
		{277, Vec2{-300.0, -3800.0f}, Vec2(200.0f, 70.f)},//6
		{177, Vec2{-300.0, -3800.0f}, Vec2(200.0f, 70.f)},
		{177, Vec2{-300.0, -3800.0f}, Vec2(200.0f, 70.f)},
		{177, Vec2{-300.0, -3800.0f}, Vec2(200.0f, 70.f)},
	};

	map<wstring, Object*> m_mModifiers;
};

