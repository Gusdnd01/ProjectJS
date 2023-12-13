#pragma once
#include "Item.h"
class WaterItem :
    public Item
{
public:
    WaterItem();
    ~WaterItem();

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    void EnterCollision(Collider* other) override;
};

