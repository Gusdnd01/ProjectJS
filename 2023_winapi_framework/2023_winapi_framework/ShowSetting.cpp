#include "pch.h"
#include "ShowSetting.h"
#include "Core.h"
#include "KeyMgr.h"

void ShowSetting::Init()
{

}

void ShowSetting::Render(HDC _dc)
{
	int x = Core::GetInst()->GetResolution().x / 2;
	int y = Core::GetInst()->GetResolution().y / 2;

	if (IsActive)
	{
		Rectangle(_dc, x - 500, y - 250 , x + 500, y + 250);

		TextOut(_dc, x, y - 220, L"¼³Á¤Ã¢", 3);


		if (KEY_DOWN(KEY_TYPE::ESC))
		{
			IsActive = false;
		}
	}
}

void ShowSetting::Update()
{

}
