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
#include "GravityManager.h"

Player::Player()
	: m_pTex(nullptr)
	, m_bLeft(false)
	, m_sState(STATE::IDLE)
	, m_fJumpPower(3.0f)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\jiwoo.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f,30.f));

	CreateRigidBody();
	GetRigidBody()->SetMass(50.0f);
	GetRigidBody()->SetGravity(7.0f);

	GMGI->AddGravObj(this);

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
	if(m_bIsJump == false)
		PlayerInput();
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
	if (m_bIsJump) return;
	
	//default is idle
	STATE state = STATE::IDLE;

	//some actions
	if (KEY_PRESS(KEY_TYPE::LEFT)) {
		state = STATE::MOVE;
		m_bLeft = true;
	}
	if (KEY_PRESS(KEY_TYPE::RIGHT)) {
		state = STATE::MOVE;
		m_bLeft = false;
	}
	if (KEY_DOWN(KEY_TYPE::SPACE)) {
		state = STATE::JUMP;
	}

	//lastly change state
	StateChange(state);
}


#pragma region FSM
void Player::StateUpdate()
{
	switch (m_sState)
	{
	case STATE::MOVE:
		MoveState(m_bLeft);
		break;
	case STATE::IDLE:
		IdleState();
		break;
	case STATE::JUMP:
		m_bIsJump = true;
		GetRigidBody()->SetGravity(-m_fJumpPower);
		JumpState();
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
	//idle animation
	GetAnimator()->PlayAnim(L"Jiwoo_Front", true);
}

void Player::JumpState()
{
	//jump animation
	//GetAnimator()->PlayAnim(L"Jump", false);

	//timer
	m_fTimer += fDT;

	

	//if timer is greater than 1
	if (m_fTimer >= 1 ) {
		//redirect state to idle

		//Compo status change
		GetRigidBody()->SetGravity(7.0f);
		
		//if Collider's Check Bottom is true
		if (GetCollider()->GetCheckBottom()) {
			//timer and jump setting
			m_fTimer = 0;
			m_bIsJump = false;
			StateChange(STATE::IDLE);
		}
	}
	if (m_bIsJump) GetCollider()->SetCheckBottom(false);
	else GetCollider()->SetCheckBottom(true);
}

void Player::HurtState()
{
	//Get hurt action
}

void Player::MoveState(bool left)
{
	Vec2 pos = GetPos();

	//Move Animation and move action
	if (left) {
		pos.x -= 100.0f * fDT;
		GetAnimator()->PlayAnim(L"Jiwoo_Left", true);
	}
	else {
		pos.x += 100.0f *fDT;
		GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	}

	SetPos(pos);
}
#pragma endregion

