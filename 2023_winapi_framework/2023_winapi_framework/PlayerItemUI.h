#pragma once
#include "Object.h"
class Texture;
class Player;
class PlayerItemUI :
    public Object
{
    //�÷��̾� ���� ��ܿ� �־���Ѵ�.
    //�Ծ��� �� ������ ������ ��� �� ������.
public:
    PlayerItemUI();
    ~PlayerItemUI();

public:
    void Update();
    void Render(HDC _dc);

public:
    void SetActive(bool _value) { m_bIsActive = _value; };
    void SetTexture(Texture* _value) { m_pTex = _value; }
    void SetOffsetPos(Vec2 _value) { m_vOffsetPos = _value; }
    void SetOwner(Object* _value) { m_pOwner = _value; }
    void SetPlayer(Player* _value) { m_pPlayer = _value; }

private:
    Object* m_pOwner;
    Player* m_pPlayer;
    Texture* m_pTex;
    bool m_bIsActive;
    Vec2 m_vOffsetPos;
};

