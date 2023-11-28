#include "pch.h"
#include "TimeMgr.h"
#include "RigidBody.h"
#include "Object.h"

RigidBody::RigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.0f)
	, m_fFriction(1.0f)
	, m_vForce(Vec2(0.0f))
	, m_vMaxVelocity(Vec2(0.0f))
	, m_vAccel(Vec2(0.0f))
	, m_vVelocity(Vec2(0.0f))
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::FinalUpdate()
{
	//힘
	float force = m_vForce.Length();

	if (force != 0.0f) {
		//방향
		m_vForce.Normalize();

		//가속도. 힘 / 무게
		float accel = force / m_fMass;

		//이걸 힘과 가속도를 곱해주고 가속도 벡터에 넣어준다.
		m_vAccel = m_vForce * accel;

		//fDT를 곱해줘야 프레임당 가속도를 더해줄 수 있겠지
		m_vVelocity += m_vAccel * fDT;
	}

	//어떤 상황이든 가속도를 계속 더해줘야함
	m_vAccel += m_vAccelAlpha;

	m_vVelocity += m_vAccel * fDT;

	//만약 속도가 0이 아니다?
	//if (!m_vVelocity.IsZero()) {
	//	Vec2 velocity = m_vVelocity;

	//	//방향 구하기
	//	velocity.Normalize();

	//	//마찰력 구하기
	//	Vec2 friction = (-velocity) * m_fFriction * fDT;

	//	//만약 마찰 가속도가 본래 속도보다 커진 경우
	//	if (m_vVelocity.Length() <= friction.Length()) {
	//		//속도를 0으로 바꿔주고
	//		m_vVelocity = Vec2(0.f);
	//	}
	//	else {
	//		//아니면 마찰력 만큼 속도에 더해준다.
	//		m_vVelocity += friction;
	//	}
	//}

	//만약 X값의 속도가 내가 설정한 최대 속도를 넘어간다?
	if (m_vVelocity.x != 0.0f && (fabs(m_vVelocity.x) < fabs(m_vMaxVelocity.x))) {
		m_vVelocity.x = (m_vVelocity.x / fabs(m_vVelocity.x)) * fabs(m_vMaxVelocity.x);
	}
	//Y축도 마찬가지로
	if (m_vVelocity.y != 0.0f && (fabs(m_vVelocity.y) < fabs(m_vMaxVelocity.y))) {
		m_vVelocity.y = (m_vVelocity.y / fabs(m_vVelocity.y)) * fabs(m_vMaxVelocity.y);
	}

	Move();
	m_vForce = Vec2(0.0f);
}

void RigidBody::Move()
{
	//힘을 구한다.
	float speed = m_vVelocity.Length();

	//힘이 0이면 반환해준다.
	if (speed == 0.0f) return;

	//변수에 담고 방향을 구해준다.
	Vec2 dir = m_vVelocity;
	dir.Normalize();

	//위치를 가져오고
	Vec2 pos = m_pOwner->GetPos();

	//뒤에 fDT를 곱해줘야 프레임당 위치를 계산해주겠지
	pos += (dir * speed * fDT);

	//여기서 오브젝트의 위치가 변환된다.
	m_pOwner->SetPos(pos);
}
