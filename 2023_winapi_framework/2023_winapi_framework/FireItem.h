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
    void EnterCollision(Collider* other) override;

};

