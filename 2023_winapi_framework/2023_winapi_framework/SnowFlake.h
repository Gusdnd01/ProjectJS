#pragma once
#include "Object.h"
class Texture;
class SnowFlake :
    public Object
{
public:
    SnowFlake();
    ~SnowFlake();
public:
    void Update() override;
    void Render(HDC _dc) override;

private:
    Texture* m_pTex;
    float m_fTimer;
};

