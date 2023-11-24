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
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\jiwoo.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f,30.f));

	CreateRigidBody();
	GetRigidBody()->SetMass(1.0f);
	GetRigidBody()->SetGravity(3.0f);

	GMGI->AddGravObj(this);

	//콜라이더의 오프셋을 변경하고 싶으면 이거 주석풀면된다.
	//GetCollider()->SetOffSetPos(Vec2(50.f,0.f));
	
	//애니메이터랑 애니메이션 설정이다.
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

	//// 오프셋 건드리기
	//Animation* pAnim = GetAnimator()->FindAnim(L"Jiwoo_Front");
	//// 하나만
	//pAnim->SetFrameOffset(0, Vec2(0.f, 20.f));

	//// 프레임 다 
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
	if (other == nullptr) return;
}

void Player::ExitCollision(Collider* other)
{
}

void Player::PlayerInput()
{
	if (m_bIsJump) return;
	STATE state = STATE::IDLE;
	if (KEY_PRESS(KEY_TYPE::LEFT)) {
		state = STATE::MOVE;
		m_bLeft = true;
	}
	if (KEY_PRESS(KEY_TYPE::RIGHT)) {
		state = STATE::MOVE;
		m_bLeft = false;
	}
	if (KEY_DOWN(KEY_TYPE::SPACE)) {
		m_bIsJump = true;
		state = STATE::JUMP;
	}
	StateChange(state);
}


#pragma region FSM
void Player::StateUpdate()
{
	Vec2 vPos = GetPos();
	switch (m_sState)
	{
	case STATE::MOVE:
		MoveState(vPos, m_bLeft);
		break;
	case STATE::IDLE:
		IdleState();
		break;
	case STATE::JUMP:
		JumpState(vPos);
		break;
	case STATE::HURT:
		HurtState();
		break;
	case STATE::END:
		break;
	default:
		break;
	}

	SetPos(vPos);
}
void Player::StateChange(STATE _type)
{
	if (_type == STATE::END) return;

	m_sState = _type;
}

void Player::IdleState()
{
	//가만히 있을때 애니메이션
	GetAnimator()->PlayAnim(L"Jiwoo_Front", true);
}

void Player::JumpState(Vec2& pos)
{
	//점프할 떄 애니메이션
	m_fTimer += fDT;

	if (m_fTimer >= 1 ) {
		StateChange(STATE::IDLE);
		if (GetCollider()->GetCheckBottom()) {
			m_fTimer = 0;
			m_bIsJump = false;
		}
	}

	pos.y -= 100.0f * fDT;
}

void Player::HurtState()
{
	//으악
}

void Player::MoveState(Vec2& pos,bool left)
{
	//움직일 때 애니메이션이랑 대충 ㅇㅇ
	if (left) {
		pos.x -= 100.0f * fDT;
		GetAnimator()->PlayAnim(L"Jiwoo_Left", true);
	}
	else {
		pos.x += 100.0f *fDT;
		GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	}
}
#pragma endregion

