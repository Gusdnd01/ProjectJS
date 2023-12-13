#pragma once
#include "Object.h"

template <class T>
class ItemFactory :
    public Object
{
public:
    ItemFactory();
    ~ItemFactory();

public:
    void Update();

public:
    void SetFactory(T _value) { m_pObjInstance = _value; }
    void SetDuration(float _value) { m_fDuration = _value; }

private:
    T m_pObjInstance;
    T* m_pCurObject;
    float m_fTimer;
    float m_fDuration;
};

