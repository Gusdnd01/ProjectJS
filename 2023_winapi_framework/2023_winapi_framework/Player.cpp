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

	m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\frog_base.bmp");

	CreateCollider();
	//�������̶� ũ�� �����ߴµ� �� ũ�⸸ �����Ű�� �Ȱ��� ������?
	GetCollider()->SetScale(Vec2(48.0f, 48.0f));

	CreateRigidBody();
	GetRigidBody()->SetMass(5.0f);
	GetRigidBody()->SetFriction(100.0f);
	GetRigidBody()->SetMaxVelocity(Vec2(200.0f, 1000.0f));

	CreateGravity();

	//if you want modify Collider's offset. use this
	
	//Animator and animation setting 
	CreateAnimator();
	//Right Animation
	GetAnimator()->CreateAnim(L"frog_idleR", m_pTex,Vec2(0.0f, 0.0f),Vec2(48.0f, 48.0f), Vec2(48.0f, 0.f),8, 0.2f);
 	GetAnimator()->CreateAnim(L"frog_hopR", m_pTex, Vec2(0.f, 48.f),Vec2(48.f, 48.f), Vec2(48.f, 0.f), 7, 0.1f);
	GetAnimator()->CreateAnim(L"frog_jump_chargeR", m_pTex, Vec2(48.0f * 2.0f, 48.0f), Vec2(48.0f), Vec2(48.0f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim(L"frog_jumpR", m_pTex, Vec2(48.f * 3.0f, 48.0f), Vec2(48.0f), Vec2(48.f, 0.f), 1, 0.1f);
	GetAnimator()->CreateAnim(L"frog_fallR", m_pTex, Vec2(48.0f * 6.0f, 48.0f),Vec2(48.0f), Vec2(48.0f, 0.0f), 1, 0.1f);

	//Left Animation
	GetAnimator()->CreateAnim(L"frog_idleL", m_pTex,Vec2(0.0f, 240.0f),Vec2(48.0f, 48.0f), Vec2(48.0f, 0.f),8, 0.2f);
 	GetAnimator()->CreateAnim(L"frog_hopL", m_pTex, Vec2(0.f, 288.f),Vec2(48.f, 48.f), Vec2(48.f, 0.f), 7, 0.1f);
	GetAnimator()->CreateAnim(L"frog_jump_chargeL", m_pTex, Vec2(48.0f * 2.0f, 288.0f), Vec2(48.0f), Vec2(48.0f, 0.f), 1, 0.2f);
	GetAnimator()->CreateAnim(L"frog_jumpL", m_pTex, Vec2(48.f * 3.0f,288.0f), Vec2(48.0f), Vec2(48.f, 0.f), 1, 0.1f);
	GetAnimator()->CreateAnim(L"frog_fallL", m_pTex, Vec2(48.0f * 6.0f, 288.0f),Vec2(48.0f), Vec2(48.0f, 0.0f), 1, 0.1f);

	//Right Idle Play
	GetAnimator()->PlayAnim(L"frog_idleR",true);

	//animation offset change
	//Animation* pAnim = GetAnimator()->FindAnim(L"Jiwoo_Front");
	// only one 
	//pAnim->SetFrameOffset(0, Vec2(0.f, 20.f));
	
	
	//all frames
	for (auto pAnim : GetAnimator()->GetAnimationMap()) {
		Animation* tempAnim = pAnim.second;
		for (size_t i = 0; i < tempAnim->GetMaxFrame(); ++i)
			tempAnim->SetFrameOffset(i, Vec2(-48.0f));
	}
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
	GetRigidBody()->StopImmediatelyX();
	m_bIsJump = false;
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
	m_LR = m_bLeft ? "L" : "R";
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
	//���̵� �ִϸ��̼��̳� ���� �ִϸ��̼��� ���� ���ش�.
	//idle animation
	if (m_bIsJump) {
		if (m_bLeft) {
			GetAnimator()->PlayAnim(L"frog_jumpL", true);
		}
		else {
			GetAnimator()->PlayAnim(L"frog_jumpR", true);
		}
	}
	else {
		if (m_bLeft) {
			GetAnimator()->PlayAnim(L"frog_idleL", true);
		}
		else {
			GetAnimator()->PlayAnim(L"frog_idleR", true);
		}
	}
	//jump animation
}

void Player::JumpState()
{
	//jump animation
	//GetAnimator()->PlayAnim(L"Jump", false);

	//���� �������� �÷��� ���� �Ŀ���ŭ ���� �����ش�.
	GetRigidBody()->AddForce(Vec2(0.0f, -m_fJumpPower), FORCE_MODE::IMPULSE);
	m_fJumpPower = 10.0f;
}

void Player::FallState()
{
	GetAnimator()->PlayAnim(L"frog_fall", true);
}

void Player::JumpChargeState()
{
	GetAnimator()->PlayAnim(L"frog_jump_charge", true);

	//�����Ӵ� ����
	m_fJumpPower += 100.0f * fDT;

	//�ִ밪 ����
	m_fJumpPower = clamp(m_fJumpPower, 500.0f, 5000.0f);
}

void Player::HurtState()
{
	//Get hurt action
	//���⼭�� ���� �΋H���� ���� �������� ����!
}

void Player::MoveState()
{
	//Move Animation and move action

	GetAnimator()->PlayAnim(L"frog_hop", true);

	if (m_bLeft) {
		GetRigidBody()->AddForce(Vec2(-350.0f, 0.0f), FORCE_MODE::FORCE);
	}
	else {
		GetRigidBody()->AddForce(Vec2(350.0f, 0.0f),FORCE_MODE::FORCE);
	}

}
#pragma endregion

