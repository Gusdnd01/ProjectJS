#include "pch.h"
#include "TestScene.h"
#include "TestObj.h"

void TestScene::Init()
{
	Object* pObj = new TestObj;

	pObj->SetPos(Vector2({ 100, 100 }));
	pObj->SetScale(Vector2({ 100, 100 }));

	AddObj(pObj, OBJECT_GROUP::DEFAULT);
}
