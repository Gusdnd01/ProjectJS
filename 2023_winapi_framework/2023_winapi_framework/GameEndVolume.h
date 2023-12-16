#pragma once
#include "Object.h"
class Texture;
class GameEndVolume :
    public Object
{
public:
    GameEndVolume();
    ~GameEndVolume();
public:
    void EnterCollision(Collider* other);

public:
    void Update();
    void Render(HDC _dc);

private:
    Texture* m_pTex;
};

