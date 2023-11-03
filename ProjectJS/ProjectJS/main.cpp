﻿// ProjectJS.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "ProjectJS.h"
#include "Core.h"
#include "BaseWindow.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    BaseWindow game({ WINDOW_WIDTH, WINDOW_HEIGHT });
    game.Run(hInstance, lpCmdLine, nCmdShow);
}