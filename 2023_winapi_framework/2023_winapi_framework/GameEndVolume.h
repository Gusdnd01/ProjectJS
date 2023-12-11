#pragma once
#include "Object.h"
class GameEndVolume :
    public Object
{
public:
    GameEndVolume();
    ~GameEndVolume();
public:
    void EnterCollision(Collider* other);

public:
    void Render(HDC _dc);
};

