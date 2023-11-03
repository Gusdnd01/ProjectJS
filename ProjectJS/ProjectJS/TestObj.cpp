#include "pch.h"
#include "TestObj.h"
#include "KeyManager.h"
#include "TimeManager.h"

void TestObj::Update()
{
	Vector2 pos = GetPos();
	if (KEY_PRESS(KEY_TYPE::LEFT)) {
		pos.x -= 100.0f * fDT;
	}
	if (KEY_PRESS(KEY_TYPE::RIGHT)) {
		pos.x += 100.0f * fDT;
	}
	
	if (KEY_PRESS(KEY_TYPE::UP)) {
		pos.y -= 100.0f * fDT;
	}
	
	if (KEY_PRESS(KEY_TYPE::DOWN)) {
		pos.y += 100.0f * fDT;
	}
	SetPos(pos);
}
