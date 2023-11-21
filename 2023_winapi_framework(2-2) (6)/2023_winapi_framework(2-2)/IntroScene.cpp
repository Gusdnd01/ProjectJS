#include "pch.h"
#include "IntroScene.h"
#include "IntroObj.h"
#include "Core.h"
#include <conio.h>
#include "KeyManager.h"

int scaleX = 100;
int scaleY = 100;

int yIncrease = 30;

void IntroScene::Init()
{
	IntroObj* obj = new IntroObj;
	obj->SetScale(Vector2({ scaleX, scaleY }));
	AddObj(obj, OBJECT_GROUP::DEFAULT);
}

void IntroScene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void IntroScene::Update()
{
	Scene::Update();
}