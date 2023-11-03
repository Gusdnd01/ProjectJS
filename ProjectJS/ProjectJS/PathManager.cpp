#include "pch.h"
#include "PathManager.h"

void PathManager::Init()
{
	GetCurrentDirectory(255, strResPath);
	wcscat_s(strResPath, 255, L"\\Res\\");
}
