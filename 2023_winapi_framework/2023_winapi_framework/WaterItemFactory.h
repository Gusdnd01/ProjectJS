#pragma once
#include "ItemFactory.h"
class WaterItemFactory :
    public ItemFactory
{
public:
    WaterItemFactory();
    ~WaterItemFactory();

public:
    void Update() override;

private:
    float m_fTimer;
};

