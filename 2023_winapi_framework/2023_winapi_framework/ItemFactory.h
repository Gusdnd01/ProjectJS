#pragma once
#include "Object.h"

class ItemFactory :
    public Object
{
public:
    ItemFactory();
    ~ItemFactory();

public:
    void Update();

public:
    void SetDuration(float _value) { m_fDuration = _value; }
    void ResetObj() { m_pCurObject = nullptr; }
private:
    Object* m_pCurObject;
    float m_fTimer;
    float m_fDuration;
};

