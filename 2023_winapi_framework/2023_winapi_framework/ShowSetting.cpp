#include "pch.h"
#include "ShowSetting.h"

void ShowSetting::Init()
{
	if (!IsActive) return;
}

void ShowSetting::Render(HDC _dc)
{
	Rectangle(_dc, 100, 100, 100, 100);
}
