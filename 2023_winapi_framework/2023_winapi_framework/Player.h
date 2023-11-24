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

    void CheckBottom(Collider* other) override;
    
public:
    void PlayerInput();

public:
    void StateUpdate();
    void StateChange(STATE _type);
    void IdleState();
    void JumpState(Vec2& pos);
    void HurtState();
    void MoveState(Vec2& pos, bool left);

public:
    const bool& GetIsJump() const { return m_bIsJump; }

private:
    Texture* m_pTex;
    RigidBody* m_rb;
    float    m_fTimer = 0.0f;
    float    m_fPercent = 0.0f;
    float    m_fJumpPower;
    bool     m_bLeft = false;  
    bool     m_bIsJump = false;
    STATE    m_sState;
};

