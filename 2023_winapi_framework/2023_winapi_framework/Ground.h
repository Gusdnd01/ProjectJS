#pragma once
#include "Object.h"
class Texture;
class Ground :
    public Object
{
public:
    Ground();
    ~Ground();

public:
    void Render(HDC _dc) override;

public:
    void EnterCollision(Collider* _other);
    void ExitCollision(Collider* _other);

public:
    void SetTiles(int _middle);

private:
    Texture* m_pTex;
    tTileSlice m_tileSlices;
};

