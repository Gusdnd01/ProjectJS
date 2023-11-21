#pragma once
#include "Object.h"

enum class STATE {
    MOVE,
    IDLE,
    JUMP,
    HURT,
    END = 10
};

class Texture;

class Player :
    public Object
{
public:
    Player();
    ~Player();

public:
    void Update() override;
    void Render(HDC _dc) override;
    void EnterCollision(Collider* other) override;
    void ExitCollision(Collider* other) override;
    Vec2 CalculateGravity();
    Vec2 CalculateMovement();

public:
    void StateUpdate();
    void StateChange(STATE _type);
    void IdleState();
    void JumpState();
    void HurtState();
    void MoveState(bool left);

private:
    Texture* m_pTex;
    bool     m_bIsGround = false;
    bool     m_bLeft = false;   
    float    m_fGravity = 9.8f;
    STATE    m_sState;
};

