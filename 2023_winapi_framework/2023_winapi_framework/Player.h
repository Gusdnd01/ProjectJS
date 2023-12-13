#pragma once
#include "Object.h"
enum class STATE {
    MOVE,
    IDLE,
    JUMP,
    JUMP_CHARGE,
    HURT,
    FALL,
    END = 10,
};

enum class PLAYER_MODE {
    NORMAL,
    WATER,
    END = 10,
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

    //FSM Funtion
public:
    void IdleState();
    void JumpState();
    void FallState();
    void JumpChargeState();
    void HurtState();
    void MoveState();

public:
    const bool& GetIsJump() const { return m_bIsJump; }

    const PLAYER_MODE GetPlayerMode() const { return m_sMode; }

public:
    void SetMode(PLAYER_MODE _value) { m_sMode = _value; }

private:
    Texture*    m_pTex;
    bool        m_bLeft;  
    bool        m_bIsJump;
    bool        m_bIsUp;
    bool        m_bIsGround;
    bool        m_bCanMove;
    float       m_fTimer = 0.0f;
    float       m_fJumpPower;
    STATE       m_sState;
    PLAYER_MODE m_sMode;
    string      m_LR;
    UINT        m_nLevel;
};

