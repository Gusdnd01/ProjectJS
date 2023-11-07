#pragma once
#include "Object.h"
class TestObj :
    public Object
{
public:
    TestObj();
    ~TestObj();

public:
    void Update() override;
    void Render(HDC _dc) override;
};

