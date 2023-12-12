#pragma once
#include "Object.h"

class Texture;
class Item :
    public Object
{
public:
    Item();
    ~Item();

public:
    virtual void Render(HDC _dc);

public:
    virtual void EnterCollision(Collider* other);

protected:
    Texture* m_pTex;
};

