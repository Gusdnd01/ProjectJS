#include "pch.h"
#include "Player.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Texture.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"

Player::Player()
	: m_pTex(nullptr)
	, m_bLeft(false)
	, m_bIsGround(false)
	, m_fGravity(20.f)
	, m_sState(STATE::IDLE)
{
	//m_pTex = new Texture;
	//wstring strFilePath = PathMgr::GetInst()->GetResPath();
	//strFilePath += L"Texture\\plane.bmp";
	//m_pTex->Load(strFilePath);
	//m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\plane.bmp");
	m_pTex = ResMgr::GetInst()->TexLoad(L"Player", L"Texture\\jiwoo.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f,30.f));
	//GetCollider()->SetOffSetPos(Vec2(50.f,0.f));
	
	// ������ �� 20�� �ФФ� ������;�ӳ���;������
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

	//// ������ �ǵ帮��
	//Animation* pAnim = GetAnimator()->FindAnim(L"Jiwoo_Front");
	//// �ϳ���
	//pAnim->SetFrameOffset(0, Vec2(0.f, 20.f));

	//// ������ �� 
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
	Vec2 vPos = GetPos();

	vPos = vPos + CalculateMovement();
	vPos = vPos + CalculateGravity();

	if(KEY_PRESS(KEY_TYPE::CTRL))
		GetAnimator()->PlayAnim(L"Jiwoo_Attack", false, 1);
	SetPos(vPos);
	GetAnimator()->Update();
}

//void Player::CreateBullet()
//{
//	Bullet* pBullet = new Bullet;
//	Vec2 vBulletPos = GetPos();
//	vBulletPos.y -= GetScale().y / 2.f;
//	pBullet->SetPos(vBulletPos);
//	pBullet->SetScale(Vec2(25.f,25.f));
////	pBullet->SetDir(M_PI / 4 * 7);
////	pBullet->SetDir(120* M_PI / 180);
//	pBullet->SetDir(Vec2(-10.f,-15.f));
//	pBullet->SetName(L"Player_Bullet");
//	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET);
//}

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
	if (m_bIsGround) return;
	m_bIsGround = true;
}

void Player::ExitCollision(Collider* other)
{
	m_bIsGround = false;
}

Vec2 Player::CalculateGravity()
{
	if (m_bIsGround) return Vec2(.0f);
	return Vec2(0.f, 10.0f* m_fGravity * fDT);
}

Vec2 Player::CalculateMovement()
{
	Vec2 finalPos;

	if (KEY_PRESS(KEY_TYPE::LEFT))
	{
		finalPos.x -= 100.f * fDT;
		GetAnimator()->PlayAnim(L"Jiwoo_Left", true);
	}
	if (KEY_PRESS(KEY_TYPE::RIGHT))
	{
		finalPos.x += 100.f * fDT;
		GetAnimator()->PlayAnim(L"Jiwoo_Right", true);
	}
	if (KEY_DOWN(KEY_TYPE::SPACE)) {
		if (m_bIsGround) {
			finalPos.y -= 1000.f * fDT;
		}
	}

	return finalPos;
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
	//������ ������ �ִϸ��̼�
}

void Player::JumpState()
{
	//������ �� �ִϸ��̼�
}

void Player::HurtState()
{

}

void Player::MoveState(bool left)
{
	//������ �� �ִϸ��̼��̶� ���� ����
	if (left) {

	}
	else {

	}
}
#pragma endregion

