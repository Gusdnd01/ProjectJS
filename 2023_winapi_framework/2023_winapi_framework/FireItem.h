#pragma once
#include "Item.h"
class ItemFactory;
class FireItem :
    public Item
{
public:
    FireItem();
    ~FireItem();

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    void SetOwner(ItemFactory* _value) { m_pOwner = _value; }

public:
    void EnterCollision(Collider* other) override;

private:
    ItemFactory* m_pOwner;
};

