#pragma once
#include "Object.h"
class Texture;
class Tile :
    public Object
{
public:
    Tile();
    ~Tile();

public:
    void Render(HDC _dc) override;

};
