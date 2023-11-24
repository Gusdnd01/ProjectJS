#pragma once
class ShowSetting
{
	SINGLE(ShowSetting);
public:
	bool IsActive = false;
public:
	void Init();
	void Render(HDC _dc);
};