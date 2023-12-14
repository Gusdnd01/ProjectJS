#pragma once
#include "Object.h"

class Texture;
class Tree :
    public Object
{
public:
    Tree();
    ~Tree();
public:
    void Render(HDC _dc) override;

private:
    Texture* m_pTex;
};

