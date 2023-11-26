#pragma once
#include "Object.h"

enum class STATE {
    MOVE,
    IDLE,
    JUMP,
    JUMP_CHARGE,
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
    void CalculateGravity();

public:
    void StateUpdate();
    void StateChange(STATE _type);
    void IdleState();
    void JumpState();
    void JumpChargeState();
    void HurtState();
    void MoveState();

public:
    const bool& GetIsJump() const { return m_bIsJump; }

private:
    Texture* m_pTex;
    bool     m_bLeft;  
    bool     m_bIsJump;
    bool     m_bIsGround;
    float    m_fTimer = 0.0f;
    float    m_fJumpPower;
    STATE    m_sState;
};

