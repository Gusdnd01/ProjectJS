#pragma once
#include "Object.h"
class Ground :
    public Object
{
public:
    Ground();
    ~Ground();

public:
    void Update() override;

public:
    void EnterCollision(Collider* _other);
};

