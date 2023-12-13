#pragma once
#include "Object.h"
class Texture;
class LowVelocitySpace :
    public Object
{
public:
    LowVelocitySpace();
    ~LowVelocitySpace();

public:
    void Update();
    void Render(HDC _dc);

public:
    void EnterCollision(Collider* other);
    void ExitCollision(Collider* other);

private:
    Texture* m_pTex;
    Vec2 m_vAddVelo;
};