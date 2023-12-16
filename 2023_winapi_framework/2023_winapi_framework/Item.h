#pragma once
#include "Object.h"
class ItemFactory;
class Texture;
class Item :
    public Object
{
public:
    Item();
    ~Item();

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    void SetOwner(ItemFactory* _value) { m_pOwner = _value; }
    void SetType(const wstring& _value) { m_wItemType = _value; }

public:
    virtual void EnterCollision(Collider* other);

protected:
    Texture* m_pTex;
    ItemFactory* m_pOwner;
    wstring m_wItemType;
};
