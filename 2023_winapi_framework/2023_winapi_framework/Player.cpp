#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Bullet.h"
#include "Scene.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "RigidBody.h"

Player::Player()
	: m_pTex(nullptr)
	, m_bLeft(false)
	, m_bIsJump(false)
	, m_bIsGround(false)
	, m_fTimer(0.0f)
	, m_fJumpPower(5.0f)
	, m_sState(STATE::IDLE)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\jiwoo.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f,30.f));

	CreateRigidBody();
	GetRigidBody()->SetMass(5.0f);
	GetRigidBody()->SetFriction(50.0f);
	GetRigidBody()->SetMaxVelocity(1000.0f);

	//if you want modify Collider's offset. use this
	//GetCollider()->SetOffSetPos(Vec2(50.f,0.f));
	
	//Animator and animation setting 
	CreateAnimator();
	GetAnimator()->CreateAnim(L"Jiwoo_Front", m_pTex,Vec2(0.f, 150.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->CreateAnim(L"Jiwoo_Back", m_pTex, Vec2(0.f, 100.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->CreateAnim(L"Jiwoo_Left", m_pTex, Vec2(0.f, 0.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->CreateAnim(L"Jiwoo_Right", m_pTex, Vec2(0.f, 50.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->CreateAnim(L"Jiwoo_Attack", m_pTex, Vec2(0.f, 200.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->PlayAnim(L"Jiwoo_Front",true);

	//animation offset change
	//Animation* pAnim = GetAnimator()->FindAnim(L"Jiwoo_Front");
	// only one 
	//pAnim->SetFrameOffset(0, Vec2(0.f, 20.f));

	//all frames
	//for (size_t i = 0; i < pAnim->GetMaxFrame(); ++i)
	//	pAnim->SetFrameOffset(i, Vec2(0.f, 20.f));
}
Player::~Player()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}
void Player::Update()
{
	//get input
	PlayerInput();

	//fsm loop
	StateUpdate();

	GetAnimator()->Update();
}

void Player::Render(HDC _dc)
{
	//Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();
	//int Width = m_pTex->GetWidth();
	//int Height = m_pTex->GetHeight();
	//// 1. 기본 옮기기
	//BitBlt(_dc
	//	,(int)(vPos.x - vScale.x /2)
	//	,(int)(vPos.y - vScale.y /2)
	//	, Width,Height, m_pTex->GetDC()
	//	,0,0,SRCCOPY);

	//// 2. 색상 걷어내기
	//TransparentBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width, Height, m_pTex->GetDC()
	//	, 0, 0, Width,Height, RGB(255,0,255));

	//// 3. 확대 및 축소
	//StretchBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width ,Height, m_pTex->GetDC()
	//	, 0, 0, Width, Height, SRCCOPY);

	// 4. 회전
	// 삼각함수, 회전행렬
	//Plgblt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width, Height, m_pTex->GetDC()
	//	, 0, 0, Width, Height, RGB(255, 0, 255));
	Component_Render(_dc);
}

void Player::EnterCollision(Collider* other)
{
}

void Player::ExitCollision(Collider* other)
{
}

void Player::CheckBottom(Collider* other)
{
}

void Player::PlayerInput()
{
	//player during jump, return Input
	//if (m_bIsJump) return;
	STATE state = STATE::IDLE;

	//some actions
	if (m_bIsGround && KEY_PRESS(KEY_TYPE::A)) {
		state = STATE::MOVE;
		m_bLeft = true;
	}
	if (m_bIsGround && KEY_PRESS(KEY_TYPE::D)) {
		state = STATE::MOVE;
		m_bLeft = false;
	}
	if (m_bIsGround && KEY_DOWN(KEY_TYPE::SPACE)) {
		state = STATE::JUMP_CHARGE;
	}
	if (m_bIsGround && KEY_UP(KEY_TYPE::SPACE)) {
		m_bIsJump = true;
		state = STATE::JUMP;
	}

	//lastly change state
	StateChange(state);
	//default is idle
	
}

void Player::CalculateGravity()
{
	if (GetCollider() != nullptr) m_bIsGround = GetCollider()->GetCheckBottom();

	//만약 땅에 있는 상태라면 내려가는걸 바로 멈춰준다.
	if (m_bIsGround && !m_bIsJump) {
		GetRigidBody()->StopImmediately();
	}

	//200의 힘으로 밑으로 계속 가속해준다.
	GetRigidBody()->AddForce(Vec2(0.0f, 500.0f));
}


#pragma region FSM
void Player::StateUpdate()
{
	//현제 상태를 구하고 그 값에 따라 스위치문을 돌린다.
	switch (m_sState)
	{
	case STATE::IDLE:
		IdleState();
		break;

	case STATE::MOVE:
		MoveState();
		break;
	
	case STATE::JUMP:
		JumpState();
		break;

	case STATE::JUMP_CHARGE:
		JumpChargeState();
		break;

	case STATE::HURT:	
		HurtState();
		break;

	case STATE::END:
		break;

	default:
		break;
	}
}
void Player::StateChange(STATE _type)
{
	if (_type == STATE::END) return;
	m_sState = _type;
}

void Player::IdleState()
{
	//여기선 중력계산이랑 아이들 애니메이션 실행만 해준다.
	//idle animation
	GetAnimator()->PlayAnim(L"Jiwoo_Front", true);
	CalculateGravity();
}

void Player::JumpState()
{
	//jump animation
	//GetAnimator()->PlayAnim(L"Jump", false);

	//점프 차지에서 올려준 점프 파워만큼 힘을 더해준다.
	GetRigidBody()->AddForce(Vec2(0.0f, -m_fJumpPower));
}

void Player::JumpChargeState()
{
	//프레임당 증가
	m_fJumpPower += 200.0f ;

	//최대값 지정
	m_fJumpPower = clamp(m_fJumpPower, 0.0f, 5000.0f);
}

void Player::HurtState()
{
	//Get hurt action
	//여기서는 벽에 부딫혔을 때에 실행해줄 무언가!
}

void Player::MoveState()
{
	//Move Animation and move action
	if (m_bLeft) {
		GetRigidBody()->AddForce(Vec2(-400.0f, 0.0f));
		GetAnimator()->PlayAnim(L"Jiwoo_Left", true);
	}
	else {
		GetRigidBody()->AddForce(Vec2(400.0f, 0.0f));
		GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	}

}
#pragma endregion

