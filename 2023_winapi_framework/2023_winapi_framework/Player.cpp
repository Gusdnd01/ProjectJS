#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Scene.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Gravity.h"

Player::Player()
	: m_pTex(nullptr)
	, m_bLeft(false)
	, m_bIsJump(false)
	, m_bIsGround(false)
	, m_fTimer(0.0f)
	, m_fJumpPower(5.0f)
	, m_sState(STATE::IDLE)
{
	this->SetName(L"Player");

	m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\jumpking.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f,50.f));

	CreateRigidBody();
	GetRigidBody()->SetMass(5.0f);
	GetRigidBody()->SetFriction(100.0f);
	GetRigidBody()->SetMaxVelocity(Vec2(200.0f, 500.0f));

	CreateGravity();

	//if you want modify Collider's offset. use this
	//GetCollider()->SetOffSetPos(Vec2(50.f,0.f));
	
	//Animator and animation setting 
	CreateAnimator();
	GetAnimator()->CreateAnim(L"jumpking_idle", m_pTex,Vec2(0.f, 150.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.2f);
	GetAnimator()->CreateAnim(L"jumpking_walk", m_pTex, Vec2(0.f, 100.f),
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
	//// 1. �⺻ �ű��
	//BitBlt(_dc
	//	,(int)(vPos.x - vScale.x /2)
	//	,(int)(vPos.y - vScale.y /2)
	//	, Width,Height, m_pTex->GetDC()
	//	,0,0,SRCCOPY);

	//// 2. ���� �Ⱦ��
	//TransparentBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width, Height, m_pTex->GetDC()
	//	, 0, 0, Width,Height, RGB(255,0,255));

	//// 3. Ȯ�� �� ���
	//StretchBlt(_dc
	//	, (int)(vPos.x - vScale.x / 2)
	//	, (int)(vPos.y - vScale.y / 2)
	//	, Width ,Height, m_pTex->GetDC()
	//	, 0, 0, Width, Height, SRCCOPY);

	// 4. ȸ��
	// �ﰢ�Լ�, ȸ�����
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
	m_bIsGround = GetGravity()->GetOnGround();
	
	STATE state = STATE::IDLE;

	//some actions

	if (m_bIsGround && KEY_DOWN(KEY_TYPE::A)) {
		GetRigidBody()->AddForce(Vec2(-350.0f, 0.0f), FORCE_MODE::IMPULSE);
	}
	if (m_bIsGround && KEY_DOWN(KEY_TYPE::D)) {
		GetRigidBody()->AddForce(Vec2(350.0f, 0.0f), FORCE_MODE::IMPULSE);
	}
	if (m_bIsGround && KEY_UP(KEY_TYPE::A)) {
		GetRigidBody()->StopImmediatelyX();
	}
	if (m_bIsGround && KEY_UP(KEY_TYPE::D)) {
		GetRigidBody()->StopImmediatelyX();
	}

	if (m_bIsGround && KEY_PRESS(KEY_TYPE::A)) {
		state = STATE::MOVE;
		m_bLeft = true;
	}
	if (m_bIsGround && KEY_PRESS(KEY_TYPE::D)) {
		state = STATE::MOVE;
		m_bLeft = false;
	}

	if (m_bIsGround&& KEY_PRESS(KEY_TYPE::SPACE)) {
		state = STATE::JUMP_CHARGE;
	}
	if (m_bIsGround&&KEY_UP(KEY_TYPE::SPACE)) {
		m_bIsJump = true;
		state = STATE::JUMP;
	}

	//lastly change state
	StateChange(state);
	
	//default is idle
}

#pragma region FSM
void Player::StateUpdate()
{
	//���� ���¸� ���ϰ� �� ���� ���� ����ġ���� ������.
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
	//���̵� �ִϸ��̼� ���ุ ���ش�.
	//idle animation
	GetAnimator()->PlayAnim(L"Jiwoo_Front", true);
}

void Player::JumpState()
{
	//jump animation
	//GetAnimator()->PlayAnim(L"Jump", false);

	//���� �������� �÷��� ���� �Ŀ���ŭ ���� �����ش�.
	GetRigidBody()->AddForce(Vec2(0.0f, -m_fJumpPower), FORCE_MODE::IMPULSE);
	m_fJumpPower = 10.0f;
}

void Player::JumpChargeState()
{
	//�����Ӵ� ����
	m_fJumpPower += 1.0f * fDT;

	//�ִ밪 ����
	m_fJumpPower = clamp(m_fJumpPower, 100.0f, 500.0f);
}

void Player::HurtState()
{
	//Get hurt action
	//���⼭�� ���� �΋H���� ���� �������� ����!
}

void Player::MoveState()
{
	//Move Animation and move action
	if (m_bLeft) {
		GetRigidBody()->AddForce(Vec2(-350.0f, 0.0f), FORCE_MODE::FORCE);
		GetAnimator()->PlayAnim(L"Jiwoo_Left", true);
	}
	else {
		GetRigidBody()->AddForce(Vec2(350.0f, 0.0f),FORCE_MODE::FORCE);
		GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	}

}
#pragma endregion

