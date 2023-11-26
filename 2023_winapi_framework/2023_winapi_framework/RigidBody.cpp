#include "pch.h"
#include "TimeMgr.h"
#include "RigidBody.h"
#include "Object.h"

RigidBody::RigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.0f)
	, m_fFriction(1.0f)
	, m_fMaxVelocity(1.0f)
	, m_vForce(Vec2(0.0f))
	, m_vAccel(Vec2(0.0f))
	, m_vVelocity(Vec2(0.0f))
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::FinalUpdate()
{
	//��
	float force = m_vForce.Length();

	if (force != 0.0f) {
		//����
		m_vForce.Normalize();

		//���ӵ�. �� / ����
		float accel = force / m_fMass;

		//�̰� ���� ���ӵ��� �����ְ� ���ӵ� ���Ϳ� �־��ش�.
		m_vAccel = m_vForce * accel;

		//fDT�� ������� �����Ӵ� ���ӵ��� ������ �� �ְ���
		m_vVelocity += m_vAccel * fDT;
	}

	//���� �ӵ��� 0�� �ƴϴ�?
	if (!m_vVelocity.IsZero()) {
		Vec2 velocity = m_vVelocity;

		//���� ���ϱ�
		velocity.Normalize();

		//������ ���ϱ�
		Vec2 friction = (-velocity) * m_fFriction * fDT;

		//���� ���� ���ӵ��� ���� �ӵ����� Ŀ�� ���
		if (velocity.Length() <= friction.Length()) {
			//�ӵ��� 0���� �ٲ��ְ�
			m_vVelocity = Vec2(0.f);
		}
		else {
			//�ƴϸ� ������ ��ŭ �ӵ��� �����ش�.
			m_vVelocity += friction;
		}
	}

	//���� �ӵ��� ���� ������ �ִ� �ӵ��� �Ѿ��?
	if (m_vVelocity.Length() >= m_fMaxVelocity) {

		//���� ���ϰ�
		m_vVelocity.Normalize();

		//�ִ� �ӵ� �����ش�.
		m_vVelocity *= m_fMaxVelocity;
	}

	Move();
	m_vForce = Vec2(0.0f);
}

void RigidBody::Move()
{
	//���� ���Ѵ�.
	float speed = m_vVelocity.Length();

	//���� 0�̸� ��ȯ���ش�.
	if (speed == 0.0f) return;

	//������ ��� ������ �����ش�.
	Vec2 dir = m_vVelocity;
	dir.Normalize();

	//��ġ�� ��������
	Vec2 pos = m_pOwner->GetPos();

	//�ڿ� fDT�� ������� �����Ӵ� ��ġ�� ������ְ���
	pos += (dir * speed * fDT);

	//���⼭ ������Ʈ�� ��ġ�� ��ȯ�ȴ�.
	m_pOwner->SetPos(pos);
}
