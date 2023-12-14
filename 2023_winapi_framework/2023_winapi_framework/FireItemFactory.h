#pragma once
#include "ItemFactory.h"
class FireItemFactory :
    public ItemFactory
{
public:
    FireItemFactory();
    ~FireItemFactory();

public:
    void Update() override;

private:
    float m_fTimer;
};

