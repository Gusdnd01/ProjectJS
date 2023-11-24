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
class RigidBody;

class Player :
    public Object
{
public:
    Player();
    ~Player();

public:
    void Update() override;
    void Render(HDC _dc) override;
    
public:
    void EnterCollision(Collider* other) override;
    void ExitCollision(Collider* other) override;
    
public:
    void PlayerInput();

public:
    void StateUpdate();
    void StateChange(STATE _type);
    void IdleState();
    void JumpState(Vec2& pos);
    void HurtState();
    void MoveState(Vec2& pos,bool left);

private:
    Texture* m_pTex;
    RigidBody* m_rb;
    bool     m_bLeft = false;   
    float    m_fTimer = 0.0f;
    bool     m_bIsJump = false;
    STATE    m_sState;
};

