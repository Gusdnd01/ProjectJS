#pragma once
#include "Object.h"

class ItemFactory :
    public Object
{
public:
    ItemFactory();
    ~ItemFactory();

public:
    virtual void Update();

public:
    Object* GetFactory() const { return m_pCurObject; }
    float GetDuration() const { return m_fDuration; }

public:
    void SetDuration(float _value) { m_fDuration = _value; }
    void SetFactory(Object* _value) { m_pCurObject = _value; }

public:
    void ResetObj() { m_pCurObject = nullptr; }
private:
    Object* m_pCurObject;
    
    float m_fDuration;
};

