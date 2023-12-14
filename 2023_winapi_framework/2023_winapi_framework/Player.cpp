#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "ShowSetting.h"
#include "Scene.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "JumpEffect.h"
#include "RigidBody.h"
#include "Gravity.h"
#include "Ground.h"
#include "Core.h"

Player::Player()
	: m_pTex(nullptr)
	, m_bLeft(false)
	, m_bIsJump(false)
	, m_bIsUp(false)
	, m_bCanMove(false)
	, m_bIsGround(false)
	, m_fTimer(0.0f)
	, m_fJumpPower(5.0f)
	, m_sState(STATE::IDLE)
{
	this->SetName(L"Player");
	this->SetIsClamp(true);
	m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\player.bmp");


	CreateCollider();
	//애니메이터 오프셋 옮겨주는거로 해결
	GetCollider()->SetScale(Vec2(48.0f, 48.0f));

	CreateRigidBody();
	GetRigidBody()->SetMass(10.0f);
	GetRigidBody()->SetFriction(1000.0f);
	GetRigidBody()->SetMaxVelocity(Vec2(1000.0f, 2000.0f));

	CreateGravity();

	//Animator and animation setting 
	CreateAnimator();
	//Right Animation
	GetAnimator()->CreateAnim(L"frog_idleR", m_pTex, Vec2(0.0f, 0.0f), Vec2(48.0f, 48.0f), Vec2(48.0f, 0.f), 8, 0.2f);
	GetAnimator()->CreateAnim(L"frog_hopR", m_pTex, Vec2(0.f, 48.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 7, 0.1f);
	GetAnimator()->CreateAnim(L"frog_jump_chargeR", m_pTex, Vec2(48.0f * 2.0f, 48.0f), Vec2(48.0f), Vec2(48.0f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim(L"frog_jumpR", m_pTex, Vec2(48.f * 3.0f, 48.0f), Vec2(48.0f), Vec2(48.f, 0.f), 1, 0.1f);
	GetAnimator()->CreateAnim(L"frog_fallR", m_pTex, Vec2(48.0f * 6.0f, 48.0f), Vec2(48.0f), Vec2(48.0f, 0.0f), 1, 0.1f);

	////Left Animation
	GetAnimator()->CreateAnim(L"frog_idleL", m_pTex, Vec2(0.0f, 240.0f), Vec2(48.0f, 48.0f), Vec2(48.0f, 0.f), 8, 0.2f);
	GetAnimator()->CreateAnim(L"frog_hopL", m_pTex, Vec2(0.f, 288.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 7, 0.1f);
	GetAnimator()->CreateAnim(L"frog_jump_chargeL", m_pTex, Vec2(48.0f * 2.0f, 288.0f), Vec2(48.0f, 48.0f), Vec2(48.0f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim(L"frog_jumpL", m_pTex, Vec2(48.f * 3.0f, 288.0f), Vec2(48.0f, 48.0f), Vec2(48.f, 0.f), 1, 0.1f);
	GetAnimator()->CreateAnim(L"frog_fallL", m_pTex, Vec2(48.0f * 6.0f, 288.0f), Vec2(48.0f, 48.0f), Vec2(48.0f, 0.0f), 1, 0.1f);

	//Right Idle Play
	GetAnimator()->PlayAnim(L"frog_idleR", true);

	//animation offset change
	//Animation* pAnim = GetAnimator()->FindAnim(L"Jiwoo_Front");
	// only one 
	//pAnim->SetFrameOffset(0, Vec2(0.f, 20.f));

	ResMgr::GetInst()->LoadSound(L"JumpSound",L"Sound\\Jump.wav",false);
	ResMgr::GetInst()->LoadSound(L"FallHitSound",L"Sound\\HitDam.wav",false);

	//all frames
	/*for (auto pAnim : GetAnimator()->GetAnimationMap()) {
		Animation* tempAnim = pAnim.second;
		for (size_t i = 0; i < tempAnim->GetMaxFrame(); ++i)
			tempAnim->SetFrameOffset(i, Vec2(-48.0f));
	}*/
}
Player::~Player()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}
void Player::Update()
{
	if (ShowSetting::GetInst()->IsEscActive || ShowSetting::GetInst()->IsActive) {
		GetRigidBody()->StopImmediatelyX();
		return; 
	}
	Object::Update(); 

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
	Ground* ground = dynamic_cast<Ground*>(other->GetObj());
	if (ground) {
		if (GetCollider()->CheckBottom(other) && (!GetCollider()->CheckLeft(other) || !GetCollider()->CheckRight(other))) {
			GetRigidBody()->StopImmediatelyX();
			m_bIsJump = false;
		}
		else if (GetCollider()->CheckLeft(other) && !m_bIsGround) {
			GetRigidBody()->StopImmediatelyX();
			GetRigidBody()->AddForce(Vec2(200.0f, -200.0f), FORCE_MODE::IMPULSE);
			GetGravity()->OnGround(false);
		}
		else if (GetCollider()->CheckRight(other) && !m_bIsGround) {
			GetRigidBody()->StopImmediatelyX();
			GetRigidBody()->AddForce(Vec2(-200.0f, -200.0f), FORCE_MODE::IMPULSE);
			GetGravity()->OnGround(false);
		}
		if (GetCollider()->CheckTop(other)) {
			GetRigidBody()->StopImmediatelyY();
			GetGravity()->OnGround(false);
			//GetRigidBody()->AddForce(Vec2(0.0f, 1000.0f), FORCE_MODE::IMPULSE);
		}
		//ResMgr::GetInst()->Play(L"FallHitSound");
	}
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
	m_bIsGround = GetGravity()->GetOnGround();

	STATE state = STATE::IDLE;
	//some actions

	if (state == STATE::IDLE && m_bIsGround) {
		if (m_bCanMove) {
			if (KEY_DOWN(KEY_TYPE::LEFT)) {
				GetRigidBody()->AddForce(Vec2(-350.0f, 0.0f), FORCE_MODE::IMPULSE);
			}
			if (KEY_DOWN(KEY_TYPE::RIGHT)) {
				GetRigidBody()->AddForce(Vec2(350.0f, 0.0f), FORCE_MODE::IMPULSE);
			}
			if (KEY_DOWN(KEY_TYPE::UP)) {
				m_bIsUp = true;
			}
			if (KEY_PRESS(KEY_TYPE::LEFT)) {
				state = STATE::MOVE;
				m_bLeft = true;
			}
			if (KEY_PRESS(KEY_TYPE::RIGHT)) {
				state = STATE::MOVE;
				m_bLeft = false;
			}
		}
		if (KEY_UP(KEY_TYPE::LEFT)) {
			GetRigidBody()->StopImmediatelyX();
		}
		if (KEY_UP(KEY_TYPE::RIGHT)) {
			GetRigidBody()->StopImmediatelyX();
		}
		if (KEY_UP(KEY_TYPE::UP)) {
			m_bIsUp = false;
		}

		if (KEY_PRESS(KEY_TYPE::SPACE)) {
			GetRigidBody()->StopImmediatelyX();
			state = STATE::JUMP_CHARGE;
		}
		if (KEY_UP(KEY_TYPE::SPACE)) {
			m_bIsJump = true;
			state = STATE::JUMP;
		}
	}


	if (!m_bIsGround && GetRigidBody()->GetVelocity().y >= 0) {
		state = STATE::FALL;
	}

	//lastly change state
	StateChange(state);

	//default is idle
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
		m_bCanMove = false;
		JumpChargeState();
		break;

	case STATE::FALL:
		FallState();
		break;

	case STATE::HURT:
		HurtState();
		break;

	default:
		break;
	}
}
void Player::StateChange(STATE _type)
{
	m_sState = _type;
}

void Player::IdleState()
{
	//아이들 애니메이션이나 점프 애니메이션을 실행 해준다.
	//idle animation
	m_bCanMove = true;
	if (m_bIsJump) {
		if (!m_bLeft) {
			GetAnimator()->PlayAnim(L"frog_jumpR", true);
		}
		else {
			GetAnimator()->PlayAnim(L"frog_jumpL", true);
		}
	}
	else {
		if (!m_bLeft) {
			GetAnimator()->PlayAnim(L"frog_idleR", true);
		}
		else {
			GetAnimator()->PlayAnim(L"frog_idleL", true);
		}
	}
	//jump animation
}

void Player::JumpState()
{
	//jump animation
	//GetAnimator()->PlayAnim(L"Jump", false);

	//현제 바라보고 있는 방향에 따라서 x축에 가해줄 힘을 구해준다.
	float xForce = 350.0f + (m_fJumpPower * 0.2f);
	xForce = m_bLeft ? -xForce : xForce;

	if (m_bIsUp) {
		xForce = 0.0f;
	}

	//점프 차지에서 올려준 점프 파워만큼 힘을 더해준다.
	GetRigidBody()->AddForce(Vec2(xForce, -m_fJumpPower), FORCE_MODE::IMPULSE);
	m_fJumpPower = 10.0f;

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	JumpEffect* jumpEffect = new JumpEffect;
	jumpEffect->SetPos(vPos- vScale / 2.0f);
	jumpEffect->SetScale(Vec2(2.0f));
	SceneMgr::GetInst()->GetCurScene()->AddObject(jumpEffect,OBJECT_GROUP::EFFECT);

	ResMgr::GetInst()->Play(L"JumpSound");
	m_bIsUp = false;
}

void Player::FallState()
{
	if (!m_bLeft) {
		GetAnimator()->PlayAnim(L"frog_fallR", true);
	}
	else {
		GetAnimator()->PlayAnim(L"frog_fallL", true);
	}
}

void Player::JumpChargeState()
{
	if (!m_bLeft) {
		GetAnimator()->PlayAnim(L"frog_jump_chargeR", true);
	}
	else {
		GetAnimator()->PlayAnim(L"frog_jump_chargeL", true);
	}

	//프레임당 증가
	m_fJumpPower += 500.0f * fDT;

	//최대값 지정
	m_fJumpPower = clamp(m_fJumpPower, 500.0f, 1450.0f);
}

void Player::HurtState()
{
	//Get hurt action
	//여기서는 벽에 부딫혔을 때에 실행해줄 무언가!
}

void Player::MoveState()
{
	//Move Animation and move action

	if (!m_bLeft) {
		GetAnimator()->PlayAnim(L"frog_hopR", true);
	}
	else {
		GetAnimator()->PlayAnim(L"frog_hopL", true);
	}

	if (m_bLeft) {
		GetRigidBody()->AddForce(Vec2(-350.0f, 0.0f), FORCE_MODE::FORCE);
	}
	else {
		GetRigidBody()->AddForce(Vec2(350.0f, 0.0f), FORCE_MODE::FORCE);
	}

}
#pragma endregion

